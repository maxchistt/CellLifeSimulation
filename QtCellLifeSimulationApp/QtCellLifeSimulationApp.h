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
	SimulationModel::Simulation* model;
	SimulationView* view;
	SimulationController* controller;
private:
	Ui::QtCellLifeSimulationAppClass ui;
};
