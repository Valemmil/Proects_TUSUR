using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace SocketTcpServer
{
    class Program
    {
        static int port = 8005; // порт для приема входящих запросов
        static void Main(string[] args)
        {
            // получаем адреса для запуска сокета
            IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), port);

            // создаем сокет
            Socket listenSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try {
                // связываем сокет с локальной точкой, по которой будем принимать данные
                listenSocket.Bind(ipPoint);

                // начинаем прослушивание
                listenSocket.Listen(10);

                Console.WriteLine("Сервер запущен. Ожидание подключений...");

                while (true) {
                    Socket handler = listenSocket.Accept();
                    // получаем сообщение
                    StringBuilder num1c = new StringBuilder();
                    int bytes = 0; // количество полученных байтов
                    byte[] data = new byte[1024]; // буфер для получаемых данных
                    do {
                        bytes = handler.Receive(data);
                        num1c.Append(Encoding.Unicode.GetString(data, 0, bytes));
                    } while (handler.Available > 0);

                    StringBuilder num2c = new StringBuilder();
                    do {
                        bytes = handler.Receive(data);
                        num2c.Append(Encoding.Unicode.GetString(data, 0, bytes));
                    } while (handler.Available > 0);

                    int num1 = Convert.ToInt32(num1c.ToString());
                    int num2 = Convert.ToInt32(num2c.ToString());

                    int result = num1 % num2;

                    Console.WriteLine(num1c.ToString() + " % " + num2c.ToString() + " = " + Convert.ToString(result));

                    // отправляем ответ
                    string resultc = Convert.ToString(result);
                    data = Encoding.Unicode.GetBytes(resultc);
                    handler.Send(data);
                    // закрываем сокет
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
            } catch (Exception ex) {
                Console.WriteLine(ex.Message);
            }
        }
    }
}