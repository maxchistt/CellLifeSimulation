#include "MainWindowCLS.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QInputDialog>
#include "TimeSettingsDialog.h"
#include <QMessageBox>
#include "SimulationView2D.h"
#include "SimulationViewC3D.h"


using namespace SimulationModel;

MainWindowCLS::MainWindowCLS(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	model = new Simulation();
#	ifndef C3D_USAGE
	ui.actionChange_view->setEnabled(false);
#	endif

	view = new SimulationView2D(this);
	setCentralWidget(view);
	controller_view = new SimulationViewController(this, model, view);

	controller_time = new SimulationTimeController(this, model);
	controller_time->setTimeSettings(30, 30);
	setPlayPause(false);

	generationSettingsWidget = new GenerationSettingsWidget(parent);
	controller_generation = new SimulationGenerationController(this, model, generationSettingsWidget);

	connect(controller_time, &SimulationTimeController::drawNewFrameSignal, controller_view, &SimulationViewController::drawNewFrameSlot);
	connect(this, &MainWindowCLS::viewChangedSignal, controller_view, &SimulationViewController::changeViewSlot);

	connect(ui.actionPlay_Pause, &QAction::triggered, this, &MainWindowCLS::onPlayPause);
	connect(ui.actionGenerate, &QAction::triggered, this, &MainWindowCLS::onGenerate);
	connect(ui.actionClear, &QAction::triggered, this, &MainWindowCLS::onClear);
	connect(ui.actionLimitSettings, &QAction::triggered, this, &MainWindowCLS::onLimitSettings);
	connect(ui.actionGenerationSettings, &QAction::triggered, this, &MainWindowCLS::onGenerationSettings);
	connect(ui.actionTimeSettings, &QAction::triggered, this, &MainWindowCLS::onTimeSettings);
	connect(ui.actionAbout, &QAction::triggered, this, &MainWindowCLS::about);
	connect(ui.actionAboutQt, &QAction::triggered, this, &MainWindowCLS::aboutQt);
	connect(ui.actionChange_view, &QAction::triggered, this, &MainWindowCLS::changeViewSlot);
}

MainWindowCLS::~MainWindowCLS()
{
	delete model;
	delete view;
	delete controller_time;
	delete controller_view;
	delete controller_generation;
	delete generationSettingsWidget;
}

void MainWindowCLS::setPlayPause(bool setPlay)
{
	if (setPlay) {
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

void MainWindowCLS::setNewView()
{
	auto oldview = view;

	if (basicView) {
		view = new SimulationView2D(this);
	}
	else {
#		ifdef C3D_USAGE
		view = new SimulationViewC3D(this);
#		else
		view = new SimulationView2D(this);
#		endif
	}

	controller_view->setResizeMode(basicView);
	setCentralWidget(view);
	emit viewChangedSignal(view);

	delete oldview;
}

void MainWindowCLS::onLimitSettings()
{
	bool ok;
	int val = QInputDialog::getInt(this, tr("Limit settings"), tr("Reproduction limit"), model->cellsLimit, 1, 3000, 1, &ok);
	if (ok) model->cellsLimit = val;
}

void MainWindowCLS::onGenerationSettings()
{
	controller_generation->openSettings();
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
		controller_generation->closeSettings();
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
	if (basicView) {
		setPlayPause(!controller_time->isPlaying());
	}
	else {
		controller_time->emitOneNextFrameIfInactive();
	}
}

void MainWindowCLS::onGenerate()
{
	controller_view->fitModelSizeToView();
	controller_generation->generate();
	controller_time->emitOneNextFrameIfInactive();
	controller_view->fit3DSceneView();
}

void MainWindowCLS::onClear()
{
	controller_generation->clear();
	controller_time->emitOneNextFrameIfInactive();
}

void MainWindowCLS::changeViewSlot()
{
	if (basicView) {
#		ifdef C3D_USAGE
		basicView = false;
		setPlayPause(false);
		ui.actionPlay_Pause->setText("Play step");
		ui.actionPlay_Pause->setIcon(QIcon(":/toolbar/resources/next.png"));
#		endif
	}
	else {
		basicView = true;
		setPlayPause(controller_time->isPlaying());
	}
	setNewView();
	controller_view->drawCurrentFrame();
	controller_view->fit3DSceneView();
}



