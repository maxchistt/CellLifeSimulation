#pragma once

#include <QWidget>
#include "ui_GenerationSettingsWidget.h"
#include "SimulationModel.h"

class GenerationSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	GenerationSettingsWidget(QWidget* parent = Q_NULLPTR, SimulationModel::Cells::CellFactory* factory = nullptr);
	~GenerationSettingsWidget();
	void setFactory(SimulationModel::Cells::CellFactory* factory);

private:
	SimulationModel::Cells::CellFactory* factory;
	Ui::GenerationSettingsWidget ui;
};
