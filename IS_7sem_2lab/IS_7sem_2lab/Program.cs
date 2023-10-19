namespace AES3
{
    class Program
    {
        static void Main(string[] args)
        {
            string PathKey = "key.txt";
            string PathMassage = "message.txt";
            string PathOut = "crypted.txt";

            Console.Write("0) Шифрование\n1) Дешифрование\n\n>");
            string? control = Console.ReadLine();

            FileInfo fileKey = new(PathKey);
            FileInfo fileMessage = new(PathMassage);
            FileInfo fileCrypted = new(PathOut);
            byte[] messageByte = Array.Empty<byte>(), 
                   keyByte = Array.Empty<byte>(),
                   cryptedByte = Array.Empty<byte>();

            switch (control)
            {
                case "0":
                {
                    try
                    {
                        //ЧТЕНИЕ
                        BinaryReader keyStream = new(File.Open(PathKey, FileMode.Open));
                        keyByte = new byte[(int)fileKey.Length];
                        keyStream.Read(keyByte, 0, (int)fileKey.Length);

                        BinaryReader messageStream = new(File.Open(PathMassage, FileMode.Open));
                        messageByte = new byte[(int)fileMessage.Length];
                        messageStream.Read(messageByte, 0, (int)fileMessage.Length);
                    }
                    catch (Exception e)
                    {
                        Console.Clear();
                        Console.WriteLine("Error of reading files\n: {0}", e.Message);
                    }
                    //ШИФРОВАНИЕ
                    if (messageByte != null && keyByte != null)
                    {
                        var chiperByte = MyAES.Encrypt(messageByte, keyByte);
                        File.WriteAllBytes(PathOut, chiperByte);
                        Console.WriteLine("File was encrypted successfull!");
                    }
                    break;
                }
                case "1":
                {
                    try
                    {
                        //ЧТЕНИЕ
                        BinaryReader keyStream = new(File.Open(PathKey, FileMode.Open));
                        keyByte = new byte[(int) fileKey.Length];
                        keyStream.Read(keyByte, 0, (int) fileKey.Length);

                        BinaryReader cryptedStream = new(File.Open(PathOut, FileMode.Open));
                        cryptedByte = new byte[(int) fileCrypted.Length];
                        cryptedStream.Read(cryptedByte, 0, (int) fileCrypted.Length);
                    }
                    catch (Exception e)
                    {
                        Console.Clear();
                        Console.WriteLine("Error of reading files\n: {0}", e.Message);
                    }
                    //ДЕШИФРОВАНИЕ
                    if (cryptedByte != null && keyByte != null)
                    {
                        var chiperByte = MyAES.Decrypt(cryptedByte, keyByte);
                        File.WriteAllBytes(PathMassage, chiperByte);
                        Console.WriteLine("File was decrypted successfull!");
                    }
                    break;
                }
            }
        }
    }
}