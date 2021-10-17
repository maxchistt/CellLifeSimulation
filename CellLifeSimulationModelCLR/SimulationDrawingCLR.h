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

	class SimFrameConverter
	{
	private:
		static DrawEntity^ convertDrawEntity(SimulationModel::drawEntity& item);
		static Drawing::Color convertColor(SimulationModel::Cells::CellColor cellcolor);
	public:
		static array<DrawEntity^>^ convert(std::vector<SimulationModel::drawEntity>& frame_vector);
	};
};

