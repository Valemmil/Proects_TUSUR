#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "matrix.h"

using namespace tasks;

using namespace std;
using namespace tasks;

void Decompose(const Matrix& A, Matrix& B, Matrix& C)
{
	int size = A.GetM();
	if (A.GetN() != size)
	{
		cout << "Îøèáêà: èñõîäíàÿ ìàòðèöà íå êâàäðàòíàÿ\n";
		exit(-2);
	}
	for (int j = 0; j < size; j++)
	{
		for (int i = j; i < size; i++)
		{
			double sum = 0;
			for (int k = 0; k < j; k++)
				sum += B.Get_unsafe(i,k) * C.Get_unsafe(k,j);
			B.Get_unsafe(i,j) = A.Get_unsafe(i,j) - sum;
		}
		for (int i = j + 1; i < size; i++)
		{
			double sum = 0;
			for (int k = 0; k < j; k++)
				sum += B.Get_unsafe(j,k) * C.Get_unsafe(k,i);
			if (B.Get_unsafe(j,j) == 0.0)
				cout << "\t\t\tÄÅËÅÍÈÅ ÍÀ ÍÓËÜ\n";
			C.Get_unsafe(j,i) = (A.Get_unsafe(j,i) - sum) / B.Get_unsafe(j,j);
		}
	}
	C.Ones(); // Åäèíèöû íà ãëàâíóþ äèàãîíàëü
}

double Determinant(const Matrix& B)
{
	double mul = 1;
	for (int i = 0; i < B.GetM(); i++)
		mul *= B.Get_unsafe(i,i);
	return mul;
}

void Vectorize(const Matrix& b, Matrix& x, Matrix& y, const Matrix& B, const Matrix& C)
{
	int size = b.GetM();
	for (int i = 0; i < size; i++)
	{
		double sum = 0;
		for (int k = 0; k <= i - 1; k++)
			sum += B.Get_unsafe(i,k) * y.Get_unsafe(k);
		if (B.Get_unsafe(i,i) == 0.0)
			cout << "\t\t\tÄÅËÅÍÈÅ ÍÀ ÍÓËÜ\n";
		y.Get_unsafe(i) = (b.Get_unsafe(i) - sum) / B.Get_unsafe(i,i);
	}
	for (int i = size - 1; i >= 0; i--)
	{
		double sum = 0;
		for (int k = i + 1; k < size; k++)
			sum += C.Get_unsafe(i,k) * x.Get_unsafe(k);
		x.Get_unsafe(i) = y.Get_unsafe(i) - sum;
	}
}

double Norm(const Matrix& m)
{
	double sum = 0;
	for (int i = 0; i < m.GetM(); i++)
	{
		for (int j = 0; j < m.GetN(); j++)
		{
			sum += m.Get_unsafe(i, j) * m.Get_unsafe(i, j);
		}
	}
	return sqrt(sum);
}

double determinant(const Matrix& m, int sx = 0, vector<int> skx = vector<int>(), int ex = -1, int sy = 0, int sky = -1, int ey = -1)
{
	if (m.GetM() != m.GetN())
	{
		cout << "Matrix is not square\n";
		return 0;
	}
	if ((ex == -1) || (ey == -1))
		ex = ey = m.GetM();
	double sum = 0, sign = 1;
	auto val = std::find(skx.begin(), skx.end(), sx);
	while (val != skx.end())
	{
		skx.erase(val);
		sx++;
		val = std::find(skx.begin(), skx.end(), sx);
	} 
	val = std::find(skx.begin(), skx.end(), ex-1);
	while (val != skx.end())
	{
		skx.erase(val);
		ex--;
		val = std::find(skx.begin(), skx.end(), ex-1);
	}
	for (int i = sx; (i < ex) && (ex-sx)>0; i++)
	{
		if (std::find(skx.begin(), skx.end(), i) != skx.end())
			continue;
		auto val = skx.emplace(skx.end(), i);
		if (sy == ey - 1 || sx == ex - 1)
			sum += m.Get_unsafe(sy, i);
		else
			sum += m.Get_unsafe(sy, i) * determinant(m, sx, skx, ex, sy+1, sky, ey) * sign;
		cout << sy << " " << i << ":" << sum << endl;
		skx.erase(val);
		sign = -sign;
	}
	return sum;
}

Matrix Iterate(const Matrix& A, const Matrix& b, double eps, ofstream& cout)
{
	int size = A.GetM();
	Matrix beta(size, 1), xk, xk_1;
	Matrix alpha(size);
	double a_norm;
	for (int i = 0; i < size; i++)
	{
		beta.Get_unsafe(i) = b.Get_unsafe(i) / A.Get_unsafe(i, i);
		for (int j = 0; j < size; j++)
		{
			if (j == i)
				continue;
			alpha.Get_unsafe(i, j) = -A.Get_unsafe(i, j) / A.Get_unsafe(i, i);
		}
	}
	cout << "alpha:\n"; cout.width(14); cout << alpha << '\n';
	cout << "beta:\n" << beta << '\n';
	a_norm = Norm(alpha);
	a_norm = fabs(1 - a_norm) / a_norm * eps;
	xk_1 = beta;
	do {
		xk = move(xk_1);
		xk_1 = beta + alpha * xk;
	} while (Norm(xk_1 - xk) >= a_norm);

	return xk_1;
}

