using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;


// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace WebCellLifeSimulationApp.Controllers
{

    [ApiController]
    [Route("[controller]")]
    public class WSSAddressController : ControllerBase
    {

        private readonly ILogger<WSSAddressController> _logger;

        public WSSAddressController(ILogger<WSSAddressController> logger)
        {
            _logger = logger;
        }

        // GET: WSSAddress/
        [HttpGet]
        public IEnumerable<string> Get()
        {
            return Enumerable.Range(1, 1).Select(index => Program.WSS.getAddress()).ToArray();
        }
    }
}
