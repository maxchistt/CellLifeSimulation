#include "SimulationTimeController.h"

SimulationTimeController::SimulationTimeController(QObject* parent, SimulationModel::Simulation* model)
	: QObject(parent)
{
	this->model = model;
	timer = new QTimer(this);
	setTimeSettings(30, 30);
	connect(timer, &QTimer::timeout, this, &SimulationTimeController::emitNextFrameSlot);
}

SimulationTimeController::~SimulationTimeController()
{
	delete timer;
}

void SimulationTimeController::setTimeSettings(int timer_ms, float sim_timelapse)
{
	timer->setInterval(timer_ms);
	model->setTimelapse(sim_timelapse);
}

void SimulationTimeController::getTimeSettings(int* timer_ms, float* sim_timelapse)
{
	*timer_ms = timer->interval();
	*sim_timelapse = model->timelapse;
}

void SimulationTimeController::start()
{
	timer->start();
}

void SimulationTimeController::stop()
{
	timer->stop();
}

bool SimulationTimeController::isPlaying()
{
	return timer->isActive();
}

void SimulationTimeController::emitOneNextFrameIfInactive()
{
	if (!timer->isActive()) emitNextFrameSlot();
}

void SimulationTimeController::emitNextFrameSlot()
{
	emit drawNewFrameSignal(model->getNextFrame());
}
