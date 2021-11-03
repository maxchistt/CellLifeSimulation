#include "QtCellLifeSimulationApp.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QInputDialog>

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

	connect(ui.actionLimitSettings, &QAction::triggered, this, &QtCellLifeSimulationApp::onLimitSettings);
	connect(ui.actionGenerationSettings, &QAction::triggered, this, &QtCellLifeSimulationApp::onGenerationSettings);
	connect(ui.actionTimeSettings, &QAction::triggered, this, &QtCellLifeSimulationApp::onTimeSettings);
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

void QtCellLifeSimulationApp::onLimitSettings()
{
	bool ok;
	int val = QInputDialog::getInt(this, tr("Reproduction limit"), tr("Limit"), 300, 1, 3000, 1, &ok);
	if (ok) model->cellsLimit = val;
}

void QtCellLifeSimulationApp::onGenerationSettings()
{
}

void QtCellLifeSimulationApp::onTimeSettings()
{
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



