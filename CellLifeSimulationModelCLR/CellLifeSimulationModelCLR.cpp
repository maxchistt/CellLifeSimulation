#include "pch.h"

#include "CellLifeSimulationModelCLR.h"

using namespace CellLifeSimulationModelCLR;
using namespace SimulationModel;

Simulation& SimulationModelCLR::ptr()
{
	return *simulation;
}

void SimulationModelCLR::generateCells(int amount)
{
	simulation->cellFactory->generateCells(amount);
}

void SimulationModelCLR::setGenerationType(int typeId)
{
	simulation->cellFactory->setGenerationType(typeId);
}

void SimulationModelCLR::setCellsReproductionLimit(int amount)
{
	simulation->cellsLimit = amount;
}

void SimulationModelCLR::clearAll()
{
	simulation->clearAll();
}

array<DrawEntity^>^ SimulationModelCLR::getNextFrame()
{
	return SimFrameConverter::convert(simulation->getNextFrame());
}

void CellLifeSimulationModelCLR::SimulationModelCLR::setSize(int x, int y)
{
	simulation->setSize(x, y);
}

int SimulationModelCLR::getWidth()
{
	return simulation->fieldSize.x;
}

int SimulationModelCLR::getHeight()
{
	return simulation->fieldSize.y;
}

void SimulationModelCLR::setTimelapse(float factor)
{
	simulation->setTimelapse(factor);
}

float SimulationModelCLR::getTimelapse()
{
	return simulation->timelapse;
}

SimulationModelCLR::SimulationModelCLR()
{
	simulation = new Simulation();
}

SimulationModelCLR::SimulationModelCLR(int x, int y)
{
	simulation = new Simulation(x, y);
}

SimulationModelCLR::~SimulationModelCLR()
{
	delete simulation;
}
