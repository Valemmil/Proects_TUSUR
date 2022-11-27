#include <iostream>
#include "Fraction.h"
#include "Polinom.h"

using namespace std;
using namespace Fractions;

int main()
{
	Fraction test1(100, 15), test2(10, 4);

	test1.show();
	test2.show();

	(test1 + test2).show();
	(test1 - test2).show();
	(test1 * test2).show();
	(test1 / test2).show();




}
