using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace networkingTest
{
    class Program
    {
        private static IPAddress ipAddr = IPAddress.Parse("192.168.2.84");

        private static Socket createServer()
        {
            
            Socket server = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            return server;
        }

        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                return;   
            }
            string msg = args[0];
            int served = 0;
            IPEndPoint localPoint = new IPEndPoint(ipAddr, 240);

            Socket server = createServer();

            try
            {
                server.Bind(localPoint);
                server.Listen(10);

                while (true)
                {
                    Socket? client;
                    byte[] buffer = new Byte[256];
                    string? data = null;
                    
                    Console.WriteLine($"Clients served: {served}");
                    Console.WriteLine("Awaiting client...");

                    client = server.Accept();
                    Console.Clear();
                    Console.WriteLine("Client connected");
                    
                    while (true)
                    {
                        int bufferByte = client.Receive(buffer);
                        data += Encoding.ASCII.GetString(buffer, 0, bufferByte);

                        if (data.IndexOf("\0") > -1)
                            break;
                    }

                    Console.WriteLine($"[CLIENT]: {data}");
                    client.Send(Encoding.ASCII.GetBytes(msg));
                    Console.WriteLine($"[SERVER]: {msg}");

                    client.Shutdown(SocketShutdown.Both);
                    client.Close();
                    Console.WriteLine("Client Disconnected");
                    served++;
                }
            } catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
    }
}