bool Check(const Matrix& A)
{
	int size = A.GetM();
	for (int i = 0; i < size; i++)
	{
		double sum = 0;
		for (int j = 0; j < size; j++)
		{
			if (j == i)
				continue;
			sum += fabs(A.Get_unsafe(i, j));
		}
		if (fabs(A.Get_unsafe(i, i)) <= sum)
			return false;
	}
	return true;
}

int main()
{
	setlocale(0, "");
	int size = 1;
	int var = 0;
	ifstream in("in.txt");
	if (!in.is_open())
	{
		cout << "Ôàéë íå íàéäåí\n";
		return 404;
	}
	in >> var;
	in >> size;
	Matrix A(size);
	Matrix b;
	if (var == 1 || var == 4)
	{
		b = move(Matrix(size, 1));
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			in >> A.Get_unsafe(i, j);
		}
		if (var == 1 || var == 4)
			in >> b.Get_unsafe(i);
		int c;
		do
		{
			c = in.get();
		} while (c != '\n' && c != EOF);
	}
	Matrix B(size), C(size);
	Decompose(A, B, C);
	//determinant(A);
	//determinant(B);
	//determinant(C);
	ofstream cout("out.txt");
	//cout << fixed;
	switch (var)
	{
	case 1:
	{
		cout << "B:\n" << B << "\n";
		cout << "C:\n" << C << "\n";
		cout << "B*C:\n" << B * C << "\n";
		cout << "ÐÅØÅÍÈÅ ÑËÀÓ\n";
		Matrix x(size, 1), y(size, 1);
		Vectorize(b, x, y, B, C);

		cout << "y:\n" << y << "\n";
		cout << "x*:\n" << x << "\n";

		Matrix eps = A * x - b;
		cout << "eps:\n" << scientific << eps << "\n";
		cout << "||eps||: " << scientific << Norm(eps);

	}
	break;
	case 2:
		cout << "B:\n" << B << "\n";
		cout << "C:\n" << C << "\n";
		cout << "B*C:\n" << B * C << "\n";
		cout << "ÎÏÐÅÄÅËÈÒÅËÜ\n";
		cout << "Det(A): " << Determinant(B) << "\n";
		break;
	case 3:
	{
		cout << "B:\n" << B << "\n";
		cout << "C:\n" << C << "\n";
		cout << "B*C:\n" << B * C << "\n";
		cout << "ÎÁÐÀÒÍÀß ÌÀÒÐÈÖÀ\n";
		Matrix A_1(size);
		A_1.Ones();
		Matrix x(size, 1), temp(size, 1);
		for (int i = 0; i < size; i++)
		{
			Matrix y(size, 1, A_1.GetRow(i));
			Vectorize(y, x, temp, B, C);
			cout << "y" << i + 1 << ":\n" << temp << '\n';
			for (int j = 0; j < size; j++)
			{
				A_1.Get_unsafe(i, j) = x.Get_unsafe(j);
			}
		}
		A_1.Transpose();
		cout << "X:\n"; cout.width(14); cout << A_1 << "\n";
		Matrix eps = A * A_1 - Matrix(size).Ones();
		cout << "eps:\n" << scientific; cout.width(14); cout << eps << "\n";
		cout << "||eps||: " << scientific << Norm(eps) << endl;
	}
	break;
	case 4:
	{
		cout << "ÐÅØÅÍÈÅ ÑËÀÓ (ÈÒÅÐÀÖÈÈ)\n";
		if (Check(A))
		{
			Matrix x = Iterate(A, b, 0.000001, cout);
			cout << "x*:\n" << x;
			Matrix eps = A * x - b;
			cout << "eps:\n" << scientific << eps << "\n";
			cout << "||eps||: " << scientific << Norm(eps) << endl;
		}
		else
		{
			cout << "ÍÅ ÑÕÎÄÈÒÑß\n";
		}
		break;
	}
	case 5:
	{
		cout << "ÎÁÐÀÒÍÀß ÌÀÒÐÈÖÀ (ÈÒÅÐÀÖÈÈ)\n";
		if (Check(A))
		{
			Matrix A_1(size);
			A_1.Ones();
			for (int i = 0; i < size; i++)
			{
				cout << "Iteration " << i + 1 << ":\n";
				Matrix y(size, 1, A_1.GetRow(i));
				Matrix x = Iterate(A, y, 0.000001, cout);
				for (int j = 0; j < size; j++)
					A_1.Get_unsafe(i, j) = x.Get_unsafe(j);
			}
			A_1.Transpose();
			cout << "X:\n"; cout.width(14); cout << A_1 << "\n";
			Matrix eps = A * A_1 - Matrix(size).Ones();
			cout << "eps:\n" << scientific; cout.width(14); cout << eps << "\n";
			cout << "||eps||: " << scientific << Norm(eps) << endl;
		}
		else
		{
			cout << "ÍÅ ÑÕÎÄÈÒÑß\n";
		}
	}
	break;
	default:
		break;
	}
	cout.close();
	//system("out.txt");
	//system("PAUSE");
	return 0;
}