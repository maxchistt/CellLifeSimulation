#include "SimulationViewController.h"
#include "ColorConverter.h"

SimulationViewController::SimulationViewController(QObject* parent, SimulationModel::Simulation* model, SimulationView* view, bool resizeMode)
	: QObject(parent)
{
	this->model = model;
	setResizeMode(resizeMode);
	changeViewSlot(view);
}

SimulationViewController::~SimulationViewController()
{
}

void SimulationViewController::fit3DSceneView()
{
	view->resize3DScene();
}

void SimulationViewController::setResizeMode(bool resize)
{
	resizeMode = resize;
}

void SimulationViewController::drawCurrentFrame()
{
	view->clear();
	for (SimulationModel::drawEntity item : currentFrame) {
		view->addDrawItem(item.point.x - item.size / 2, item.point.y - item.size / 2, item.size, ColorConverter::convertColor(item.color));
	}
	view->frameComplete();
}

void SimulationViewController::fitModelSizeToView()
{
	if(resizeMode)model->setSize(view->width(), view->height());
}

void SimulationViewController::changeViewSlot(SimulationView* newView)
{
	this->view = newView;
	fitModelSizeToView();
	drawCurrentFrame();
}

void SimulationViewController::drawNewFrameSlot(std::vector<SimulationModel::drawEntity> frame)
{
	currentFrame = frame;
	fitModelSizeToView();
	drawCurrentFrame();
}
