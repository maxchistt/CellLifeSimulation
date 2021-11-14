using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Timers;
using SimulationModelNET;

namespace WebCellLifeSimulationApp
{
    public partial class SimDrawController
    {
        public void clearCells()
        {
            simulation.clearAll();
        }
        public void generateCells(int amount)
        {
            simulation.cellFactory.generateCells(amount);
        }
        public void setGenerationType(int typeId)
        {
            simulation.cellFactory.setGenerationType(typeId);
        }
        public void setCellsReproductionLimit(int limit)
        {
            simulation.cellsLimit() = limit;
        }
        public int[] getSimulationSize()
        {
            return new int[] {
                simulation.getWidth(),
                simulation.getHeight()
            };
        }
        public void setSimulationSize(int x, int y)
        {
            simulation.setSize(x, y);
        }
    }

    public partial class SimDrawController
    {
        private SimulationNET simulation;
        private Timer timer;
        private DrawEntity[] drawEntities;
        private Action<DrawEntity[]>[] handlers;

        public SimDrawController()
        {
            simulation = new SimulationNET();
            drawEntities = new DrawEntity[0];
            handlers = new Action<DrawEntity[]>[0];
            timer = new Timer();
            timer.Elapsed += onTimerTick;
        }
        ~SimDrawController()
        {
            timer.Stop();
            timer.Close();
        }

        public void start()
        {
            timer.Start();
        }
        public void stop()
        {
            timer.Stop();
        }

        public void setTimeSettings(float simulation_timelapse, int timer_interval)
        {
            timer.Interval = timer_interval > 0 ? timer_interval : 100;
            simulation.setTimelapse(simulation_timelapse);
        }
        public void addUpdateHandler(Action<DrawEntity[]> handler)
        {
            Array.Resize(ref handlers, handlers.Length + 1);
            handlers[handlers.Length - 1] = handler;
        }

        private void onTimerTick(Object source, ElapsedEventArgs e)
        {
            updateFrame();
            foreach (Action<DrawEntity[]> handler in handlers)
            {
                handler(drawEntities);
            }
        }
        private void updateFrame()
        {
            drawEntities = simulation.getNextFrame();
        }
    }
}
