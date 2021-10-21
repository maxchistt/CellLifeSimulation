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
    public class SocketContainer
    {
        private List<WebSocket> clients;

        public int connectionsCount()
        {
            return clients.Count();
        }

        public SocketContainer()
        {
            clients = new();
            Program.simulation.addUpdateHandler(handleSimulationUpdate);
        }

        public async Task handleSocketConnection(WebSocket webSocket)
        {
            add(ref webSocket);
            var buffer = new byte[1024 * 4];
            WebSocketReceiveResult result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            while (!result.CloseStatus.HasValue)
            {
                await webSocket.SendAsync(new ArraySegment<byte>(buffer, 0, result.Count), result.MessageType, result.EndOfMessage, CancellationToken.None);
                result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            }
            await webSocket.CloseAsync(result.CloseStatus.Value, result.CloseStatusDescription, CancellationToken.None);
            delete(ref webSocket);
        }

        private void add(ref WebSocket socket)
        {
            clients.Add(socket);
        }

        private void delete(ref WebSocket socket)
        {
            clients.Remove(socket);
        }

        private void handleSimulationUpdate(DrawEntity[] entities)
        {
            string json_str = DrawConverter.toJson(entities);
            byte[] bytes = Encoding.ASCII.GetBytes(json_str);
            ArraySegment<byte> buf = new ArraySegment<byte>(bytes);
            WebSocketMessageType mestype = WebSocketMessageType.Text;
            bool end = true;
            CancellationToken token = CancellationToken.None;
            foreach (WebSocket socket in clients)
            {
                socket.SendAsync(buf, mestype, end, token);
            }
        }
    }
}
