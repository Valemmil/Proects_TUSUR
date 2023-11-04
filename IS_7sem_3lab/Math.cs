using System.Numerics;

namespace RSA{

    class MathNum{

        public static long Gcd(long a, long b)
        {
            long q, r;
            long x1 = 0, x2 =1;
            long y1 = 1, y2 = 0;

            while(b > 0)
            {
                q = a / b;
                r = a - q * b;
                long x = x2 - q * x1;
                long y = y2 - q * y1;
                a = b;
                b = r;
                x2 = x1;
                x1 = x;
                y2 = y1;
                y1 = y;
            }

            return Math.Min(x2, y2);
        }

        public static BigInteger Power(BigInteger x, long n, BigInteger m) {

            if (n == 1){
                return x;
            }

            if (n % 2 == 0){
                BigInteger p = Power(x, n / 2, m) % m;
                return (p * p) % m;
            }

            return (x * Power(x, n - 1, m)) % m;
        }
    }

}