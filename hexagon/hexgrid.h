﻿#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#include "hexagon.h"


using std::abs;
using std::ceil;
using std::pair;
using std::vector;
using std::map;
using std::unordered_map;
using hex::Hexagon;

namespace hex {
	enum Layout
	{
		HORIZONTAL, // Flat
		VERTICAL // Pointy
	};

	struct Point
	{
		double x;
		double y;
		Point(double x_, double y_) : x(x_), y(y_) {}
	};

	struct Orientation
	{
		const double f0;
		const double f1;
		const double f2;
		const double f3;
		const double b0;
		const double b1;
		const double b2;
		const double b3;
		Orientation(double f0_, double f1_, double f2_, double f3_, double b0_, double b1_, double b2_, double b3_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), b0(b0_), b1(b1_), b2(b2_), b3(b3_) {}
	};

	struct hash {
		typedef size_t result_type;
		size_t operator()(const Hexagon& h) const {
			std::hash<double> fn_hash;
			size_t hq = fn_hash(h.q());
			size_t hr = fn_hash(h.r());
			return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
		}
	};
	struct OffsetCoord {
		const int col, row;
		OffsetCoord(int col_, int row_) : col(col_), row(row_) {}
	};


	class HexGrid
	{
	public:
		explicit HexGrid(double radius_, Layout layout_) : m_radius(radius_), m_orientation(set_orientation(layout_)) {}


		Hexagon opposite(const Hexagon & hex)
		{
			return	Hexagon( -1 * hex.q(), -1 * hex.r(), -1 * hex.s() );
		}

		double hex_length(Hexagon hex)
		{
			return ((abs(hex.q()) + abs(hex.r()) + abs(hex.s())) / 2.0);
		}

		double hex_distance(Hexagon a, Hexagon b)
		{
			return hex_length(a - b);
		}
		Hexagon round_hex(double frac_q, double frac_r, double frac_s)
		{
			double q = (round(frac_q));
			double r = (round(frac_r));
			double s = (round(frac_s));

			double q_diff = abs(q - frac_q);
			double r_diff = abs(r - frac_r);
			double s_diff = abs(s - frac_s);

			if (q_diff > r_diff && q_diff > s_diff)
			{
				q = -r - s;
			}
			else if (r_diff > s_diff)
			{
				r = -q - s;
			}
			else
			{
				s = -q - r;
			}
			return Hexagon(q, r, s);
		}

		Point hex_to_pixel(const Hexagon &h)
		{
			const Orientation M{ m_orientation };
			double x = (M.f0 * h.q() + M.f1 * h.r())*m_radius;
			double y = (M.f2 * h.q() + M.f3 * h.r())*m_radius;
			return Point(x, y);
		}
		vector<pair<Hexagon,uint8_t>> belongs_to_center(const Hexagon &h) const
		{
			vector<Hexagon> results{};
			int mod = int(h.q() - h.r() * 2) % 7;
			int n = _to_seven_num(mod);
			return m_index_directions[n];
		}
		int to_seven_num(const Hexagon &h) const
		{
			int mod = int(h.q() - h.r() * 2) % 7;
			return _to_seven_num(mod);

		}

		int _to_seven_num(int n) const {
			switch (n){
			case 0:	return 0;
			case 1:	return 5;
			case 2:	return 1;
			case 3:	return 6;
			case 4:	return 3;
			case 5:	return 4;
			case 6:	return 2;
			default:return 0;
			}
		}

		int get_filter(int n){
			switch (n) {
			case 0: return	0b10000000;
			case 1: return	0b00000001;
			case 2: return	0b00000010;
			case 3: return	0b00000100;
			case 4: return	0b00001000;
			case 5: return	0b00010000;
			case 6: return	0b00100000;
			default : return	0b10000000;
			}

		}
		void set_index(Hexagon idx,Hexagon data, uint8_t filter) 
		{
			unordered_map< Hexagon, unordered_map<uint8_t,Hexagon>, hash > x;
			auto it = m_indexes.find(idx);
			// インデックスにない場合
			if (it == end(m_indexes))
			{
				m_indexes[idx] = {{data,filter}};
			}
			else
			{
				if(m_indexes[idx].find(data)==end(m_indexes[idx]))
					m_indexes[idx][data] = filter;
			}
		}

		Hexagon pixel_to_hex(const Point &p)
		{
			const Point pt{ p.x / m_radius , p.y / m_radius };
			const Orientation M{ m_orientation };
			double q = double(M.b0 * pt.x + M.b1 * pt.y);
			double r = double(M.b2 * pt.x + M.b3 * pt.y);
			return Hexagon(q, r, -q - r);

		}
		

		void add_point(const Hexagon & hex, const Point & pt)
		{
			auto it = m_hexagon_map.find(hex);
			if (it != m_hexagon_map.end()) {
				m_hexagon_map[hex].push_back(pt);
				vector<pair<Hexagon, uint8_t>> belongs = belongs_to_center(hex);
				for (auto idx = belongs.begin(); idx != end(belongs); ++idx) 
				{
					set_index(idx->first, hex, idx->second);				
				}
			}
			else
			{
				m_hexagon_map[hex] = { pt };
			}
		}

