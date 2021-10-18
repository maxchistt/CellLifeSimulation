using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebCellLifeSimulationApp
{
    public class Program
    {
        public static SimulationModelController simulation;

        public static void Main(string[] args)
        {
            setupSimulation();
            CreateHostBuilder(args).Build().Run();
        }

        public static void setupSimulation()
        {
            simulation = new SimulationModelController();
            simulation.setTimeSettings(10, 100);
            simulation.setCellsReproductionLimit(300);
            simulation.setSimulationSize(600, 800);
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
