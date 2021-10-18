using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using SimulationModelCLR;

using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System.Net;
using System.Net.WebSockets;
using System.Threading;
using System.Text;

namespace WebCellLifeSimulationApp
{
    public class WebSocketContainer
    {
        private List<WebSocket> clients;

        public WebSocketContainer()
        {
            clients = new();
            Program.simulation.addUpdateHandler(handleUpdate);
        }

        public void add (ref WebSocket socket)
        {
            clients.Add(socket);
        }

        public void delete(ref WebSocket socket)
        {
            clients.Remove(socket);
        }

        private void handleUpdate(DrawEntity[] entities)
        {
            string json_str = DrawEntitiesConverter.toJson(entities);
            byte[] bytes = Encoding.ASCII.GetBytes(json_str);
            ArraySegment<byte> buf = new ArraySegment<byte>(bytes);
            WebSocketMessageType mestype = WebSocketMessageType.Text;
            bool end = true;
            CancellationToken token = CancellationToken.None;
            foreach(WebSocket socket in clients)
            {
                socket.SendAsync(buf, mestype, end, token);
            }
        }
    }
}
