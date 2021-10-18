using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using System.Text.Json;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace WebCellLifeSimulationApp.Controllers
{

    [ApiController]
    [Route("api/[controller]")]
    public class WSSAddressController : ControllerBase
    {

        private readonly ILogger<WSSAddressController> _logger;

        public WSSAddressController(ILogger<WSSAddressController> logger)
        {
            _logger = logger;
        }

        // GET: api/WSSAddress/getWSSAddress
        [HttpGet("getWSSAddress")]
        public string Get()
        {
            return JsonSerializer.Serialize(Program.WSS.getAddress());
        }
    }
}
