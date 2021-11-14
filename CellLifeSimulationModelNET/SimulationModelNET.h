#pragma once
#include "SimulationModel.h"
#include "SimulationDrawingNET.h"
#include "CellsNET.h"

using namespace System;

namespace SimulationModelNET {
	public ref class SimulationNET sealed
	{
	private:
		SimulationModel::Simulation* simulation;
	public:
		CellsNET::CellFactoryNET^ cellFactory;
		void clearAll();
		array<DrawEntity^>^ getNextFrame();
		void setSize(int x, int y);
		int getWidth();
		int getHeight();
		void setTimelapse(float factor);
		int% cellsLimit();
		float% timelapse();

		SimulationNET();
		SimulationNET(int x, int y);
		~SimulationNET();
	};
}
