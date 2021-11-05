#include "MainWindowCLS.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QInputDialog>
#include "TimeSettingsDialog.h"
#include <QMessageBox>

using namespace SimulationModel;

MainWindowCLS::MainWindowCLS(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	model = new Simulation();
	view = new SimulationView(this);
	setCentralWidget(view);
	controller_view = new SimulationViewController(this, model, view);
	controller_time = new SimulationTimeController(this, model);
	controller_time->setTimeSettings(30, 30);
	setPlayPause(false);
	generationSettingsWidget = new GenerationSettingsWidget(parent, model->cellFactory);

	connect(controller_time, &SimulationTimeController::fitToViewSizeSignal, controller_view, &SimulationViewController::fitModelToViewSlot);
	connect(controller_time, &SimulationTimeController::drawFrameSignal, controller_view, &SimulationViewController::drawFrameSlot);

	connect(ui.actionPlay_Pause, &QAction::triggered, this, &MainWindowCLS::onPlayPause);
	connect(ui.actionGenerate, &QAction::triggered, this, &MainWindowCLS::onGenerate);
	connect(ui.actionClear, &QAction::triggered, this, &MainWindowCLS::onClear);

	connect(ui.actionLimitSettings, &QAction::triggered, this, &MainWindowCLS::onLimitSettings);
	connect(ui.actionGenerationSettings, &QAction::triggered, this, &MainWindowCLS::onGenerationSettings);
	connect(ui.actionTimeSettings, &QAction::triggered, this, &MainWindowCLS::onTimeSettings);

	connect(ui.actionAbout, &QAction::triggered, this, &MainWindowCLS::about);
	connect(ui.actionAboutQt, &QAction::triggered, this, &MainWindowCLS::aboutQt);
}

MainWindowCLS::~MainWindowCLS()
{
	delete generationSettingsWidget;
	delete model;
	delete view;
	delete controller_time;
	delete controller_view;
}

void MainWindowCLS::setPlayPause(bool on)
{
	if (on) {
		controller_time->start();
		ui.actionPlay_Pause->setText("Pause");
		ui.actionPlay_Pause->setIcon(QIcon(":/toolbar/resources/pause.png"));
	}
	else {
		controller_time->stop();
		ui.actionPlay_Pause->setText("Play");
		ui.actionPlay_Pause->setIcon(QIcon(":/toolbar/resources/play.png"));
	}
}

void MainWindowCLS::onLimitSettings()
{
	bool ok;
	int val = QInputDialog::getInt(this, tr("Limit settings"), tr("Reproduction limit"), model->cellsLimit, 1, 3000, 1, &ok);
	if (ok) model->cellsLimit = val;
}

void MainWindowCLS::onGenerationSettings()
{
	generationSettingsWidget->show();
}

void MainWindowCLS::onTimeSettings()
{
	TimeSettingsDialog(this, controller_time).exec();
}

void MainWindowCLS::closeEvent(QCloseEvent* event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr("Close"),
		tr("Are you sure?\n"),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		generationSettingsWidget->close();
		event->accept();
	}
}

void MainWindowCLS::about()
{
	QString str;
	str += "Project of 2D simulation of cell life with several clients in C# and C++. This is a Qt client.<br/>";
	str += "For more information see <a href=\"https://github.com/maxchistt/CellLifeSimulation\">GitHub page</a>";
	QMessageBox::about(this, "About", str);
}

void MainWindowCLS::aboutQt()
{
	QMessageBox::aboutQt(this);
}

void MainWindowCLS::onPlayPause() {
	setPlayPause(!controller_time->isPlaying());
}

void MainWindowCLS::onGenerate()
{
	model->cellFactory->generateCells(30);
	controller_time->drawOneFrameIfInactive();
}

void MainWindowCLS::onClear()
{
	model->clearAll();
	controller_time->drawOneFrameIfInactive();
}



