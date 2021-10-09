#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCellLifeSimulationApp.h"
//#include "SimulationModel.h"

class QtCellLifeSimulationApp : public QMainWindow
{
    Q_OBJECT

public:
    QtCellLifeSimulationApp(QWidget *parent = Q_NULLPTR);
    //Simulation* simulation;

private:
    Ui::QtCellLifeSimulationAppClass ui;
};
