#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <unordered_map>
using std::unordered_map;
using std::max;

namespace hex {
	struct honeycomb{
		static int get_number(int q, int r) { return  ((q + 1) << 2) | (r + 1); }
		static unordered_map<int, int> get_pattern(int q, int r, int s)  {
			if (q == 0 && r == 0) 	// ����	
				return { { 6,1 },{ 2,1 },{ 9,1 },{ 5,0 },{ 1,1 } ,{ 8,1 },{ 4,1 } };

			if (q == 0) 
			{
				if (r > 0)			//�k�@�p
					return { { 6,1 },{ 2,1 },{ 9,1 },{ 5,0 },{ 1,0 } ,{ 8,0 },{ 4,-1 } };
				else				//��@�p
					return { { 6,-1 },{ 2,0 },{ 9,0 },{ 5,0 },{ 1,1 } ,{ 8,1 },{ 4,1 } };
			}
			else if (r == 0)
			{
				if (q > 0)			//�k���@�p
					return { { 6,1 },{ 2,0 },{ 9,1 },{ 5,0 },{ 1,-1 } ,{ 8,1 },{ 4,0 } };
				else				//�쐼�@�p
					return { { 6,0 },{ 2,1 },{ 9,-1 },{ 5,0 },{ 1,1 },{ 8,0 },{ 4,1 } };
			}
			else if (s == 0)
			{
				if (r > 0)			//�k���@�p
					return { { 6,1 },{ 2,1 },{ 9,0 },{ 5,0 },{ 1,1 },{ 8,-1 },{ 4,0 } };
				else				//�쓌�@�p
					return { { 6,0 },{ 2,-1},{ 9,1 },{ 5,0 },{ 1,0 }, { 8,1 },{ 4,1 } };
			}
			else
			{
				const int aq{ abs(q) };
				const int ar{ abs(r) };
				const int as{ abs(s) };

				if (aq > ar && aq > as)
					if (q > 0)		// ���@��
						return { { 6,0 },{ 2,-1 },{ 9,1 },{ 5,0 },{ 1,-1 } ,{ 8,1 },{ 4,0 } };
					else			// ���@��
						return { { 6,0 },{ 2,1 },{ 9,-1 },{ 5,0 },{ 1,1 } ,{ 8,-1 },{ 4,0 } };
				else
					if (ar > as)
						if (r > 0)	//�k���@��
							return { { 6,1 },{ 2,1 },{ 9,0 },{ 5,0 },{ 1,0} ,{ 8,-1 },{ 4,-1} };
						else		//�쓌�@��
							return { { 6,-1 },{ 2,-1 },{ 9,0 },{ 5,0 },	{ 1,0 } ,{ 8,1 },{ 4,1 } };
					else
						if (s > 0)	//�쐼�@��
							return { { 6,-1 },{ 2,0 },{ 9,-1 },{ 5,0 },{ 1,1 } ,{ 8,0 },{ 4,1 } };
						else		//�k���@��
							return { { 6,1 },{ 2,0 },{ 9,1 },{ 5,0 },{ 1,-1 } ,{ 8,0 },{ 4,-1 } };
			}
		}
	};
}