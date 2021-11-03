#include "QtCellLifeSimulationApp.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>

using namespace SimulationModel;

QtCellLifeSimulationApp::QtCellLifeSimulationApp(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	model = new Simulation();

	view = new SimulationView(this);
	setCentralWidget(view);

	controller = new SimulationController(model, view);
	controller->setTimeSettings(30, 30);
	controller->generateCells(70);
	controller->start();
}

QtCellLifeSimulationApp::~QtCellLifeSimulationApp()
{
	delete model;
	delete view;
	delete controller;
}

