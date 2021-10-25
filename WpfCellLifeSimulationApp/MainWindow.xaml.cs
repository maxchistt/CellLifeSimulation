﻿using System;
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

using SimulationModelCLR;

namespace WpfCellLifeSimulationApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SimDrawController simulation;
        LinegraphicWindow graph;
        public MainWindow()
        {
            InitializeComponent();
            graph = new();

            simulation = new(this.SimView, graph);
            simulation.setDispatchTimerInterval(100);
            simulation.setTimeSettings(30, 50);
            simulation.setCellsReproductionLimit(300);
            graph.Show();
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }

        private void onHide(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }

        private void onClose(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void onClear(object sender, RoutedEventArgs e)
        {
            simulation.clearCells();
        }

        private void onGenerateCells(object sender, RoutedEventArgs e)
        {
            simulation.generateCells(7);
            simulation.start();
            PlayPause.Content = "=";
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