		vector<Point> & get_points(const Hexagon & hex)
		{
			auto it = m_hexagon_map.find(hex);
			if (it != m_hexagon_map.end()) {
				return (static_cast<vector<Point>>(it->second));
			}
			return vector<Point>{};
		}

		/**
		* 円環状にセルを移動しながら点群が存在する座標を調べます。
		*/
		vector<Hexagon> walk_on_ring(const Hexagon & center, int step) {
			// グリッド座標をセットする
			vector<Hexagon> results{};

			// 5の方角に移動する。
			Hexagon hex = center + (m_hex_directions[5] * (double)step);
			// 点群が存在するか確認
			if (m_hexagon_map.find(hex) != m_hexagon_map.end()) {
				results.push_back(hex);
			}
			// ６回方向を変える
			for (int i = 0; i < 6; i++) {
				// 円の大きさ分直進する
				for (int j = 0; j < step; j++) {
					hex = m_hex_directions[i] + hex;
					// 点群が存在するか確認
					if (m_hexagon_map.find(hex) != m_hexagon_map.end()) {
						results.push_back(hex);
					}
				}
			}
			return results;
		}

		/**
		* 近傍点を探索します。
		*/
		unordered_map<int, vector<Hexagon>> neighbors(const Hexagon & center, double distance) {
			// 点群が存在するグリッド座標を格納する
			unordered_map<int, vector<Hexagon>> results{};
			// 起点のインデックス位置を確認
			int seven_num = to_seven_num(center);
			int filter = get_filter(seven_num);
			Hexagon index_pos = opposite(m_hex_directions[seven_num]);

			// 原点のセルに点群が存在するかを確認
			if (m_hexagon_map.find(center) != m_hexagon_map.end()) {
				results[0] = { center };
			}



			// グリッド間の距離の計算
			double grid_size = (2 * m_radius* sqrt(3));
			// 探索対象範囲の上限
			int limit = int(ceil(distance / grid_size)) + 1;
			// １つ離れたセルから同心円状に探索対象範囲を移動します。
			for (int i = 1; i <= limit; i++) {
				results[i] = walk_on_ring(center, i);
			}
			return results;
		}

	private:

		const Orientation set_orientation(const Layout & layout)
		{
			if (layout == Layout::HORIZONTAL)
			{
				return{ 3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0), 2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0 };
			}
			else
			{
				return{ sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0, sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0 };
			}

		}


		const double m_radius;
		const Orientation m_orientation;
		unordered_map< Hexagon, vector<Point>, hash > m_hexagon_map;

		// 7方向へ移動する為の座標
		const std::vector<Hexagon> m_hex_directions = {
			Hexagon(+0,+0,+0),	// 中央
			Hexagon(+1,-3,+2),	// 南
			Hexagon(-2,-1,+3),	// 南西
			Hexagon(-3,+2,+1),	// 北西
			Hexagon(-1,+3,-2),	// 北
			Hexagon(+2,+1,-3),	// 北東
			Hexagon(+3,-2,-1)	// 南東
		};

		const std::vector<Hexagon> m_honeycomb_directions = {
			Hexagon(+0,+0,+0),	// 中央
			Hexagon(+0,-1,+1),	// 南
			Hexagon(-1,+0,+1),	// 南西
			Hexagon(-1,+1,+0),	// 北西
			Hexagon(+0,+1,-1),	// 北
			Hexagon(+1,+0,-1),	// 北東
			Hexagon(+1,-1,+0)	// 南東
		};





		const std::vector<vector<pair<Hexagon, uint8_t>>> m_index_directions = {
			{{ Hexagon(+0,+0,+0),0b10111111 }/*中央*/},
			/*------------------------------------------------------------------------------------------------*/
			{{ Hexagon(+0,+1,-1),0b10100011 }/* 南 */,{Hexagon(+1,-2,+1),0b00001100 }/*北北西*/,{Hexagon(-2,+0,+2),0b00010000}/*北西２*/ },
			{{ Hexagon(+1,+0,-1),0b10000111 }/*南西*/,{Hexagon(-1,-1,+2),0b00011000 }/*北北東*/,{Hexagon(-2,+2,+0),0b00100000}/*南東２*/ }, 
			{{ Hexagon(+1,-1,+0),0b10001110 }/*北西*/,{Hexagon(-2,+1,+1),0b00110000 }/* 東２ */,{Hexagon(+0,+2,-2),0b00000001}/* 南２ */ }, 
			{{ Hexagon(+0,-1,+1),0b10011100 }/* 北 */,{Hexagon(-1,+2,-1),0b00100001 }/*南南東*/,{Hexagon(+2,+0,-2),0b00000010}/*南西２*/ }, 
			{{ Hexagon(-1,+0,+1),0b10111000 }/*北東*/,{Hexagon(+1,+1,-2),0b00000011 }/*南南西*/,{Hexagon(+2,-2,+0),0b00000100}/*北西２*/ }, 
			{{ Hexagon(-1,+1,+0),0b10110001 }/*南東*/,{Hexagon(+2,-1,-1),0b00000110 }/* 西２ */,{Hexagon(+0,-2,+2),0b00001000}/* 北２ */ }
			/*------------------------------------------------------------------------------------------------*/
		};
		unordered_map< Hexagon, map<Hexagon,uint8_t >, hash > m_indexes;

	};
}

