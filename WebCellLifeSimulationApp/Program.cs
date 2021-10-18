using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Net;

namespace WebCellLifeSimulationApp
{
    public class Program
    {
        public static SimulationModelController simulation;
        public static WebSocketServer WSS;
        public static bool PROD = false;

        public static void Main(string[] args)
        {
            prepare();
            CreateHostBuilder(args).Build().Run();
        }

        public static void startWSS()
        {
            WSS.start();
        }

        private static void prepare()
        {
            simulation = new SimulationModelController();
            WSS = new WebSocketServer();
            setupSimulation();
            simulation.addUpdateHandler(WSS.sendUpdate);
        }

        private static void setupSimulation()
        {
            simulation.clearCells();
            simulation.setTimeSettings(10, 100);
            simulation.setCellsReproductionLimit(300);
            simulation.setSimulationSize(600, 800);
            simulation.generateCells(20);
            simulation.start();
        }

        [Obsolete]
        public static string getIp()
        {
            string Host = Dns.GetHostName();
            IPAddress[] IPlist = Dns.GetHostByName(Host).AddressList;
            string IP = IPlist[1].ToString();
            return PROD ? IP : "localhost";
        }

        public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
                .ConfigureWebHostDefaults(webBuilder =>
                {
                    webBuilder.UseStartup<Startup>();
                });
    }
}
