#include "pch.h"

#include "SimulationModelCLR.h"

using namespace SimulationModelCLR;
using namespace CellsCLR;
using namespace SimulationModel;

void SimulationCLR::clearAll()
{
	simulation->clearAll();
}

array<DrawEntity^>^ SimulationCLR::getNextFrame()
{
	return SimFrameConverter::convert(simulation->getNextFrame());
}

void SimulationCLR::setSize(int x, int y)
{
	simulation->setSize(x, y);
}

int SimulationCLR::getWidth()
{
	return simulation->fieldSize.x;
}

int SimulationCLR::getHeight()
{
	return simulation->fieldSize.y;
}

void SimulationCLR::setTimelapse(float factor)
{
	simulation->setTimelapse(factor);
}

int% SimulationCLR::cellsLimit()
{
	return simulation->cellsLimit;
}

float% SimulationCLR::timelapse()
{
	return simulation->timelapse;
}

SimulationCLR::SimulationCLR()
{
	simulation = new Simulation();
	cellFactory = gcnew CellFactoryCLR(simulation->cellFactory);
}

SimulationCLR::SimulationCLR(int x, int y)
{
	simulation = new Simulation(x, y);
	cellFactory = gcnew CellFactoryCLR(simulation->cellFactory);
}

SimulationCLR::~SimulationCLR()
{
	delete simulation;
}
