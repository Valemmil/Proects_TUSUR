#pragma once

namespace Fractions {
	class Fraction {
	private:
		static int IDS;
		int m_id;

		int numerator;//числитель
		int denominator;//знаменатель

	public:
		Fraction(int numerator = 0, int denominator = 1);
		~Fraction();

		void reduction(); //сокращение дроби
		void rightFraction();
		void show();

		Fraction& operator+= (const Fraction& b);
		Fraction& operator-= (const Fraction& b);
		Fraction& operator*= (const Fraction& b);
		Fraction& operator/= (const Fraction& b);


		friend Fraction operator+(const Fraction& d1, const Fraction& d2);
		friend Fraction operator-(const Fraction& d1, const Fraction& d2);
		friend Fraction operator*(const Fraction& d1, const Fraction& d2);
		friend Fraction operator/(const Fraction& d1, const Fraction& d2);

		Fraction& operator= (const Fraction& a);
	};
}


