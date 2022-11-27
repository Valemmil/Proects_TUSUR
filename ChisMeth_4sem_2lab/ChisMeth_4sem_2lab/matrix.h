#pragma once
#include <iostream>

namespace tasks {
	class Matrix
	{
	private:
		double* matrix;
		int M, N;
		int id;
		static int idCounter;
		class Proxy {
		private:
			double* _array;
			int len;
		public:
			Proxy(double* _array, int len);
			double& operator[](int index);
			double operator[](int index) const;
			friend std::ostream& operator<<(std::ostream& strm, const Proxy& Proxy);
		};
	public:
		Matrix();
		Matrix(int M, int N, double* data = nullptr);
		Matrix(int MN, double* data = nullptr);
		Matrix(int M, int N, double (*foo)(int, int));
		Matrix(int MN, double (*foo)(int, int));
		Matrix(const Matrix& Matr);
		Matrix(Matrix&& Matr);

		void Input();
		Matrix& Ones();
		Matrix& Zeros();
		Matrix& Transpose();
		int GetID() const;
		int GetM() const;
		int GetN() const;
		double Get(int ind1, int ind2) const;
		double Get_unsafe(int ind1, int ind2) const;
		double& Get_unsafe(int ind1, int ind2);
		double Get_unsafe(int ind) const;
		double& Get_unsafe(int ind);
		double* GetRow(int ind) const;
		bool IsEmpty() const;
		bool CanMultiply(const Matrix& Matr) const;
		bool CanAdd(const Matrix& Matr) const;
		double Max() const;
		double Min() const;

		static void swap(Matrix& one, Matrix& two);

		Proxy operator[](int index);
		const Proxy operator[](int index) const;

		Matrix& operator=(const Matrix& Matr);
		Matrix& operator=(Matrix&& Matr);
		Matrix& operator+=(const Matrix& Matr);
		Matrix& operator-=(const Matrix& Matr);
		Matrix& operator*=(const Matrix& Matr);
		Matrix& operator*=(double val);

		bool operator==(const Matrix& Matr) const;
		bool operator!=(const Matrix& Matr) const;

		friend std::ostream& operator<<(std::ostream& strm, const Matrix& Matr);
		friend std::ostream& operator<<(std::ostream& strm, const Proxy& Proxy);
		~Matrix();
	};


	Matrix operator+(const Matrix& Matr1, const Matrix& Matr2);
	Matrix operator-(const Matrix& Matr1, const Matrix& Matr2);
	Matrix operator*(const Matrix& Matr1, const Matrix& Matr2);
	Matrix operator*(const Matrix& Matr, double val);
	Matrix operator*(double val, const Matrix& Matr);


}


