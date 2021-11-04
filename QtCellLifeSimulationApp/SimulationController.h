#pragma once
#include <qobject.h>
#include "SimulationModel.h"
#include "SimulationView.h"
#include <QTimer>

class SimulationController :
	public QObject
{
	Q_OBJECT

private:
	QTimer* timer;
	SimulationModel::Simulation* model;
	SimulationView* view;

public:
	SimulationController(SimulationModel::Simulation* model, SimulationView* view);
	~SimulationController();

	void setTimeSettings(int timer_ms, float sim_timelapse);
	void getTimeSettings(int* timer_ms, float* sim_timelapse);
	void start();
	void stop();
	void generateCells(int amount);
	bool isPlaying();
	void drawOneFrameIfInactive();
private slots:
	void drawNextFrame();
};

