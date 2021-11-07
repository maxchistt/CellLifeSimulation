#include "SimulationGenerationController.h"

SimulationGenerationController::SimulationGenerationController(QObject* parent, SimulationModel::Simulation* model, GenerationSettingsWidget* settings_widget)
	: QObject(parent)
{
	this->model = model;
	this->settings_widget = settings_widget;

	connect(settings_widget, &GenerationSettingsWidget::setGenerationAmountSignal, this, &SimulationGenerationController::setGenerationAmountSlot);
	connect(settings_widget, &GenerationSettingsWidget::setupGenerationAmountSignal, this, &SimulationGenerationController::getGenerationAmountSlot);

	settings_widget->setCellFactory(model->cellFactory);
}

SimulationGenerationController::~SimulationGenerationController()
{
}

void SimulationGenerationController::clear()
{
	model->clearAll();
}

void SimulationGenerationController::generate()
{
	model->cellFactory->generateCells(generationAmount);
}

void SimulationGenerationController::openSettings()
{
	settings_widget->show();
}

void SimulationGenerationController::closeSettings()
{
	settings_widget->close();
}

void SimulationGenerationController::getGenerationAmountSlot(int& amount)
{
	amount = generationAmount;
}

void SimulationGenerationController::setGenerationAmountSlot(int amount)
{
	if (amount >= 0) generationAmount = amount;
}
