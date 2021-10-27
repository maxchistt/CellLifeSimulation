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
    public partial class SimDrawController
    {
        private SimulationCLR simulation;
        private DrawEntity[] frame;
        private Canvas view = null;
        private LinegraphicWindow graphic = null;

        private DispatcherTimer dispatch_timer_image;
        private DispatcherTimer dispatch_timer_chart;
        private Timer simulation_timer;

        private Brush[] brushes;

        public SimDrawController()
        {
            simulation = new SimulationCLR();
            frame = Array.Empty<DrawEntity>();
            brushes = new Brush[3] {
                new SolidColorBrush((Color)ColorConverter.ConvertFromString("SeaGreen")),
                new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF1295D3")),
                new SolidColorBrush((Color)ColorConverter.ConvertFromString("Red"))
            };

            dispatch_timer_image = new DispatcherTimer(System.Windows.Threading.DispatcherPriority.Normal);
            dispatch_timer_image.Tick += new EventHandler(onDispatchTimerImageTick);
            dispatch_timer_chart = new DispatcherTimer(System.Windows.Threading.DispatcherPriority.SystemIdle);
            dispatch_timer_chart.Tick += new EventHandler(onDispatchTimerChartTick);
            simulation_timer = new Timer();
            simulation_timer.Elapsed += new ElapsedEventHandler(onNextFrameTimerTick);
            setTimeSettings(30, 30, 30);
            stop();
        }

        public SimDrawController(Canvas canvas, LinegraphicWindow graphic) : this()
        {
            setImage(canvas);
            setGraph(graphic);
        }

        ~SimDrawController()
        {
            stop();
        }

        public void setSize(int w, int h)
        {
            simulation.setSize(w, h);
        }

        public void setImage(Canvas image)
        {
            if (view != image)
            {
                view = image;
                view.SizeChanged += new SizeChangedEventHandler((object sender, SizeChangedEventArgs e) =>
                {
                    setSize((int)e.NewSize.Width, (int)e.NewSize.Height);
                });
            }
        }

        public void setGraph(LinegraphicWindow graphic)
        {
            this.graphic = graphic;
        }

        public bool isrunning()
        {
            return simulation_timer.Enabled;
        }

        public void start()
        {
            dispatch_timer_image.Start();
            dispatch_timer_chart.Start();
            simulation_timer.Start();
        }
        public void stop()
        {
            simulation_timer.Stop();
            dispatch_timer_chart.Stop();
            dispatch_timer_image.Stop();
        }

        public void setTimeSettings(float simulation_timelapse, int timer_interval, int dispatch_timer_interval)
        {
            simulation_timer.Interval = timer_interval > 0 ? timer_interval : 100;
            simulation.setTimelapse(simulation_timelapse);
            dispatch_timer_chart.Interval = TimeSpan.FromMilliseconds(dispatch_timer_interval > 0 ? dispatch_timer_interval : 100);
            dispatch_timer_image.Interval = TimeSpan.FromMilliseconds(dispatch_timer_interval > 0 ? dispatch_timer_interval : 100);
        }

        private void onNextFrameTimerTick(Object source, ElapsedEventArgs e)
        {
            frame = simulation.getNextFrame();
        }

        private void onDispatchTimerImageTick(object sender, EventArgs e)
        {
            if (view != null)
            {
                view.Visibility = Visibility.Hidden;
                view.Children.Clear();
                foreach (var item in this.frame)
                {
                    Ellipse el = new Ellipse();
                    el.Width = item.size;
                    el.Height = item.size;
                    double x = item.x - el.Width / 2;
                    double y = item.y - el.Height / 2;
                    el.Margin = new Thickness(x, y, 0, 0);
                    el.Fill = brushes[getColorId(item.color.Name)];
                    view.Children.Add(el);
                }
                view.Visibility = Visibility.Visible;
            };
        }

        private void onDispatchTimerChartTick(object sender, EventArgs e)
        {
            if (graphic != null)
            {
                graphic.chart.Visibility = Visibility.Hidden;
                var values = new int[3] { 0, 0, 0 };
                foreach (var item in this.frame)
                {
                    values[getColorId(item.color.Name)]++;
                }
                graphic.addValues(values);
                graphic.chart.Visibility = Visibility.Visible;
            };
        }

        private int getColorId(String colorname)
        {
            return colorname switch
            {
                "Green" => 0,
                "Blue" => 1,
                "Red" => 2,
                _ => throw new ArgumentException("Недопустимый код операции")
            };
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
