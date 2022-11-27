#include "matrix.h"
//#include <iostream>
#include <algorithm>
#include <string>

namespace tasks {
	int Matrix::idCounter = 0;

	Matrix::Matrix() : id(idCounter++), M(0), N(0), matrix(nullptr)
	{
		//std::cout << "\n\tCоздание матрицы #" << id << "\n";
	}

	Matrix::Matrix(int M, int N, double* data) : id(idCounter++)
	{
		//new double[M * N];
		//std::cout << "\n\tCоздание матрицы #" << id << "\n";
		if (((this->M = M) < 0) || ((this->N = N) < 0)) {
			throw ("Ќе могу создать матрицу #" + std::to_string(this->id) + ", так как один из размеров < 0");
		}

		if ((this->M == 0) || (this->N == 0)) {
			this->M = this->N = 0;
			this->matrix = nullptr;
		}
		else {
			if (data == nullptr)
				this->matrix = new double[M * N]();
			else {
				this->matrix = new double[M * N];
				for (int i = 0; i < M * N; i++)
					this->matrix[i] = data[i];
				//std::copy(data, data + M * N, this->matrix);
			}
		}

	}

	Matrix::Matrix(int MN, double* data) : Matrix(MN, MN, data) {}

	Matrix::Matrix(int M, int N, double (*foo)(int, int)) : Matrix(M, N)
	{
		for (int i = 0; i < M * N; i++)
			this->matrix[i] = foo(i / N, i % N);
	}

	Matrix::Matrix(int MN, double (*foo)(int, int)) : Matrix(MN, MN, foo) {}

	Matrix::Matrix(const Matrix& Matr) : Matrix(Matr.M, Matr.N, Matr.matrix) {}

	Matrix::Matrix(Matrix&& Matr) : id(idCounter++), M(Matr.M), N(Matr.N), matrix(Matr.matrix)
	{
		//std::cout << "\n\tCоздание матрицы #" << id << "\n";
		Matr.matrix = nullptr;
	}

