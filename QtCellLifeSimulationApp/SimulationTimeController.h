#pragma once

#include <QObject>
#include "SimulationModel.h"
#include <QTimer>

class SimulationTimeController : public QObject
{
	Q_OBJECT
private:
	QTimer* timer;
	SimulationModel::Simulation* model;
public:
	SimulationTimeController(QObject* parent, SimulationModel::Simulation* model);
	~SimulationTimeController();

	void setTimeSettings(int timer_ms, float sim_timelapse);
	void getTimeSettings(int* timer_ms, float* sim_timelapse);
	void start();
	void stop();
	bool isPlaying();
	void drawOneFrameIfInactive();
signals:
	void drawFrameSignal(std::vector<SimulationModel::drawEntity> frame);
	void fitToViewSizeSignal();
private slots:
	void nextFrameSlot();

};
