#include "pch.h"

#include "SimulationModelNET.h"

using namespace SimulationModelNET;
using namespace CellsNET;
using namespace SimulationModel;

void SimulationNET::clearAll()
{
	simulation->clearAll();
}

array<DrawEntity^>^ SimulationNET::getNextFrame()
{
	return SimFrameConverter::convert(simulation->getNextFrame());
}

void SimulationNET::setSize(int x, int y)
{
	simulation->setSize(x, y);
}

int SimulationNET::getWidth()
{
	return simulation->fieldSize.x;
}

int SimulationNET::getHeight()
{
	return simulation->fieldSize.y;
}

void SimulationNET::setTimelapse(float factor)
{
	simulation->setTimelapse(factor);
}

int% SimulationNET::cellsLimit()
{
	return simulation->cellsLimit;
}

float% SimulationNET::timelapse()
{
	return simulation->timelapse;
}

SimulationNET::SimulationNET()
{
	simulation = new Simulation();
	cellFactory = gcnew CellFactoryNET(simulation->cellFactory);
}

SimulationNET::SimulationNET(int x, int y)
{
	simulation = new Simulation(x, y);
	cellFactory = gcnew CellFactoryNET(simulation->cellFactory);
}

SimulationNET::~SimulationNET()
{
	delete simulation;
}
