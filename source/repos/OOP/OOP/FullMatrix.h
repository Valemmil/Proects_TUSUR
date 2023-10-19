#pragma once
#include <iostream>
namespace tasks {
	class MyException : public std::exception
	{
	private:
		std::string m_error;

	public:
		MyException(std::string error);

		// ¬озвращаем std::string в качестве константной строки C-style
		const char* what() const noexcept;
	};
	class Matrix
	{
	private:
		class Proxy {
		private:
			double* _array;
		public:
			Proxy(double* _array);
			double& operator[](const int& index);
			double operator[](const int& index) const;
		};
	protected:
		int id;
		static int idCounter;
		double* matrix;
		int M, N;
	public:
		explicit Matrix();
		explicit Matrix(int M, int N, double* data = nullptr);
		explicit Matrix(int MN, double* data = nullptr);
		explicit Matrix(int M, int N, double (*foo)(int, int));
		explicit Matrix(int MN, double (*foo)(int, int));
		explicit Matrix(const Matrix& Matr);
		Matrix(Matrix&& Matr) noexcept;

		void Input();
		int GetID() const;
		int GetM() const;
		int GetN() const;
		double* GetArray() const;
		double Get(int ind1, int ind2) const;
		bool IsEmpty() const;
		static bool CanMultiply(const Matrix& Matr1, const Matrix& Matr2);
		static bool CanAdd(const Matrix& Matr1, const Matrix& Matr2);
		double Max() const;
		double Min() const;


		Proxy operator[](const int& index);
		const Proxy operator[](const int& index) const;

		Matrix& operator=(const Matrix& Matr);
		Matrix& operator=(Matrix&& Matr) noexcept;
		Matrix& operator+=(const Matrix& Matr);
		Matrix& operator-=(const Matrix& Matr);
		Matrix& operator*=(const Matrix& Matr);
		Matrix& operator*=(const double& val);

		friend std::ostream& operator<<(std::ostream& strm, const Matrix& Matr);

		~Matrix();
	};
	Matrix operator+(const Matrix& Matr1, const Matrix& Matr2);
	Matrix operator-(const Matrix& Matr1, const Matrix& Matr2);
	Matrix operator*(const Matrix& Matr1, const Matrix& Matr2);
	Matrix operator*(const Matrix& Matr, const double& val);
	Matrix operator*(const double& val, const Matrix& Matr);

	class Vector : public Matrix
	{
	public:
		explicit Vector(int N = 0, double* data = nullptr);
		Vector(const Vector& Vect);
		Vector(Vector&& Vect) noexcept;
		Vector(const Matrix& Vect);
		Vector(Matrix&& Vect);
		double Get(int ind1) const;
		Vector& Transpose();
		Vector TransposeCopy() const;
		double& operator[](int ind);
		double operator[](int ind) const;

		double GetLength() const;
		void Normalize();

		Vector& operator=(const Matrix& other);
		Vector& operator=(Matrix&& other);
		Vector& operator=(const Vector& other);
		Vector& operator=(Vector&& other) noexcept;
		Vector& operator*=(const Matrix& Matr);
		Vector& operator*=(const Vector& Vect);
		Vector& operator*=(double val);
	};
	/*Matrix operator*(const Matrix& Matr, const Vector& Vect);
	Vector operator*(const Vector& Vect, const Matrix& Matr);
	Vector operator*(const Vector& Vect1, const Vector& Vect2);*/
}

