using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Timers;
using System.Windows.Media;

using System.Windows.Shapes;

using System.Windows.Threading;

using SimulationModelCLR;

namespace WpfCellLifeSimulationApp
{
    class DTimer : DispatcherTimer
    {
        public DTimer()
        {
            Interval = new TimeSpan(0, 0, 0, 0, 100);
            Stop();
        }

        public void setInterval(int ms)
        {
            Interval = new TimeSpan(0, 0, 0, 0, ms);
        }

        public void addHandler(Action handler)
        {
            Tick += new EventHandler((object sender, EventArgs e) =>
            {
                handler();
            });
        }
    }

    public partial class SimDrawController
    {
        private SimulationCLR simulation;
        private DrawEntity[] frame;
        private Canvas view;

        private DTimer dispatch_timer;
        private Timer simulation_timer;

        public SimDrawController(Canvas image)
        {
            frame = Array.Empty<DrawEntity>();
            simulation = new SimulationCLR();
            view = image;
            simulation.setSize((int)view.Width, (int)view.Height);
            dispatch_timer = new DTimer();
            dispatch_timer.addHandler(onDispatchTimerTick);
            simulation_timer = new Timer();
            simulation_timer.Elapsed += nextFrameTimerHandler;
            setDispatchTimerInterval(30);
            setTimeSettings(30, 30);
        }
        ~SimDrawController()
        {
            stop();
        }

        public void start()
        {
            dispatch_timer.Start();
            simulation_timer.Start();
        }
        public void stop()
        {
            simulation_timer.Stop();
            dispatch_timer.Stop();
        }

        public void setTimeSettings(float simulation_timelapse, int timer_interval)
        {
            simulation_timer.Interval = timer_interval > 0 ? timer_interval : 100;
            simulation.setTimelapse(simulation_timelapse);
        }

        public void setDispatchTimerInterval(int timer_interval)
        {
            dispatch_timer.setInterval(timer_interval > 0 ? timer_interval : 100);
        }

        private void nextFrameTimerHandler(Object source, ElapsedEventArgs e)
        {
            frame = simulation.getNextFrame();
        }

        private void onDispatchTimerTick()
        {
            view.Children.Clear();
            foreach (var item in this.frame)
            {
                Ellipse el = new Ellipse();
                el.Width = item.size;
                el.Height = item.size;
                double x = item.x - el.Width / 2;
                double y = item.y - el.Height / 2;
                el.Margin = new Thickness(x, y, 0, 0);
                try
                {
                    el.Fill = new SolidColorBrush((Color)ColorConverter.ConvertFromString(item.color.Name));
                }
                catch (Exception err)
                {
                    el.Fill = Brushes.Black;
                }
                
                view.Children.Add(el);
            }
        }
    };

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
    };
};
