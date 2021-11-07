#include "SimulationGenerationController.h"

SimulationGenerationController::SimulationGenerationController(QObject* parent, SimulationModel::Simulation* model, GenerationSettingsWidget* settings_widget)
	: QObject(parent)
{
	this->model = model;
	this->settings_widget = settings_widget;
	settings_widget->setCellFactory(model->cellFactory);
}

SimulationGenerationController::~SimulationGenerationController()
{
}

void SimulationGenerationController::clear()
{
	model->clearAll();
}

void SimulationGenerationController::generate(int amount)
{
	model->cellFactory->generateCells();
}

void SimulationGenerationController::openSettings()
{
	settings_widget->show();
}

void SimulationGenerationController::closeSettings()
{
	settings_widget->close();
}
