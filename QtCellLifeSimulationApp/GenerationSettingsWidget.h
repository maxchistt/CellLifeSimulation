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
	void updateTable();

private slots:
	void clearAllOptions();
	void deleteSelectedOption();
	void editSelectedOption();
	void editor_new();
	void editor_reset();
	void editor_save();

private:
	SimulationModel::Cells::CellFactory* factory;
	Ui::GenerationSettingsWidget ui;
};
