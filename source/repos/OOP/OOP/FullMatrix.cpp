#include "FullMatrix.h"
#include <math.h>
#include <string>
namespace tasks {
	MyException::MyException(std::string error) : m_error(error) {}
	const char* MyException::what() const noexcept {
		return m_error.c_str(); // C++11 и выше
	}
	int Matrix::idCounter = 0;

	Matrix::Matrix() : id(idCounter++), M(0), N(0), matrix(nullptr)
	{
		std::cout << "\n\t—оздание массива " << id << "\n";
	}

	Matrix::Matrix(int M, int N, double* data) : id(idCounter++)
	{
		std::cout << "\n\t—оздание массива " << id << "\n";
		if (((this->M = M) < 0) || ((this->N = N) < 0)) {
			throw MyException(std::string("Invalid Sized Matrix ") + std::to_string(this->id) + ":" + std::to_string(M) + " " + std::to_string(N));
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
				std::copy(data, data + M * N, this->matrix);
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

	Matrix::Matrix(Matrix&& Matr) noexcept : id(idCounter++), M(Matr.M), N(Matr.N)
	{
		this->matrix = Matr.matrix;
		Matr.matrix = nullptr;
	}

	void Matrix::Input()
	{
		std::cout << "¬ведите массив " << id << "\n";
		for (int i = 0; i < this->M; i++) {
			std::cout << "¬ведите строку " << i + 1 << ":\n";
			for (int j = 0; j < this->N; j++) {
				std::cout << j + 1 << ": ";
				std::cin >> this->matrix[i * this->N + j];
			}
		}
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
	double* Matrix::GetArray() const
	{
		return this->matrix;
	}
	double Matrix::Get(int ind1, int ind2) const
	{
		if ((ind1 >= M) || (ind1 < 0))
			throw MyException("Invalid matrix " + std::to_string(this->id) + "index1: " + std::to_string(ind1));
		if ((ind2 >= N) || (ind2 < 0))
			throw MyException("Invalid matrix " + std::to_string(this->id) + "index2: " + std::to_string(ind2));
		return this->matrix[ind1 * this->N + ind2];
	}
	bool Matrix::IsEmpty() const
	{
		return (this->M == 0) || (this->N == 0);
	}
	bool Matrix::CanMultiply(const Matrix& Matr1, const Matrix& Matr2)
	{
		return !(Matr1.IsEmpty() || Matr2.IsEmpty()) && (Matr1.N == Matr2.M);
	}
	bool Matrix::CanAdd(const Matrix& Matr1, const Matrix& Matr2)
	{
		return !(Matr1.IsEmpty() || Matr2.IsEmpty()) && ((Matr1.M == Matr2.M) && (Matr1.N == Matr2.N));
	}
	double Matrix::Max() const
	{
		if (this->IsEmpty())
			throw MyException("Max of empty matrix " + std::to_string(this->id));
		double num = this->matrix[0];
		for (int i = 1; i < this->M * this->N; i++)
			if (this->matrix[i] > num)
				num = this->matrix[i];
		return num;
	}
	double Matrix::Min() const
	{
		if (this->IsEmpty())
			throw MyException("Min of empty matrix " + std::to_string(this->id));
		double num = this->matrix[0];
		for (int i = 1; i < this->M * this->N; i++)
			if (this->matrix[i] < num)
				num = this->matrix[i];
		return num;
	}

	Matrix::Proxy::Proxy(double* _array) : _array(_array) { }

	double& Matrix::Proxy::operator[](const int& index)
	{
		return this->_array[index];
	}

	double Matrix::Proxy::operator[](const int& index) const
	{
		return this->_array[index];
	}

	Matrix::Proxy Matrix::operator[](const int& index)
	{
		return Proxy(this->matrix + index * this->N);
	}

	const Matrix::Proxy Matrix::operator[](const int& index) const
	{
		return Proxy(this->matrix + index * this->N);
	}

	Matrix& Matrix::operator=(const Matrix& Matr)
	{
		if (this->M * this->N != Matr.M * Matr.N) {
			delete[] this->matrix;
			this->matrix = new double[Matr.M * Matr.N];
		}
		this->M = Matr.M;
		this->N = Matr.N;
		std::copy(Matr.matrix, Matr.matrix + this->M * this->N, this->matrix);
		return *this;
	}
	Matrix& Matrix::operator=(Matrix&& Matr) noexcept
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
		if (!CanAdd(*this, Matr))
			throw MyException("Cannot add " + std::to_string(this->id) + " and " + std::to_string(Matr.id));
		for (int i = 0; i < this->M * this->N; i++)
			this->matrix[i] += Matr.matrix[i];
		return *this;
	}
	Matrix& Matrix::operator-=(const Matrix& Matr)
	{
		if (!CanAdd(*this, Matr))
			throw MyException("Cannot subtract " + std::to_string(this->id) + " and " + std::to_string(Matr.id));
		for (int i = 0; i < this->M * this->N; i++)
			this->matrix[i] -= Matr.matrix[i];
		return *this;
	}
	Matrix& Matrix::operator*=(const Matrix& Matr)
	{
		if (!CanMultiply(*this, Matr))
			throw MyException("Cannot multiply " + std::to_string(this->id) + " and " + std::to_string(Matr.id));

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
	Matrix& Matrix::operator*=(const double& val)
	{
		for (int i = 0; i < this->M * this->N; i++)
			this->matrix[i] *= val;
		return *this;
	}
	Matrix::~Matrix()
	{
		std::cout << "\n\t”даление массива " << id << "\n";
		delete[] this->matrix;
	}
	std::ostream& operator<<(std::ostream& strm, const Matrix& Matr)
	{
		std::streamsize width = strm.width();
		for (int i = 0; i < Matr.M; i++) {
			for (int j = 0; j < Matr.N; j++) {
				if (width == 0)
					strm.width(7);
				else
					strm.width(width);
				strm << Matr.matrix[i * Matr.N + j];
			}
			strm << "\n";
		}
		return strm;
	}
	Matrix operator+(const Matrix& Matr1, const Matrix& Matr2)
	{
		return std::move(Matrix(Matr1) += Matr2);
	}
	Matrix operator-(const Matrix& Matr1, const Matrix& Matr2)
	{
		return std::move(Matrix(Matr1) -= Matr2);
	}
	Matrix operator*(const Matrix& Matr1, const Matrix& Matr2)
	{
		return std::move(Matrix(Matr1) *= Matr2);
	}
	Matrix operator*(const Matrix& Matr, const double& val)
	{
		return std::move(Matrix(Matr) *= val);
	}
	Matrix operator*(const double& val, const Matrix& Matr)
	{
		return std::move(Matrix(Matr) *= val);
	}

	//int Vector::idCounter = 0;
	Vector::Vector(int N, double* data) : Matrix(1, N, data) {}

	Vector::Vector(const Vector& Vect) : Vector(Vect.N, Vect.matrix) {}

	Vector::Vector(Vector&& Vect) noexcept : Matrix(Vect) {}

	Vector::Vector(const Matrix& Vect)
	{
		this->id = idCounter++;
		if (!((Vect.GetN()==1)||(Vect.GetM()==1)))
			throw MyException("Cannot copy to V#" + std::to_string(this->id) + " from M#" + std::to_string(Vect.GetID()));
		Matrix::operator=(Vect);
	}

	Vector::Vector(Matrix&& Vect)
	{
		this->id = idCounter++;
		if (!((Vect.GetN() == 1) || (Vect.GetM() == 1)))
			throw MyException("Cannot move to V#" + std::to_string(this->id) + " from M#" + std::to_string(Vect.GetID()));
		Matrix::operator=(Vect);
	}

	double Vector::Get(int ind1) const
	{
		if ((ind1 >= this->N)||(ind1 < 0))
			throw MyException("Invalid vector  " + std::to_string(this->id) + " index " + std::to_string(ind1));
		return this->matrix[ind1];
	}

	Vector& Vector::Transpose()
	{
		std::swap(this->M, this->N);
		return *this;
	}

	Vector Vector::TransposeCopy() const
	{
		return std::move(Vector(*this).Transpose());
	}

	double& Vector::operator[](int ind)
	{
		return this->matrix[ind];
	}

	double Vector::operator[](int ind) const
	{
		return this->matrix[ind];
	}

	double Vector::GetLength() const
	{
		double sum = 0;
		for (int i = 0; i < this->M * this->N; i++)
			sum += this->matrix[i] * this->matrix[i];
		return sqrt(sum);
	}

	void Vector::Normalize()
	{
		Matrix::operator*=(1/this->GetLength());
	}

	Vector& Vector::operator=(const Matrix& other)
	{
		if (!((other.GetN()==1)||(other.GetM()==1)))
			throw MyException("Cannot copy over V#" + std::to_string(this->id) + " with M#" + std::to_string(other.GetID()));
		Matrix::operator=(other);
		return *this;
	}

	Vector& Vector::operator=(Matrix&& other)
	{
		if (!((other.GetN() == 1) || (other.GetM() == 1)))
			throw MyException("Cannot copy over V#" + std::to_string(this->id) + " with M#" + std::to_string(other.GetID()));
		Matrix::operator=(other);
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		Matrix::operator=(other);
		return *this;
	}

	Vector& Vector::operator=(Vector&& other) noexcept
	{
		Matrix::operator=(other);
		return *this;
	}

	Vector& Vector::operator*=(const Matrix& Matr)
	{
		if (!(CanMultiply(*this, Matr)))
			throw MyException("Cannot multiply V#" + std::to_string(this->id) + " and M#" + std::to_string(Matr.GetID()));
		if (!((this->M == 1) || (Matr.GetN()==1)))
			throw MyException("Cannot multiply and save V#" + std::to_string(this->id) + " and M#" + std::to_string(Matr.GetID()));
		Matrix::operator*=(Matr);
		return *this;
	}

	Vector& Vector::operator*=(const Vector& Vect)
	{
		if (!(CanMultiply(*this, Vect)))
			throw MyException("Cannot multiply V#" + std::to_string(this->id) + " and V#" + std::to_string(Vect.id));
		if (!((this->M == 1) || (Vect.GetN() == 1)))
			throw MyException("Cannot multiply and save V#" + std::to_string(this->id) + " and M#" + std::to_string(Vect.GetID()));
		Matrix::operator*=(Vect);
		return *this;
	}

	Vector& Vector::operator*=(double val)
	{
		Matrix::operator*=(val);
		return *this;
	}

	//Matrix operator*(const Matrix& Matr, const Vector& Vect)
	//{
	//	return std::move(operator*(Matr, (Matrix)Vect));// Matrix(Matr) *= Vect;//operator*(Matr,Vect);
	//}

	//Vector operator*(const Vector& Vect, const Matrix& Matr)
	//{
	//	if (!(Matrix::CanMultiply(Vect, Matr)))
	//		throw MyException("Cannot multiply V#" + std::to_string(Vect.GetID()) + " and M#" + std::to_string(Matr.GetID()));
	//	Matrix Result(Matrix(1, Vect.GetN(), Vect.GetArray()) * Matr);
	//	return Vector(Result.GetN(), Result.GetArray());
	//}

	//Vector operator*(const Vector& Vect1, const Vector& Vect2)
	//{
	//	if (!(Matrix::CanMultiply(Vect1, Vect2)))
	//		throw MyException("Cannot multiply V#" + std::to_string(Vect1.GetID()) + " and M#" + std::to_string(Vect2.GetID()));
	//	return std::move(Vector(Vect1) *= Vect2);
	//}
}
