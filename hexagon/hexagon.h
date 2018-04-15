#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

namespace hex {
	/**
	 * Hexagon class
	 */
	class Hexagon
	{
	public:
		// constructors
		explicit Hexagon() : q_(0), r_(0), s_(0) {}
		explicit Hexagon(double q, double r) : q_(q), r_(r), s_(-q - r) {}
		explicit Hexagon(double q, double r, double s) : q_(q), r_(r), s_(s) {}

		// copy constructor
		Hexagon(const Hexagon& hex) : q_(hex.q()), r_(hex.r()), s_(hex.s()) {}
	
		//--- operators ---
		// = operator
		Hexagon& operator = (const Hexagon& hex)
		{
			if (&hex != this)
			{
				q_ = hex.q();
				r_ = hex.r();
				s_ = hex.s();

			}
			return *this;
		}
		// equal operator
		bool operator==(const Hexagon& hex) const
			{ return q() == hex.q() && r() == hex.r() && s() == hex.s();}
		// not equal operator
		bool operator!=(const Hexagon& hex) const	{return !(*this == hex);}

		// greater operator
		bool operator<(const Hexagon& hex) const
			{ return (abs(q()) + abs(r()) + abs(s())) < (abs(hex.q()) + abs(hex.r()) + abs(hex.s()));}

		// less operator
		bool operator>(const Hexagon& hex) const
			{ return (abs(q()) + abs(r()) + abs(s())) > (abs(hex.q()) + abs(hex.r()) + abs(hex.s()));}

		// add operator
		friend Hexagon operator+(const Hexagon& hex0, const Hexagon& hex1)
			{ return Hexagon(hex0.q() + hex1.q(), hex0.r() + hex1.r(), hex0.s() + hex1.s());}

		// subtract operator
		friend Hexagon operator-(const Hexagon& hex0, const Hexagon& hex1)
			{ return Hexagon(hex0.q() - hex1.q(), hex0.r() - hex1.r(), hex0.s() - hex1.s());}

		// multiplication( hex * n )
		friend Hexagon operator*(const Hexagon& hex, const double& n)
			{ return Hexagon((hex.q() * n), (hex.r() * n), (hex.s() * n));}

		// multiplication( n * hex ) 
		friend Hexagon operator*(const double& n, const Hexagon& hex)
			{ return Hexagon((hex.q() * n), (hex.r() * n), (hex.s() * n));}

		// --- members  ---
		double& q() { return q_; }
		double& r() { return r_; }
		double& s() { return s_; }

		double q() const { return q_; }
		double r() const { return r_; }
		double s() const { return s_; }

	private:
		double q_;
		double r_;
		double s_;
	};
}