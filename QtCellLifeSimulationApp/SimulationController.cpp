#include "SimulationController.h"

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

QColor SimulationController::convertColor(Cells::CellColor cellcolor)
{
	switch (cellcolor)
	{
	case SimulationModel::Cells::CellColor::RED:
		return Qt::red;
	case SimulationModel::Cells::CellColor::GREEN:
		return Qt::darkGreen;
	case SimulationModel::Cells::CellColor::BLUE:
		return Qt::blue;
	case SimulationModel::Cells::CellColor::GRAY:
		return Qt::gray;
	case SimulationModel::Cells::CellColor::ORANGE:
		return Qt::darkYellow;
	case SimulationModel::Cells::CellColor::YELLOW:
		return Qt::yellow;
	case SimulationModel::Cells::CellColor::BROWN:
		return Qt::darkGray;
	default:
		return Qt::black;
	}
}

void SimulationController::drawNextFrame()
{
	view->clear();
	model->setSize(view->width(), view->height());
	for (auto item : model->getNextFrame()) {
		view->drawCircle(item.point.x - item.size / 2, item.point.y - item.size / 2, item.size, convertColor(item.color));
	}
}

void SimulationController::setTimeSettings(int timer_ms, float sim_timelapse)
{
	timer->setInterval(timer_ms);
	model->setTimelapse(sim_timelapse);
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
