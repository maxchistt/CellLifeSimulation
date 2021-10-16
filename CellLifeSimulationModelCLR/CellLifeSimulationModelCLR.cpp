#include "pch.h"

#include "CellLifeSimulationModelCLR.h"

using namespace CellLifeSimulationModelCLR;
using namespace SimulationModel;

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
