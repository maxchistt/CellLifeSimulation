using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using SimulationModelNET;

namespace WebCellLifeSimulationApp
{
    public class DrawConverter
    {
        public static string toJson(DrawEntity[] arr)
        {
            string json_str = "{ \"frame\" : [ ";

            for (int i = 0; i < arr.Length; i++)
            {
                if (i > 0) json_str += ", ";
                json_str += "{ " +
                   "\"x\": " + arr[i].x.ToString() + ", " +
                   "\"y\": " + arr[i].y.ToString() + ", " +
                   "\"size\": " + arr[i].size.ToString() + ", " +
                   "\"color\": \"" + arr[i].color.ToString() + "\" " +
                  "}";
            }
            json_str += " ] }";
            return json_str;
        }
    }
}
