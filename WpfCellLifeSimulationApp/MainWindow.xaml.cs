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
using System.Windows.Navigation;
using System.Windows.Shapes;

using SimulationModelNET;

namespace WpfCellLifeSimulationApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SimDrawController simulation;
        LinegraphicWindow graph = null;
        public MainWindow()
        {
            InitializeComponent();
            simulation = new();
            simulation.setImage(SimView);
            simulation.setTimeSettings(30, 30, 30);
            simulation.setCellsReproductionLimit(300);
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }

        private void onShowGraph(object sender, RoutedEventArgs e)
        {
            graph = new();
            simulation.setGraph(graph);
            graph.Show();
        }

        private void onHide(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }

        private void onClose(object sender, RoutedEventArgs e)
        {
            this.Close();
            if (graph != null) graph.Close();
        }

        private void onClear(object sender, RoutedEventArgs e)
        {
            simulation.clearCells();
            simulation.updOneFrame();
        }

        private void onGenerateCells(object sender, RoutedEventArgs e)
        {
            simulation.generateCells(7);
            simulation.updOneFrame();
        }

        private void onPlayPause(object sender, RoutedEventArgs e)
        {
            if (simulation.isrunning())
            {
                simulation.stop();
                PlayPause.Content = ">";
            }
            else
            {
                simulation.start();
                PlayPause.Content = "=";
            }
        }
    }
}
