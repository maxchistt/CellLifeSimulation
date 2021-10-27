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
        public DTimer(DispatcherPriority priority) : base(priority)
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
        private Canvas view = null;
        private LinegraphicWindow graphic = null;

        private DTimer dispatch_timer_image;
        private DTimer dispatch_timer_chart;
        private Timer simulation_timer;

        Brush[] brushes;

        public SimDrawController()
        {
            frame = Array.Empty<DrawEntity>();
            simulation = new SimulationCLR();

            dispatch_timer_image = new DTimer(System.Windows.Threading.DispatcherPriority.Normal);
            dispatch_timer_image.addHandler(onDispatchTimerImageTick);
            dispatch_timer_chart = new DTimer(System.Windows.Threading.DispatcherPriority.SystemIdle);
            dispatch_timer_chart.addHandler(onDispatchTimerChartTick);
            simulation_timer = new Timer();
            simulation_timer.Elapsed += nextFrameTimerHandler;
            setDispatchTimerInterval(30);
            setTimeSettings(30, 30);

            brushes = new Brush[3] {
                new SolidColorBrush((Color)ColorConverter.ConvertFromString("SeaGreen")),
                new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF1295D3")),
                new SolidColorBrush((Color)ColorConverter.ConvertFromString("Red"))
            };
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

        public void setImage(Canvas image)
        {
            view = image;
            simulation.setSize((int)view.Width, (int)view.Height);
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

        public void setTimeSettings(float simulation_timelapse, int timer_interval)
        {
            simulation_timer.Interval = timer_interval > 0 ? timer_interval : 100;
            simulation.setTimelapse(simulation_timelapse);
        }

        public void setDispatchTimerInterval(int timer_interval)
        {
            dispatch_timer_chart.setInterval(timer_interval > 0 ? timer_interval : 100);
            dispatch_timer_image.setInterval(timer_interval > 0 ? timer_interval : 100);
        }

        private void nextFrameTimerHandler(Object source, ElapsedEventArgs e)
        {
            frame = simulation.getNextFrame();
        }

        private void onDispatchTimerImageTick()
        {
            if(view!=null)redrawImage();
        }

        private void onDispatchTimerChartTick()
        {
            if (graphic != null) updateChart();
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

        private void updateChart()
        {
            graphic.chart.Visibility = Visibility.Hidden;
            var values = new int[3] { 0, 0, 0 };
            foreach (var item in this.frame)
            {
                values[getColorId(item.color.Name)]++;
            }
            graphic.addValues(values);
            graphic.chart.Visibility = Visibility.Visible;
        }

        private void redrawImage()
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
