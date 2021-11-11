#pragma once

#include <QObject>
#include "SimulationModel.h"
#include "SimulationView.h"

class SimulationViewController : public QObject
{
	Q_OBJECT
private:
	std::vector<SimulationModel::drawEntity> currentFrame;
	SimulationModel::Simulation* model;
	SimulationView* view;
	bool resizeMode = true;
public:
	void fitModelSizeToView();
	void drawCurrentFrame();
public:
	SimulationViewController(QObject* parent, SimulationModel::Simulation* model, SimulationView* view, bool resizeMode=true);
	~SimulationViewController();
	void fit3DSceneView();
	void setResizeMode(bool resize);
public slots:
	void drawNewFrameSlot(std::vector<SimulationModel::drawEntity> frame);
	void changeViewSlot(SimulationView* newView);
};
