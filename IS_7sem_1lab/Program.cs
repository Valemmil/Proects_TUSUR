//Класс для шифровки и дешифровки строки с помощью метода магического квадрата. Входные и выходные данные запишите в файл типа .txt 
using System.Text;

class MagicSquare {
    private static readonly int[,] magicSquare = {
        {6,  12, 25,  8, 28, 32},
        {21,  1, 31, 36, 17,  5},
        {27, 22, 35, 14,  9,  4},
        {20, 34, 15, 13, 10, 19},
        {30, 26,  3, 11, 23, 18},
        {7,  16,  2, 29, 24, 33}	
    };
    public static string EncryptMagicSquare(string Text, int length){
        // лист для зашифрованного текста
        var squareText = new List<char>();
        // вносим текст в магический квадрат
        for (int j = 0; j <= (length-1) / 36; j++) 
            foreach (int i in magicSquare)
                if ((j*36)+i <= Text.Length)
                    squareText.Add(Text[(j*36) + i-1]);
                else
                    squareText.Add(' ');

        string sSquareText = string.Join("", squareText);

        return sSquareText;
    }
    public static string DecryptMagicSquare(string Text){
        // расшифровка текста
        char[] decryptedText = new char[Text.Length];
        foreach ((int ind, char simbol) in Text.Select((item, index) => (index, item))){
            int position = magicSquare[ind % 36 / 6, ind % 36 % 6];
            decryptedText[(ind / 36 * 36) + position-1] = simbol;
        }
        string sDecryptedText = string.Join("", decryptedText);

        return sDecryptedText;
    }
    public static void Main(string[] args){

        while (true){
            Console.Write("0) Exit\n1) Encrypt\n2) Decrypt\n>");
            var control = Console.ReadLine();
            Console.WriteLine(control);

            if (control == "0"){
                break;
            }

            if (control == "1"){
                var infstream = File.OpenRead("in.txt");
                // выделяем массив для считывания данных из файла
                byte[] buffer = new byte[infstream.Length];
                // считываем данные
                infstream.Read(buffer, 0, buffer.Length);
                // декодируем байты в строку
                string textFromFile = Encoding.Default.GetString(buffer);
                // закрываем файл
                infstream.Close();

                string sSquareText = EncryptMagicSquare(textFromFile, buffer.Length);

                // вносим зашифрованный текст в файл
                File.WriteAllText("out.txt", sSquareText);
            }
            
            if (control == "2"){
                var infstream = File.OpenRead("out.txt");
                // выделяем массив для считывания данных из файла
                byte[] buffer = new byte[infstream.Length];
                // считываем данные
                infstream.Read(buffer, 0, buffer.Length);
                // декодируем байты в строку
                string textFromFile = Encoding.Default.GetString(buffer);
                // закрываем файл
                infstream.Close();

                string sDecryptedText = DecryptMagicSquare(textFromFile);

                File.WriteAllText(@"result.txt", sDecryptedText);
            }

        }
    }
}