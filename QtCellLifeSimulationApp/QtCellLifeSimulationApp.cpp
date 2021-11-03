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
	setPlayPause(false);

	connect(ui.actionPlay_Pause, &QAction::triggered, this, &QtCellLifeSimulationApp::onPlayPause);
	connect(ui.actionGenerate, &QAction::triggered, this, &QtCellLifeSimulationApp::onGenerate);
	connect(ui.actionClear, &QAction::triggered, this, &QtCellLifeSimulationApp::onClear);
}

QtCellLifeSimulationApp::~QtCellLifeSimulationApp()
{
	delete model;
	delete view;
	delete controller;
}

void QtCellLifeSimulationApp::setPlayPause(bool on)
{
	if (on) {
		controller->start();
		ui.actionPlay_Pause->setText("Pause");
	}
	else {
		controller->stop();
		ui.actionPlay_Pause->setText("Play");
	}
}

void QtCellLifeSimulationApp::onPlayPause() {
	setPlayPause(!controller->isPlaying());
}

void QtCellLifeSimulationApp::onGenerate()
{
	model->cellFactory->generateCells(30);
	controller->drawOneFrameIfInactive();
}

void QtCellLifeSimulationApp::onClear()
{
	model->clearAll();
}



