#include "SimulationController.h"
#include "ColorConverter.h"

SimulationController::SimulationController(SimulationModel::Simulation* model, SimulationView* view)
{
	this->setParent(view->parent());
	this->model = model;
	this->view = view;
	timer = new QTimer(this);
	setTimeSettings(30, 30);
	model->setSize(view->width(), view->height());
	connect(timer, &QTimer::timeout, this, &SimulationController::drawNextFrame);
}

SimulationController::~SimulationController()
{
	delete timer;
}

void SimulationController::drawNextFrame()
{
	view->clear();
	model->setSize(view->width(), view->height());
	for (auto item : model->getNextFrame()) {
		view->drawCircle(item.point.x - item.size / 2, item.point.y - item.size / 2, item.size, ColorConverter::convertColor(item.color));
	}
}

void SimulationController::setTimeSettings(int timer_ms, float sim_timelapse)
{
	timer->setInterval(timer_ms);
	model->setTimelapse(sim_timelapse);
}

void SimulationController::getTimeSettings(int* timer_ms, float* sim_timelapse)
{
	*timer_ms = timer->interval();
	*sim_timelapse = model->timelapse;
}

void SimulationController::start()
{
	timer->start();
}

void SimulationController::stop()
{
	timer->stop();
}

void SimulationController::generateCells(int amount)
{
	model->cellFactory->generateCells(amount);
}

bool SimulationController::isPlaying()
{
	return timer->isActive();
}

void SimulationController::drawOneFrameIfInactive()
{
	if (!timer->isActive()) drawNextFrame();
}
