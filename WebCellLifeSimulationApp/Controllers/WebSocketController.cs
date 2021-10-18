using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

using System.Net;
using System.Net.WebSockets;
using System.Threading;
using System.Text;

using SimulationModelCLR;

namespace WebCellLifeSimulationApp.Controllers
{
    #region snippet
    public class WebSocketController : ControllerBase
    {
        // GET: wsserver/getConnections
        [HttpGet("wsserver/getConnections")]
        public int GetConnections()
        {
            return Program.WSC.size();
        }

        [HttpGet("/ws")]
        public async Task Get()
        {
            if (HttpContext.WebSockets.IsWebSocketRequest)
            {
                using WebSocket webSocket = await HttpContext.WebSockets.AcceptWebSocketAsync();
                await Echo(HttpContext, webSocket);
            }
            else
            {
                HttpContext.Response.StatusCode = (int)HttpStatusCode.BadRequest;
            }
        }
        #endregion

        private async Task Echo(HttpContext context, WebSocket webSocket)
        {
            Program.WSC.add(ref webSocket);
            var buffer = new byte[1024 * 4];
            WebSocketReceiveResult result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            while (!result.CloseStatus.HasValue)
            {
                await webSocket.SendAsync(new ArraySegment<byte>(buffer, 0, result.Count), result.MessageType, result.EndOfMessage, CancellationToken.None);
                result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            }
            await webSocket.CloseAsync(result.CloseStatus.Value, result.CloseStatusDescription, CancellationToken.None);
            Program.WSC.delete(ref webSocket);
        }

    }
}