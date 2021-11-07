#include "SimulationGenerationController.h"

SimulationGenerationController::SimulationGenerationController(QObject* parent, SimulationModel::Simulation* model, GenerationSettingsWidget* settings_widget)
	: QObject(parent)
{
	this->model = model;
	this->settings_widget = settings_widget;
	settings_widget->setCellFactory(model->cellFactory);
	connect(settings_widget, &GenerationSettingsWidget::setGenerationAmountSignal, this, setGenerationAmountSlot);
	connect(settings_widget, &GenerationSettingsWidget::getGenerationAmountSignal, this, getGenerationAmountSlot);
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

int SimulationGenerationController::getGenerationAmountSlot()
{
	return generationAmount;
}

void SimulationGenerationController::setGenerationAmountSlot(int amount)
{
	if (amount >= 0) generationAmount = amount;
}
