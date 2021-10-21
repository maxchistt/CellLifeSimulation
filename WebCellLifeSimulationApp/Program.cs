using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Net;
using SimulationModelCLR;

namespace WebCellLifeSimulationApp
{
    public class Program
    {
        public static SimDrawController simulation;
        public static SocketContainer WSC;

        public static void Main(string[] args)
        {
            simulation = new SimDrawController();
            WSC = new SocketContainer();
            setupSimulation();
            CreateHostBuilder(args).Build().Run();
        }

        private static void setupSimulation()
        {
            simulation.clearCells();
            simulation.setTimeSettings(12, 50);
            simulation.setCellsReproductionLimit(300);
            simulation.setSimulationSize(400, 800);
            simulation.start();
        }

        public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
                .ConfigureWebHostDefaults(webBuilder =>
                {
                    webBuilder.UseStartup<Startup>();
                });
    }
}
