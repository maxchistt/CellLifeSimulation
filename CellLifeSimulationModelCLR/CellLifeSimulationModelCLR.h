#pragma once
#include "SimulationModel.h"

using namespace System;

namespace CellLifeSimulationModelCLR {
	public ref class SimulationModelCLR sealed
	{
	private:
		SimulationModel::Simulation* simulation;
	public:
		SimulationModel::Simulation& ptr() {
			return *simulation;
		};
	public:
		SimulationModelCLR();
		SimulationModelCLR(int x, int y);
		~SimulationModelCLR();
	};
}
