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
	int generationAmount = 30;
public:
	SimulationGenerationController(QObject* parent, SimulationModel::Simulation* model, GenerationSettingsWidget* settings_widget);
	~SimulationGenerationController();

	void clear();
	void generate();
	void openSettings();
	void closeSettings();

private slots:
	void setGenerationAmountSlot(int amount);
	void getGenerationAmountSlot(int& amount);
};
