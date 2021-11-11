#include "SimulationViewController.h"
#include "ColorConverter.h"

SimulationViewController::SimulationViewController(QObject* parent, SimulationModel::Simulation* model, SimulationView* view, bool fitToView)
	: QObject(parent)
{
	this->model = model;
	this->view = view;
	this->fitToView = fitToView;

	fitModelToViewSlot();
}

SimulationViewController::~SimulationViewController()
{
}

void SimulationViewController::fitModelToViewSlot()
{
	if (fitToView)model->setSize(view->width(), view->height());
}

void SimulationViewController::drawFrameSlot(std::vector<SimulationModel::drawEntity> frame)
{
	view->clear();
	for (SimulationModel::drawEntity item : frame) {
		view->drawItem(item.point.x - item.size / 2, item.point.y - item.size / 2, item.size, ColorConverter::convertColor(item.color));
	}
}
