#include <iostream>
#include <iomanip>
#include <fstream>
#include "matrix.h"

using namespace std;
using namespace tasks;

Matrix SL_Gauss(Matrix a, Matrix b, ostream& os = cout)
{
    int  r;
    double M, max, s;
    Matrix x(a.GetM(), 1);
    for (int k = 0; k < a.GetM(); k++)
    {
        max = abs(a[k][k]);
        r = k;
        for (int i = k + 1; i < a.GetM(); i++)
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                r = i;
            }
        for (int j = 0; j < a.GetM(); j++)
            swap(a[k][j], a[r][j]);
        swap(b[k][0], b[r][0]);

        for (int i = k + 1; i < a.GetM(); i++)
        {
            M = a[i][k] / a[k][k];
            for (int j = k; j < a.GetM(); j++)
            {
                a[i][j] -= M * a[k][j];
            }
            b[i][0] -= M * b[k][0];
        }

    }
    if (a[a.GetM() - 1][a.GetM() - 1] == 0)
        if (b[a.GetM() - 1][0] == 0)
            return-1;
        else return-2;
    else
    {
        for (int i = a.GetM() - 1; i >= 0; i--) {
            s = 0;
            for (int j = i + 1; j < a.GetM(); j++)
                s += a[i][j] * x[j][0];
            x[i][0] = (b[i][0] - s) / a[i][i];
        }
        return x;
    }
}

int INVERSE(Matrix& A, Matrix& y, ostream& os = cout) {
    int i, j, res = 0;
    Matrix b(A.GetM(), 1), x(A.GetM(), 1);
    for (i = 0; i < A.GetM(); i++)
    {
        for (j = 0; j < A.GetM(); j++)
            if (j == i)
                b[j][0] = 1;
            else b[j][0] = 0;
        x = SL_Gauss(A, b, os);
        for (j = 0; j < A.GetM(); j++)
        {
            y[j][i] = x[j][0];
        }
    }
    return 0;
}

double det(Matrix& A) {
    int r;
    double c, M, max, det = 1;
    Matrix a(A.GetM(), A.GetM());

    for (int i = 0; i < A.GetM(); i++)
        for (int j = 0; j < A.GetM(); j++)
            a[i][j] = A[i][j];
    for (int k = 0; k < A.GetM(); k++)
    {
        max = abs(a[k][k]);
        r = k;
        for (int i = k + 1; i < A.GetM(); i++)
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);  r = i;
            }
        if (r != k) det = -det;
        for (int j = 0; j < A.GetM(); j++)
        {
            c = a[k][j];
            a[k][j] = a[r][j];
            a[r][j] = c;
        }

        for (int i = k + 1; i < A.GetM(); i++)
        {
            M = a[i][k] / a[k][k];
            for (int j = k; j < A.GetM(); j++)
                a[i][j] -= M * a[k][j];
        }
    }
    for (int i = 0; i < A.GetM(); i++)
        det *= a[i][i];
    return det;
}

double norm_e(Matrix& e)
{
    double sum = 0;
    for (int i = 0; i < e.GetM(); i++)
    {
        for (int j = 0; j < e.GetN(); j++)
        {
            sum += e.Get_unsafe(i, j) * e.Get_unsafe(i, j);
        }
    }
    return sqrt(sum);
}

int main()
{
    int N;
    ifstream in("in.txt");
    in >> N;
    if (N < 0) { N *= -1; }
    Matrix a(N, N), b(N, N), x(N, 1), res(N, 1);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            in >> a[i][j];
        in >> x[i][0];
    }
        
    in.close();
    ofstream out("out.txt");
    Matrix a1(a);
    out << "A:\n" << a << "\n";
    out << "X:\n" << x << "\n";

    out << "Method Gauss" << endl;
    res = SL_Gauss(a, x, out);
    out << "X:\n" << res << "\n";
    out << "determinant: " << det(a) << scientific << setprecision(3) << endl << endl;

    out << "Vector eps:" << endl;
    Matrix eps1 = a * res - x;
    out << eps1 << endl;
    out << "Norm vector eps: " << norm_e(eps1) << endl << endl;

    INVERSE(a1, b, out);
    out << "Inverse matrix:\n" << b << "\n";

    Matrix E(a.GetM(), b.GetN());
    for (int i = 0; i < a.GetM(); i++)
        for (int j = 0; j < b.GetN(); j++) {
            E[i][j] = 0;
            if (i == j)
                E[i][j] = 1;
        }

    out << "Matrix eps:" << endl;
    Matrix eps2(a.GetM(), b.GetN());
    //eps2 = a * b - E;
    for (int i = 0; i < a.GetM(); i++)
        for (int j = 0; j < b.GetN(); j++) {
            double sum = 0;
            for (int k = 0; k < a.GetN(); k++)
                sum += a[i][k] * b[k][j];
            eps2[i][j] = sum - E[i][j];
        }
    //eps2[0][0]--;
    out << eps2 << endl;
    out << "Norm matrix eps: " << norm_e(eps2) << endl << endl;


    
    out.close();
    return 0;
}