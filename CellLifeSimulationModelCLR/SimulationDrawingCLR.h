#pragma once
#include "SimulationModel.h"

using namespace System;

namespace CellLifeSimulationModelCLR {
	public ref struct DrawEntity sealed {
		int x = 0;
		int y = 0;
		int size = 0;
		Drawing::Color color = Drawing::Color::Black;
		DrawEntity(int x, int y, int size, Drawing::Color color);
	};

	public ref class SimFrameContainer sealed
	{
	private:
		std::vector<SimulationModel::drawEntity>* frame_vector;
		DrawEntity^ makeDrawEntity(SimulationModel::drawEntity& item);
		Drawing::Color convertColor(SimulationModel::Cells::CellColor cellcolor);
	public:
		int Size();
		DrawEntity^ getByIndex(const int index);
		SimFrameContainer(std::vector<SimulationModel::drawEntity>& vector_entities);
		~SimFrameContainer();
	};
};