	void Matrix::Input()
	{
		std::cout << "¬ведите матрицу " << id << "\n";
		for (int i = 0; i < this->M; i++) {
			std::cout << "¬ведите строку " << i + 1 << ":\n";
			for (int j = 0; j < this->N; j++) {
				std::cout << j + 1 << ": ";
				std::cin >> this->matrix[i * this->N + j];
			}
		}
	}
	Matrix& Matrix::Ones()
	{
		for (int i = 0; i < (M < N ? M : N); i++)
			matrix[i * N + i] = 1.0;
		return *this;
	}
	Matrix& Matrix::Zeros()
	{
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				matrix[i * N + j] = 0.0;
		return *this;
	}
	Matrix& Matrix::Transpose()
	{
		if (M != N)
			throw ("не квадратна€");
		for (int i = 0; i < M; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				double temp = matrix[i * N + j];
				matrix[i * N + j] = matrix[j * M + i];
				matrix[j * M + i] = temp;
			}
		}
		//int temp = M;
		//M = N;
		//N = temp;
		return *this;
	}
	int Matrix::GetID() const
	{
		return this->id;
	}
	int Matrix::GetM() const
	{
		return this->M;
	}
	int Matrix::GetN() const
	{
		return this->N;
	}
	double Matrix::Get(int ind1, int ind2) const
	{
		if ((ind1 >= M) || (ind1 < 0))
			throw "ќбращение к отрицательному (" + std::to_string(ind1) + ") индексу (1) матрицы #" + std::to_string(this->id);
		if ((ind2 >= N) || (ind2 < 0))
			throw "ќбращение к отрицательному (" + std::to_string(ind2) + ") индексу (2) матрицы #" + std::to_string(this->id);
		return this->matrix[ind1 * this->N + ind2];
	}
	double Matrix::Get_unsafe(int ind1, int ind2) const
	{
		return matrix[ind1 * N + ind2];
	}
	double& Matrix::Get_unsafe(int ind1, int ind2)
	{
		return matrix[ind1 * N + ind2];
	}
	double Matrix::Get_unsafe(int ind) const
	{
		return matrix[ind];
	}
	double& Matrix::Get_unsafe(int ind)
	{
		return matrix[ind];
	}
	double* Matrix::GetRow(int ind) const
	{
		return matrix + N * ind;
	}
	bool Matrix::IsEmpty() const
	{
		return (this->M == 0) || (this->N == 0);
	}
	bool Matrix::CanMultiply(const Matrix& Matr) const
	{
		return !(this->IsEmpty() || Matr.IsEmpty()) && (this->N == Matr.M);
	}
	bool Matrix::CanAdd(const Matrix& Matr) const
	{
		return !(this->IsEmpty() || Matr.IsEmpty()) && ((this->M == Matr.M) && (this->N == Matr.N));
	}
	double Matrix::Max() const
	{
		if (this->IsEmpty())
			throw "Ќевозможно найти максимум матрицы #" + std::to_string(this->id) + ", так как данна€ матрица пуста€";
		double num = this->matrix[0];
		for (int i = 1; i < this->M * this->N; i++)
			if (this->matrix[i] > num)
				num = this->matrix[i];
		return num;
	}
	double Matrix::Min() const
	{
		if (this->IsEmpty())
			throw "Ќевозможно найти минимум матрицы #" + std::to_string(this->id) + ", так как данна€ матрица пуста€";
		double num = this->matrix[0];
		for (int i = 1; i < this->M * this->N; i++)
			if (this->matrix[i] < num)
				num = this->matrix[i];
		return num;
	}
	void Matrix::swap(Matrix& one, Matrix& two)
	{
		int t = one.M;
		one.M = two.M;
		two.M = t;
		t = one.N;
		one.N = two.N;
		two.N = t;
		double* temp = one.matrix;
		one.matrix = two.matrix;
		two.matrix = temp;
	}
	Matrix::Proxy::Proxy(double* _array, int len) : _array(_array), len(len) { }

	double& Matrix::Proxy::operator[](int index)
	{
		return this->_array[index];
	}

	double Matrix::Proxy::operator[](int index) const
	{
		return this->_array[index];
	}

	std::ostream& operator<<(std::ostream& strm, const Matrix::Proxy& Proxy)
	{
		std::streamsize width = strm.width();
		if (width == 0)
			width = 7;
		for (int i = 0; i < Proxy.len; i++) {
			strm.width(width);
			strm << Proxy._array[i];
		}
		strm << "\n";
		return strm;
	}

	Matrix::Proxy Matrix::operator[](int index)
	{
		return Proxy(this->matrix + index * this->N, this->N);
	}

	const Matrix::Proxy Matrix::operator[](int index) const
	{
		return Proxy(this->matrix + index * this->N, this->N);
	}

	Matrix& Matrix::operator=(const Matrix& Matr)
	{
		if (this->M * this->N != Matr.M * Matr.N) {
			delete[] this->matrix;
			this->matrix = new double[Matr.M * Matr.N];
		}
		this->M = Matr.M;
		this->N = Matr.N;
		//std::copy(Matr.matrix, Matr.matrix + this->M * this->N, this->matrix);
		for (int i = 0; i < M * N; i++)
			this->matrix[i] = Matr.matrix[i];
		return *this;
	}
	Matrix& Matrix::operator=(Matrix&& Matr)
	{
		if (this == &Matr)
			return *this;
		this->M = Matr.M;
		this->N = Matr.N;
		delete[] this->matrix;
		this->matrix = Matr.matrix;
		Matr.matrix = nullptr;
		return *this;
	}
	Matrix& Matrix::operator+=(const Matrix& Matr)
	{
		if (!this->CanAdd(Matr))
			throw "Ќевозможно сложить матрицы #" + std::to_string(this->id) + " и #" + std::to_string(Matr.id) + ", так как либо по крайней мере одна из них - пуста€, либо их размеры не совпадают";
		for (int i = 0; i < this->M * this->N; i++)
			this->matrix[i] += Matr.matrix[i];
		return *this;
	}
	Matrix& Matrix::operator-=(const Matrix& Matr)
	{
		if (!this->CanAdd(Matr))
			throw "Ќевозможно вычесть из матрицы #" + std::to_string(this->id) + " матрицу #" + std::to_string(Matr.id) + ", так как либо по крайней мере одна из них - пуста€, либо их размеры не совпадают";
		for (int i = 0; i < this->M * this->N; i++)
			this->matrix[i] -= Matr.matrix[i];
		return *this;
	}
	Matrix& Matrix::operator*=(const Matrix& Matr)
	{
		if (!this->CanMultiply(Matr))
			throw "Ќевозможно перемножить матрицы #" + std::to_string(this->id) + " и #" + std::to_string(Matr.id) + ", так как либо по крайней мере одна из них - пуста€, либо их размеры не согласованы";

		double* arr = new double[this->M * Matr.N];
		double sum;
		for (int i = 0; i < this->M; i++)
			for (int j = 0; j < Matr.N; j++) {
				sum = 0;
				for (int k = 0; k < this->N; k++)
					sum += this->matrix[i * this->N + k] * Matr.matrix[k * Matr.N + j];
				arr[i * Matr.N + j] = sum;
			}
		delete[] this->matrix;
		this->N = Matr.N;
		this->matrix = arr;
		return *this;
	}
	Matrix& Matrix::operator*=(double val)
	{
		for (int i = 0; i < this->M * this->N; i++)
			this->matrix[i] *= val;
		return *this;
	}
	bool Matrix::operator==(const Matrix& Matr) const
	{
		bool value = ((this->N == Matr.N) && (this->M == Matr.M));
		for (int i = 0; (i < this->N * this->M) && (value); i++)
			value = (value && (this->matrix[i] == Matr.matrix[i]));
		return value;
	}
	bool Matrix::operator!=(const Matrix& Matr) const
	{
		return !(*this == Matr);
	}
	Matrix::~Matrix()
	{
		//std::cout << "\n\t”даление матрицы #" << id << "\n";
		delete[] this->matrix;
	}
	std::ostream& operator<<(std::ostream& strm, const Matrix& Matr)
	{
		std::streamsize width = strm.width();
		if (width == 0)
			width = 11;
		for (int i = 0; i < Matr.M; i++) {
			for (int j = 0; j < Matr.N; j++) {
				strm.width(width);
				strm << Matr.matrix[i * Matr.N + j];
			}
			strm << "\n";
		}
		return strm;
	}
	Matrix operator+(const Matrix& Matr1, const Matrix& Matr2)
	{
		return Matrix(Matr1) += Matr2;
	}
	Matrix operator-(const Matrix& Matr1, const Matrix& Matr2)
	{
		return Matrix(Matr1) -= Matr2;
	}
	Matrix operator*(const Matrix& Matr1, const Matrix& Matr2)
	{
		return Matrix(Matr1) *= Matr2;
	}
	Matrix operator*(const Matrix& Matr, double val)
	{
		return Matrix(Matr) *= val;
	}
	Matrix operator*(double val, const Matrix& Matr)
	{
		return Matrix(Matr) *= val;
	}
}

