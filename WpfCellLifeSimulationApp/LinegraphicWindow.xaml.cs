using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using LiveCharts;
using LiveCharts.Wpf;

namespace WpfCellLifeSimulationApp
{
    /// <summary>
    /// Логика взаимодействия для linegraphic.xaml
    /// </summary>
    public partial class LinegraphicWindow : Window
    {
        const int maxpoints = 100;
        const int even = 2;

        int[] counterVal = new int[3] { 1, 1, 1 };
        int[] counterEven = new int[3] { 1, 1, 1 };

        public LinegraphicWindow()
        {
            InitializeComponent();
            graph_Plant.Values = new ChartValues<int>();
            graph_Planter.Values = new ChartValues<int>();
            graph_Hunter.Values = new ChartValues<int>();
        }

        public void addValues(int[] vals)
        {
            addChartValue(ref graph_Plant, vals, 0);
            addChartValue(ref graph_Planter, vals, 1);
            addChartValue(ref graph_Hunter, vals, 2);
        }

        void addChartValue(ref LiveCharts.Wpf.LineSeries line, int[] vals, int index)
        {
            if (line.Values.Count > maxpoints)
            {
                int ind = 0;
                List<object> newvals = new();
                foreach (var item in line.Values)
                {
                    if (ind % even == 0) newvals.Add(item);
                    ind++;
                };
                line.Values.Clear();
                line.Values.AddRange(newvals);
                counterEven[index] *= even;
            };

            if (counterVal[index] >= counterEven[index])
            {
                line.Values.Add(vals[index]);
                counterVal[index] = 1;
            }
            else
            {
                counterVal[index]++;
            }

        }

        private void onHide(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }

        private void onClose(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }
    }
}
