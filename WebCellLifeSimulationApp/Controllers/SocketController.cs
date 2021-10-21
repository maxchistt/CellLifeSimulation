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
    public class SocketController : ControllerBase
    {
        // GET: ws/getConnections
        [HttpGet("ws/getConnections")]
        public int GetConnections()
        {
            return Program.WSC.connectionsCount();
        }

        // ws://[hostname]:[port]/ws
        [HttpGet("/ws")]
        public async Task Get()
        {
            if (HttpContext.WebSockets.IsWebSocketRequest)
            {
                using WebSocket webSocket = await HttpContext.WebSockets.AcceptWebSocketAsync();
                await Program.WSC.handleSocketConnection(webSocket);
            }
            else
            {
                HttpContext.Response.StatusCode = (int)HttpStatusCode.BadRequest;
            }
        }
        #endregion
    }
}