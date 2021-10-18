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
    public class SimulationController : ControllerBase
    {
        private readonly ILogger<SimulationController> _logger;

        public SimulationController(ILogger<SimulationController> logger)
        {
            _logger = logger;
        }

        // GET: api/Simulation/getSize
        [HttpGet("getSize")]
        public int[] GetSize()
        {
            return Program.simulation.getSimulationSize();
        }

        // GET api/Simulation/generateCells/5
        [HttpGet("generateCells/{id}")]
        public void generateCells(int id)
        {
            Program.simulation.generateCells(id);
        }

        // GET api/Simulation/clearCells
        [HttpGet("clearCells")]
        public void clearCells()
        {
            Program.simulation.clearCells();
        }
    }
}
