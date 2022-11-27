#include <iostream>
#include "Fraction.h"

using namespace std;

namespace Fractions {
	int Fraction::IDS = 0;

	Fraction::Fraction(int numerator, int denominator)//конструктор
	{
		if (denominator == 0) throw "1";

		m_id = IDS++;

		//cout << "F_Constructor " << this << endl;

		this->numerator = numerator;
		this->denominator = denominator;
		reduction();
	}


	Fraction::~Fraction() //деструктор
	{
		//cout << "F_Destructor " << this << endl;
	}


	void Fraction::reduction() //сокращение дроби
	{
		if (denominator < 0)
		{
			this->denominator = -this->denominator;
			this->numerator = -this->numerator;
		}

		int a = this->numerator;
		int b = this->denominator;

		while (b > 0) {
			int c = a % b;
			a = b;
			b = c;
		}
		this->numerator = this->numerator / a;
		this->denominator = this->denominator / a;
	}


	void Fraction::rightFraction()
	{
		reduction();
		int new_denominator = this->denominator;
		int whole = this->numerator / this->denominator;
		int new_numerator = this->numerator % new_denominator;

		if (new_numerator != 0)
			cout << endl << whole << " " << new_numerator << "/" << new_denominator << endl;
		else
			cout << endl << whole << endl;
	}


	void Fraction::show() //вывод
	{
		if (this->denominator == 1)
			cout << endl << numerator << endl;
		else
			cout << endl << numerator << "/" << denominator << endl;
	}


	Fraction& Fraction::operator+= (const Fraction& b)
	{
		int new_denominator = this->denominator * b.denominator;
		int new_numerator = this->numerator * new_denominator / this->denominator + b.numerator * new_denominator / b.denominator;

		this->denominator = new_denominator;
		this->numerator = new_numerator;

		reduction();
		return *this;
	}


	Fraction& Fraction::operator-= (const Fraction& b)
	{
		int new_denominator = this->denominator * b.denominator;
		int new_numerator = this->numerator * new_denominator / this->denominator - b.numerator * new_denominator / b.denominator;

		this->denominator = new_denominator;
		this->numerator = new_numerator;

		reduction();
		return *this;
	}


	Fraction& Fraction::operator*= (const Fraction& b)
	{
		int new_denominator = this->denominator * b.denominator;
		int new_numerator = this->numerator * b.numerator;

		this->denominator = new_denominator;
		this->numerator = new_numerator;

		reduction();
		return *this;
	}


	Fraction& Fraction::operator/= (const Fraction& b)
	{
		int new_denominator = this->denominator * b.numerator;
		int new_numerator = this->numerator * b.denominator;

		this->denominator = new_denominator;
		this->numerator = new_numerator;

		reduction();
		return *this;
	}


	Fraction operator+(const Fraction& d1, const Fraction& d2)
	{
		Fraction a(d1);
		a += d2;
		return a;
	}


	Fraction operator-(const Fraction& d1, const Fraction& d2)
	{
		Fraction a(d1);
		a -= d2;
		return a;
	}


	Fraction operator*(const Fraction& d1, const Fraction& d2)
	{
		Fraction a(d1);
		a *= d2;
		return a;
	}


	Fraction operator/(const Fraction& d1, const Fraction& d2)
	{
		Fraction a(d1);
		a /= d2;
		return a;
	}


	Fraction& Fraction::operator= (const Fraction& a)
	{
		numerator = a.numerator;
		denominator = a.denominator;

		return *this;
	}
}
