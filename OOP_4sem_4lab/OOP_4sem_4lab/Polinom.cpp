#include "Polinom.h"
#include <iostream>
#include <cmath>

using namespace std;

namespace Polinoms {

	int max(int a, int b) {
		if (a > b) return a;
		return b;
	}


	int Polinom::IDS = 0;


	Polinom::Polinom()
	{
		m_id = IDS++;
		l = 0;
		data = nullptr;
		//cout << "P_Constructor " << this << endl;
	}


	Polinom::Polinom(double* data, unsigned l)
	{
		m_id = IDS++;

		this->l = l;
		this->data = new double[this->l + 1]();
		copy(data, data + l + 1, this->data);
		updateZero();
		//cout << "P_Constructor " << this << endl;
	}


	Polinom::Polinom(unsigned _l)
	{
		m_id = IDS++;
		l = _l;
		data = new double[l + 1]();

		//cout << "P_Constructor " << this << endl;

		return;
	}


	Polinom::Polinom(const Polinom& other) :Polinom() { //конструктор копирования
		*this = other;
		//cout << "P_Constructor (copy) " << this << endl;
	}


	Polinom::Polinom(Polinom&& other) noexcept :Polinom()	//спецификатор не пропускающий исключения
	{
		*this = move(other);
		//cout << "P_Constructor " << this << endl;
	}


	Polinom::~Polinom()
	{
		delete[] data;
		//cout << "P_Destructor " << this << endl;
	}


	void Polinom::show()//вывод полинома
	{
		for (unsigned i = 0; i <= l; i++) {
			if (data[i] > 0)
				cout << "+" << data[i] << "*x^" << i;
			if (data[i] < 0)
				cout << data[i] << "*x^" << i;
			else
				continue;
		}
	}


	Polinom& Polinom::operator+= (const Polinom& b)
	{
		if (b.l == l) {
			for (unsigned k = 0; k <= l; k++)
				data[k] = data[k] + b.data[k];

			return *this;
		}
		
		if (b.l < l) {
			for (unsigned k = 0; k <= b.l; k++)
				data[k] = data[k] + b.data[k];

			return *this;
		}
		
		if (b.l > l) {
			for (unsigned k = 0; k <= b.l; k++) {
				if (k >= l) {
					data[k] = b.data[k];
					l++;
				}
				else {
					data[k] = data[k] + b.data[k];
				}
			}
		}
		return *this;
	}

	Polinom& Polinom::operator-= (const Polinom& b)
	{
		if (b.l == l) {
			for (unsigned k = 0; k <= l; k++) 
				data[k] = data[k] - b.data[k];

			return *this;
		}
		
		if (b.l < l) {
			for (unsigned k = 0; k <= b.l; k++)
				data[k] = data[k] - b.data[k];

			return *this;
		}
		
		if (b.l > l) {
			for (unsigned k = 0; k <= b.l; k++) {
				if (k >= l) {
					data[k] = -b.data[k];
					l++;
				}
				else
				{
					data[k] = data[k] - b.data[k];
				}
			}
		}
		return *this;
	}


	Polinom& Polinom::operator*= (const Polinom& b)
	{
		int new_l = l * b.l;
		double* new_data = new double[new_l + 1]();

		for (unsigned i = 0; i <= l; i++) {
			for (unsigned j = 0; j <= b.l; j++) {
				new_data[i + j] = new_data[i + j] + data[i] * b.data[j];
			}
		}

		data = new_data;
		l = new_l;

		return *this;
	}


	Polinom& Polinom::operator/= (const Polinom& b)
	{
		if ((b.data[b.l] == 0) || (l < b.l))
			throw "Size error.\n";

		unsigned newL = l - b.l;

		Polinom result(newL);

		for (unsigned i = 0; i <= result.l; ++i) {
			result.data[newL - i] = data[l - i] / b.data[b.l];

			for (unsigned j = 0; j <= b.l; j++) {
				data[l - j - i] -= b.data[b.l - j] * result.data[newL - i];
			}
		}

		*this = result;
		void updateZero();
		return *this;
	}


	Polinom& Polinom::operator%=(const Polinom& rhs)
	{
		if ((rhs.data[rhs.l] == 0) || (l < rhs.l))
			throw "Size error.\n";

		unsigned new_degree = l - rhs.l;

		for (unsigned i = 0; i <= new_degree; ++i) {
			double element = data[l - i] / rhs.data[rhs.l];

			for (unsigned j = 0; j <= rhs.l; j++) {
				data[l - j - i] -= rhs.data[rhs.l - j] * element;
			}
		}

		updateZero();
		return *this;
	}


	double Polinom::operator()(double x)
	{
		double value = 0;
		for (unsigned k = 0; k <= l; k++) {
			value = value + data[k] * pow(x, k);
		}
		return value;
	}

	Polinom& Polinom::operator=(Polinom&& rhs) noexcept
	{
		if (this != &rhs) {
			delete[] data;
			data = rhs.data;
			l = rhs.l;
			rhs.data = nullptr;
			rhs.l = 0;
		}
		return *this;
	}

	void Polinom::updateZero()
	{
		if (l > 0) {
			while (data[l] == 0) {
				l--;
			}
		}
	}


	Polinom& Polinom::operator= (const Polinom& a)
	{
		if (l != a.l) {
			if (data != NULL) delete[]data;
			data = new double[a.l + 1];
		}

		l = a.l;
		copy(a.data, a.data + l + 1, data);
		return *this;
	}


	Polinom operator+(const Polinom& d1, const Polinom& d2)
	{
		Polinom a(d1);
		a += d2;
		return a;
	}

	Polinom operator-(const Polinom& d1, const Polinom& d2)
	{
		Polinom a(d1);
		a -= d2;
		return a;
	}

	Polinom operator*(const Polinom& d1, const Polinom& d2)
	{
		Polinom a(d1);
		a *= d2;
		return a;
	}

	Polinom operator/(const Polinom& d1, const Polinom& d2)
	{
		Polinom a(d1);
		a /= d2;
		return a;
	}

	Polinom operator%(const Polinom& d1, const Polinom& d2)
	{
		Polinom a(d1);
		a %= d2;
		return a;
	}

}