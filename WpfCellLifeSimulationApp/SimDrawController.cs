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
            setInterval(50);
            Stop();
        }

        public void setInterval(int ms)
        {
            Interval = TimeSpan.FromMilliseconds(ms);
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
        private LinegraphicWindow graphic;

        private DTimer dispatch_timer;
        private Timer simulation_timer;

        public SimDrawController(Canvas image, LinegraphicWindow graph)
        {
            frame = Array.Empty<DrawEntity>();
            simulation = new SimulationCLR();
            view = image;
            graphic = graph;
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

        public bool isrunning()
        {
            return simulation_timer.Enabled;
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
            var countsarr = new int[3] { 0, 0, 0 };

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
                    Color color = (Color)ColorConverter.ConvertFromString(item.color.Name);
                    
                    if (color == Colors.Green) { countsarr[0]++; color = (Color)ColorConverter.ConvertFromString("SeaGreen"); }
                    else if (color == Colors.Blue) { countsarr[1]++; color = (Color)ColorConverter.ConvertFromString("#FF1295D3"); }
                    else if (color == Colors.Red) { countsarr[2]++; }

                    el.Fill = new SolidColorBrush(color);
                }
                catch (Exception err)
                {
                    el.Fill = Brushes.Black;
                }

                view.Children.Add(el);
            }
            graphic.draw(countsarr);
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
