using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using SimulationModelNET;

using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System.Net;
using System.Net.WebSockets;
using System.Threading;
using System.Text;

namespace WebCellLifeSimulationApp
{
    public class SocketProcessor
    {
        private List<WebSocket> clients;

        public int connectionsCount()
        {
            return clients.Count();
        }

        public SocketProcessor()
        {
            clients = new();
            Program.simulation.addUpdateHandler(handleSimulationUpdate);
        }

        public async void AddSocket(WebSocket webSocket, TaskCompletionSource<object> socketFinishedTcs)
        {
            clients.Add(webSocket);

            await processSocketConnection(webSocket);

            clients.Remove(webSocket);

            socketFinishedTcs.TrySetResult(null);
        }

        private async Task processSocketConnection(WebSocket webSocket)
        {
            var buffer = new byte[1024 * 4];
            WebSocketReceiveResult result = null;
            while (result == null || !result.CloseStatus.HasValue)
            {
                result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            }
            await webSocket.CloseAsync(result.CloseStatus.Value, result.CloseStatusDescription, CancellationToken.None);
        }

        private void handleSimulationUpdate(DrawEntity[] entities)
        {
            string json_str = DrawConverter.toJson(entities);
            byte[] bytes = Encoding.ASCII.GetBytes(json_str);
            ArraySegment<byte> buf = new ArraySegment<byte>(bytes);
            WebSocketMessageType mestype = WebSocketMessageType.Text;
            bool end = true;
            CancellationToken token = CancellationToken.None;
            foreach (WebSocket socket in clients.ToArray())
            {
                socket.SendAsync(buf, mestype, end, token);
            }
        }
    }
}
