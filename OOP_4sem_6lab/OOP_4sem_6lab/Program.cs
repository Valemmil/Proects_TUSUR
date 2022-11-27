using System;


namespace Deaglen
{
    class Program
    {
        static void Main(string[] args)
        {
            
            double[,] a = new double[4, 3] { { 3, 4, 5}, { 23, 43, 55}, { 3.5, 4, 55}, { 33, 44, 5} };
            double[,] b = new double[4, 3] { { 31, 243, 45 }, { 3, 4, 535 }, { 3.5, 4, 0 }, { 3, 9, 1 } };

            Matrix A = new Matrix(4, 3, a);
            Matrix B = new Matrix(4, 3, b);
            Console.WriteLine(" ");
            Console.WriteLine(A);
            Console.WriteLine(" ");
            Console.WriteLine(B);

            Matrix C = new Matrix();
            C = A + B;
            Console.WriteLine(" ");
            Console.WriteLine(C);


            double[,] c1 = new double[3, 4] { { 3, 10, 0, 0 }, { 3, 4, 5, 1 }, { 0, 4, 5, 1 } };
            Matrix C1 = new Matrix(3, 4, c1);
            C = A * C1;
            Console.WriteLine(" ");
            Console.WriteLine(C);

        }
    }
}
