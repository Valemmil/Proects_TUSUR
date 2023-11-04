using System.Text;
using System.Numerics;
namespace RSA
{

    class MyRSA{

        static readonly Dictionary<char, int> dictEncrypt = new()
        {
            {'А', 10}, {'Б', 11}, {'В', 12}, {'Г', 13}, {'Д', 14},
            {'Е', 15}, {'Ж', 16}, {'З', 17}, {'И', 18}, {'Й', 19},
            {'К', 20}, {'Л', 21}, {'М', 22}, {'Н', 23}, {'О', 24},
            {'П', 25}, {'Р', 26}, {'С', 27}, {'Т', 28}, {'У', 29},
            {'Ф', 30}, {'Х', 31}, {'Ц', 32}, {'Ч', 33}, {'Ш', 34},
            {'Щ', 35}, {'Ъ', 36}, {'Ы', 37}, {'Ь', 38}, {'Э', 39},
            {'Ю', 40}, {'Я', 41}, {'A', 42}, {'B', 43}, {'C', 44}, 
            {'D', 45}, {'E', 46}, {'F', 47}, {'G', 48}, {'H', 49}, 
            {'I', 50}, {'J', 51}, {'K', 52}, {'L', 53}, {'M', 54}, 
            {'N', 55}, {'O', 56}, {'P', 57}, {'Q', 58}, {'R', 59}, 
            {'S', 60}, {'T', 61}, {'U', 62}, {'V', 63}, {'W', 64}, 
            {'X', 65}, {'Y', 66}, {'Z', 67}, {' ', 68}, {',', 69}, 
            {'.', 70}, {'!', 71}, {'?', 72}, {';', 73}, {':', 74}, 
            {'-', 75}, {'@', 76}, {'$', 77}, {'%', 78}, {'&', 79}, 
            {'#', 80}, {'«', 81}, {'»', 82}, {'0', 83}, {'1', 84}, 
            {'2', 85}, {'3', 86}, {'4', 87}, {'5', 88}, {'6', 89}, 
            {'7', 90}, {'8', 91}, {'9', 92}, {'\n',93}, {'\r',94},
            {'’', 95}, {'—', 96}, {'…', 97}
        };

        public static int[,] KeyGeneration(int p, int q, int e) {
        
            int N = q * p;
            int FiN = (q - 1) * (p - 1);
            Console.WriteLine($"FiN = {FiN}");
            
            long x = MathNum.Gcd(FiN, e);
            x = Math.Abs(x);

            Console.WriteLine($"x = {x}");

            int d = FiN - (int)x;
            
            return new int[,] {{e, N}, {d, N}};
        }

        static Dictionary<long, char> GetDictDecrypt(){

            Dictionary<long, char> dictDecrypt = new();

            foreach (KeyValuePair<char, int> elm in dictEncrypt){
                dictDecrypt.Add(elm.Value, elm.Key);
            }

            return dictDecrypt;
        }

        public static string Encrypt(string text,int[] key){

            BigInteger cryptedSimbol, simbol;
            int lensimbol = (int)Math.Log10(key[1]) + 1;
            StringBuilder cryptedText = new(), codedTextBuilder = new();

            foreach (char letter in text){
                try{
                    codedTextBuilder.Append(dictEncrypt[letter]);
                }
                catch{
                    codedTextBuilder.Append(dictEncrypt[' ']);
                }

            }

            string codedText = codedTextBuilder.ToString();
            int lenblock;

            for (int i = 0; i < codedText.Length; i += lenblock){
            
                lenblock = lensimbol;

                if (i + lenblock > codedText.Length){
                    lenblock = codedText.Length - i;
                }
                else{

                    simbol = Convert.ToInt64(codedText.Substring(i, lenblock));

                    if (simbol > key[1]){
                        --lenblock;
                    }

                    if (codedText[i + lenblock] == '0'){
                        --lenblock;
                    }
                }

                simbol = Convert.ToInt64(codedText.Substring(i, lenblock));
                cryptedSimbol = MathNum.Power(simbol, key[0], key[1]);
                string temp = cryptedSimbol.ToString().PadLeft(lensimbol, '0');
                cryptedText = cryptedText.Append(temp);

            }

            return cryptedText.ToString();
            
        }

        public static string Decrypt(string cryptedText, int[] key)
        {
            long simbol, cryptedSimbol;

            int lensimbol = (int)Math.Log10(key[1]) + 1;
            StringBuilder messageText = new(), codedTextBuilder = new();
            Dictionary<long, char> dictDecrypte = GetDictDecrypt();
            BigInteger bigCryptedSimbol, bigKey, bigSimbol;


            for (int i = 0; i < cryptedText.Length; i += lensimbol){
                cryptedSimbol = Convert.ToInt64(cryptedText.Substring(i, lensimbol));

                bigCryptedSimbol = new(cryptedSimbol);
                bigKey = new(key[1]);
                bigSimbol = MathNum.Power(bigCryptedSimbol, key[0], bigKey);

                codedTextBuilder = codedTextBuilder.Append(bigSimbol.ToString());                              
            }

            string codedText = codedTextBuilder.ToString();

            for (int i = 0; i < codedText.Length; i += 2){
                simbol = Convert.ToInt64(codedText.Substring(i, 2));

                messageText = messageText.Append(dictDecrypte[simbol]);  
            }         

            return messageText.ToString();

        }
    }
}