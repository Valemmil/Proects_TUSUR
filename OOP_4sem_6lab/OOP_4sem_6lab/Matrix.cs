using System;
using System.Collections.Generic;
using System.Text;

namespace Deaglen
{


    class Matrix
    {
        public int h;
        public int l;
        public double[,] data = null;
        private static int IDS = 0;
        public int m_id;
        public Matrix()
        {
            m_id = IDS++;
            data = null;
            h = 0;
            l = 0;
            Console.WriteLine("Конструктор матрицы " + m_id);
        }

        public Matrix(int n, double[,] _data)
        {
            h = n;
            l = n;
            data = new double[h, l];
            for (int k = 0; k < n; k++)
                for (int z = 0; z < n; z++)
                    data[k, z] = _data[k, z];
            m_id = IDS++;
            Console.WriteLine("Конструктор матрицы " + m_id);
        }

        public Matrix(int _h, int _l, double[,] _data)
        {
            h = _h;
            l = _l;
            data = new double[h, l];
            for (int k = 0; k < h; k++)
                for (int z = 0; z < l; z++)
                    data[k, z] = _data[k, z];
            m_id = IDS++;
            Console.WriteLine("Конструктор матрицы " + m_id);
        }

        public Matrix Clone()
        {
            Matrix clone = new Matrix(this);

            return clone;
        }

        public Matrix(Matrix a) : this()
        {
            data = a.data;
            h = a.h;
            l = a.l;
            m_id = IDS++;
            Console.WriteLine("Конструктор матрицы " + m_id);
            //Console.WriteLine($"Конструктор класса {Id}");
        }

        public bool IsPlus(Matrix a)
        {
            if (h == a.h && l == a.l)
                return true;
            else
                return false;
        }

        public bool IsMulti(Matrix a)
        {
            if (h == a.l)
                return true;
            else
                return false;
        }

        public double MinElem()
        {
            double min = data[0, 0];
            for (int k = 0; k < h; k++)
                for (int z = 0; z < l; z++)
                    if (data[k, z] < min)
                        min = data[k, z];

            return min;
        }
        public double MaxElem()
        {
            double max = data[0, 0];
            for (int k = 0; k < h; k++)
                for (int z = 0; z < l; z++)
                    if (data[k, z] > max)
                        max = data[k, z];

            return max;
        }
        public static Matrix operator +(Matrix a, Matrix b)
        {
            if (!a.IsPlus(b))
                throw new ArgumentException("PlusError");

            double[,] newData = new double[a.h, a.l];

            for (int k = 0; k < a.h; k++)
                for (int i = 0; i < a.l; i++)
                    newData[k, i] = a.data[k, i] + b.data[k, i];

            Matrix newMatrix = new Matrix(a.h, a.l, newData);
            return newMatrix;
        }
        public static Matrix operator -(Matrix a, Matrix b)
        {
            if (!a.IsPlus(b))
                throw new ArgumentException("MinusError");

            double[,] newData = new double[a.h, a.l];

            for (int k = 0; k < a.h; k++)
                for (int i = 0; i < a.l; i++)
                    newData[k, i] = a.data[k, i] - b.data[k, i];

            Matrix newMatrix = new Matrix(a.h, a.l, newData);
            return newMatrix;
        }
        public static Matrix operator *(Matrix a, Matrix b)
        {
            if (!a.IsMulti(b))
                throw new ArgumentException(" * Error");

            double[,] newData = new double[a.h, b.l];

            for (int k = 0; k < a.h; k++)
            {
                for (int i = 0; i < b.l; i++)
                {
                    for (int z = 0; z < b.h; z++)
                        newData[k, i] += a.data[k, z] * b.data[z, i];
                }

            }


            Matrix newMatrix = new Matrix(a.h, a.l, newData);
            return newMatrix;
        }

        public static Matrix operator *(Matrix a, double b)
        {
            double[,] newData = new double[a.h, a.l];

            for (int k = 0; k < a.h; k++)
                for (int i = 0; i < a.l; i++)
                    newData[k, i] = a.data[k, i] * b;

            Matrix newMatrix = new Matrix(a.h, a.l, newData);
            return newMatrix;
        }

        public double this[int k, int i]
        {
            get
            {
                return data[k, i];
            }
            set
            {
                data[k, i] = value;
            }
        }

        public override string ToString()
        {
            string str = "";

            for (int k = 0; k < h; k++)
            {
                for (int i = 0; i < l; i++)
                {
                    str = str + data[k, i].ToString();
                    str += " ";
                }
                str += "\n";
            }

            return str;
        }
        ~Matrix()
        {

            Console.WriteLine("Деструктор матрицы " + m_id);
            //Console.WriteLine($"Деструктор класса {Id}");
        }

    }
}
