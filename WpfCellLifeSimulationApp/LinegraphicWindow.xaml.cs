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
        public LinegraphicWindow()
        {
            InitializeComponent();
            graph_Plant.Values = new ChartValues<int>();
            graph_Planter.Values = new ChartValues<int>();
            graph_Hunter.Values = new ChartValues<int>();
        }

        public void draw(int[] values)
        {
            graph_Plant.Values.Add(values[0]);
            graph_Planter.Values.Add(values[1]);
            graph_Hunter.Values.Add(values[2]);
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
