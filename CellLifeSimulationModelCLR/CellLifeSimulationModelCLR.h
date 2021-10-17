#pragma once
#include "SimulationModel.h"
#include "SimulationDrawingCLR.h"
#include "CellsCLR.h"

using namespace System;

namespace CellLifeSimulationModelCLR {
	public ref class SimulationModelCLR sealed
	{
	private:
		SimulationModel::Simulation* simulation;
	public:
		CellsCLR::CellFactoryCLR^ cellFactory;
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
