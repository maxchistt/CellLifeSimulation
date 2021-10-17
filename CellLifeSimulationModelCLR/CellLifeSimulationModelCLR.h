#pragma once
#include "SimulationModel.h"
#include "SimulationDrawingCLR.h"

using namespace System;

namespace CellLifeSimulationModelCLR {
	public ref class SimulationModelCLR sealed
	{
	private:
		SimulationModel::Simulation* simulation;
	public:
		SimulationModel::Simulation& ptr();
		void generateCells(int amount);
		void setGenerationType(int typeId);
		void setCellsReproductionLimit(int amount);
		void clearAll();
		array<DrawEntity^>^ getNextFrame();
		void setSize(int x, int y);
		int getWidth();
		int getHeight();
		void setTimelapse(float factor);
		float getTimelapse();

		SimulationModelCLR();
		SimulationModelCLR(int x, int y);
		~SimulationModelCLR();
	};
}
