#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCellLifeSimulationApp.h"
#include "SimulationModel.h"
#include "SimulationView.h"
#include "SimulationController.h"

class QtCellLifeSimulationApp : public QMainWindow
{
	Q_OBJECT
public:
	QtCellLifeSimulationApp(QWidget* parent = Q_NULLPTR);
	~QtCellLifeSimulationApp();
private:
	SimulationModel::Simulation* model;
	SimulationView* view;
	SimulationController* controller;
	Ui::QtCellLifeSimulationAppClass ui;
	void setPlayPause(bool on);
private slots:
	void onPlayPause();
	void onGenerate();
	void onClear();
	void onLimitSettings();
	void onGenerationSettings();
	void onTimeSettings();
};
