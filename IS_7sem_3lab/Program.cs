using System.Text;

namespace RSA
{

    class Program{

        static void Main(){
            Console.WriteLine("Алгорит шифрования RSA");
            int p = 2339, q = 1667, e = 5;

            int[,] keys = MyRSA.KeyGeneration(p, q, e);

            Console.WriteLine("Public Key: {0}:{1}\nPrivate Key: {2}:{3}", keys[0,0], keys[0,1], keys[1,0], keys[1,1]);
            int[] publicKeyRSA = new int[] {keys[0,0], keys[0,1]};
            int[] privateKeyRSA = new int[] {keys[1,0], keys[1,1]};
            

            string pathMessage = "message.txt";
            string pathCrypted = "crypted.txt";


            while(true){
                Console.Write("\n1) Шифровка\n2) Дешифровка\n>");
                string? control = 
                // "2";
                Console.ReadLine();

                if (control == ""){
                    break;
                }

                if (control == "1"){
                    string textMessage = File.ReadAllText(pathMessage).ToUpper();
                    string textCrypted = MyRSA.Encrypt(textMessage, publicKeyRSA);
                    string bs64 = Convert.ToBase64String(Encoding.UTF8.GetBytes(textCrypted));
                    File.WriteAllText(pathCrypted, bs64);
                }

                if (control == "2"){
                    string bs64 = File.ReadAllText(pathCrypted);
                    string textCrypted = Encoding.UTF8.GetString(Convert.FromBase64String(bs64));
                    string textMessage = MyRSA.Decrypt(textCrypted, privateKeyRSA);
                    File.WriteAllText(pathMessage, textMessage);
                }

            }


        }

    }

}