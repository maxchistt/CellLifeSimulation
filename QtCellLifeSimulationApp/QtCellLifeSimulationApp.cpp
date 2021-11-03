#include "QtCellLifeSimulationApp.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QInputDialog>
#include "TimeSettingsDialog.h"
#include <QMessageBox>

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
	generationSettings = new GenerationSettingsWidget(parent, model->cellFactory);

	connect(ui.actionPlay_Pause, &QAction::triggered, this, &QtCellLifeSimulationApp::onPlayPause);
	connect(ui.actionGenerate, &QAction::triggered, this, &QtCellLifeSimulationApp::onGenerate);
	connect(ui.actionClear, &QAction::triggered, this, &QtCellLifeSimulationApp::onClear);

	connect(ui.actionLimitSettings, &QAction::triggered, this, &QtCellLifeSimulationApp::onLimitSettings);
	connect(ui.actionGenerationSettings, &QAction::triggered, this, &QtCellLifeSimulationApp::onGenerationSettings);
	connect(ui.actionTimeSettings, &QAction::triggered, this, &QtCellLifeSimulationApp::onTimeSettings);
}

QtCellLifeSimulationApp::~QtCellLifeSimulationApp()
{
	delete generationSettings;
	delete model;
	delete view;
	delete controller;
}

void QtCellLifeSimulationApp::setPlayPause(bool on)
{
	if (on) {
		controller->start();
		ui.actionPlay_Pause->setText("Pause");
		ui.actionPlay_Pause->setIcon(QIcon(":/toolbar/resources/pause.png"));
	}
	else {
		controller->stop();
		ui.actionPlay_Pause->setText("Play");
		ui.actionPlay_Pause->setIcon(QIcon(":/toolbar/resources/play.png"));
	}
}

void QtCellLifeSimulationApp::onLimitSettings()
{
	bool ok;
	int val = QInputDialog::getInt(this, tr("Limit settings"), tr("Reproduction limit"), model->cellsLimit, 1, 3000, 1, &ok);
	if (ok) model->cellsLimit = val;
}

void QtCellLifeSimulationApp::onGenerationSettings()
{
	generationSettings->show();
}

void QtCellLifeSimulationApp::onTimeSettings()
{
	TimeSettingsDialog(this, controller).exec();
}

void QtCellLifeSimulationApp::closeEvent(QCloseEvent* event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr("Close"),
		tr("Are you sure?\n"),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		generationSettings->close();
		event->accept();
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



