#include "QtCellLifeSimulationApp.h"

using namespace SimulationModel;

QtCellLifeSimulationApp::QtCellLifeSimulationApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    simulation = new Simulation();
}
