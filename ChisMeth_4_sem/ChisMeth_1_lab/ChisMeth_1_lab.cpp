#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <math.h>
#include <algorithm>
#include "PolStr.h"

using namespace std;

double dichotomyMetod(double a, double b, double eps, char* nStr) {
	double x;
	x = 0;
	while (((b - a) / 2) > eps) {
		x = (a + b) / 2;
		if ((EvalPolStr(nStr, a, 0) * EvalPolStr(nStr, x, 0)) > 0) a = x;
		else b = x;
	}

	fstream fout("output.txt");
	fout << x << endl << EvalPolStr(nStr, x, 0) << endl << (a + b) / 2;
	fout.close();
	return x;
}
int main() {
	ifstream fin("input.txt");
	if (!fin.is_open())
		cout << "Ошибка файла" << endl;
	double a, b, eps;
	int control;
	char* str = new char[100];
	fin >> control >> str >> a >> b >> eps;
	fin.close();
	char* nStr = CreatePolStr(str, 0);
	switch (control)
	{
	case 1:
		dichotomyMetod(a, b, eps, nStr);
		break;
	default:
		break;
	}
	return 0;
}