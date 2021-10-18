using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WatsonWebsocket;
using SimulationModelCLR;

namespace WebCellLifeSimulationApp
{
    public class WebSocketServer
    {
        private List<string> clients;
        private WatsonWsServer server;
        private string socketAddress;

        public WebSocketServer()
        {
            clients = new();
            server = new();
        }

        private void setup()
        {
            int PORT = 9000;
            string IP = Program.getIp();
            clients = new List<string>();
            server = new WatsonWsServer(IP, PORT);
            server.ClientConnected += ClientConnected;
            server.ClientDisconnected += ClientDisconnected;
            socketAddress = "ws://" + IP + ":" + PORT.ToString() + "/";
        }

        public void start()
        {
            setup();
            server.Start();
        }

        public string getAddress()
        {
            return socketAddress;
        }

        public void sendUpdate(DrawEntity[] entities)
        {
            string json_str = DrawEntitiesConverter.toJson(entities);

            clients.ForEach((string ipPort) =>
            {
                server.SendAsync(ipPort, json_str);
            });
        }

        private void ClientConnected(object sender, ClientConnectedEventArgs args)
        {
            Console.WriteLine("Client connected: " + args.IpPort);
            clients.Add(args.IpPort);
        }

        private void ClientDisconnected(object sender, ClientDisconnectedEventArgs args)
        {
            Console.WriteLine("Client disconnected: " + args.IpPort);
            clients.Remove(args.IpPort);
        }

    }
}
