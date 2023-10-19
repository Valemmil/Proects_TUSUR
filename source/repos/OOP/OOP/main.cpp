#include <iostream>
#include "FullMatrix.h"
//#include "Vector.h"
int main()
{
    setlocale(0, "");
    try {
        double data1[2] = { 3,4 };
        double data2[2] = { 1,2 };
        double data3[4] = { 1,2,3,4 };
        tasks::Vector A(2, data1);
        tasks::Vector E(4, data3);
        A *= 2;
        tasks::Matrix P(1, 4, data3);
        tasks::Matrix C(2, 2, data3);
        tasks::Vector papados(P);
        std::cout << "A\n" << A;
        std::cout << "A^T\n" << A.TransposeCopy();
        std::cout << "A+A\n" << A+A;
        std::cout << "A-A\n" << A-A;
        std::cout << "A*A^T\n" << A*A.TransposeCopy() << "end\n";
        std::cout << "A^T*A\n" << A.TransposeCopy()*A << "end\n";
        //A.Transpose();
        std::cout << 9.0 * A;
        std::cout << E + P;
        std::cout << A + A << "õ2";
        std::cout << P * E.Transpose() << "P*E";
        std::cout << E * P << "E*P";
        //std::cout << A * C << "A*C";
        //std::cout << A * A << "A*A";
        tasks::Vector bom;
        bom = A * C;
        std::cout << "bom" << bom << "bom";
    }
    //catch (tasks::MyException& e) {
    //    std::cout << e.what();
    //}
    catch (std::exception &e) {
        std::cout << e.what();
    }
    return 0;
}
