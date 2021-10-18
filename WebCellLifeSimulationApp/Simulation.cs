using System;
using System.Collections.Generic;
using System.Linq;
using System.Timers;
using System.Threading.Tasks;
using SimulationModelCLR;

namespace WebCellLifeSimulationApp
{
    public class SimulationModel
    {
        private SimulationCLR simulation;

        protected SimulationModel()
        {
            simulation = new SimulationCLR();
        }

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

        protected void setTimelapse(float simulation_timelapse)
        {
            simulation.setTimelapse(simulation_timelapse);
        }
        protected DrawEntity[] getNextFrame()
        {
            return simulation.getNextFrame();
        }
    }

    public class SimulationModelController : SimulationModel
    {
        private Timer timer;
        private DrawEntity[] drawEntities;
        private Action[] handlers;

        public SimulationModelController() : base()
        {
            drawEntities = new DrawEntity[0];
            handlers = new Action[0];
            timer = new Timer();
            timer.Elapsed += onTimerTick;
        }
        ~SimulationModelController()
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
            base.setTimelapse(simulation_timelapse);
        }
        public void addUpdateHandler(Action handler)
        {
            Array.Resize(ref handlers, handlers.Length + 1);
            handlers[handlers.Length - 1] = handler;
        }

        private void onTimerTick(Object source, ElapsedEventArgs e)
        {
            updateFrame();
            foreach (Action handler in handlers)
            {
                handler();
            }
        }
        private void updateFrame()
        {
            drawEntities = base.getNextFrame();
        }
    }
}
