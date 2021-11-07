#pragma once

#include <QObject>
#include "SimulationModel.h"
#include "GenerationSettingsWidget.h"

class SimulationGenerationController : public QObject
{
	Q_OBJECT
private:
	GenerationSettingsWidget* settings_widget;
	SimulationModel::Simulation* model;
public:
	SimulationGenerationController(QObject* parent, SimulationModel::Simulation* model, GenerationSettingsWidget* settings_widget);
	~SimulationGenerationController();

	void clear();
	void generate(int amount);
	void openSettings();
	void closeSettings();
};
