#pragma once

#include <QObject>
#include "SimulationModel.h"
#include "SimulationView.h"

class SimulationViewController : public QObject
{
	Q_OBJECT
private:
	SimulationModel::Simulation* model;
	SimulationView* view;
	bool fitToView;
public:
	SimulationViewController(QObject* parent, SimulationModel::Simulation* model, SimulationView* view, bool fitToView = true);
	~SimulationViewController();
	void fit3DSceneView();
public slots:
	void drawFrameSlot(std::vector<SimulationModel::drawEntity> frame);
	void fitModelToViewSlot();
	void onChangeViewSlot(SimulationView* newView);
};
