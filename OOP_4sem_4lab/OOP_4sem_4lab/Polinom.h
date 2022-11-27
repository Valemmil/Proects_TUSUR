#pragma once
#include<iostream>


namespace Polinoms {
	class Polinom{
	private:
		static int IDS;
		int m_id;
		double* data;
		unsigned l;

	public:
		Polinom(double* data, unsigned l);
		Polinom();
		Polinom(unsigned l);

		Polinom(const Polinom& a);
		Polinom(Polinom&& a) noexcept;

		~Polinom();


		void show();
		void updateZero();


		Polinom& operator+= (const Polinom& b);
		Polinom& operator-= (const Polinom& a);
		Polinom& operator*= (const Polinom& b);
		Polinom& operator/= (const Polinom& b);
		Polinom& operator%=(const Polinom& a);


		friend Polinom operator+(const Polinom& d1, const Polinom& d2);
		friend Polinom operator-(const Polinom& d1, const Polinom& d2);
		friend Polinom operator*(const Polinom& d1, const Polinom& d2);
		friend Polinom operator/(const Polinom& d1, const Polinom& d2);
		friend Polinom operator%(const Polinom& d1, const Polinom& d2);


		double operator()(double x); ///double calculate(double x) const;


		Polinom& operator= (const Polinom& a);
		Polinom& operator=(Polinom&& a) noexcept;

	};
}