#pragma once
#pragma once
#include <vector>
#include "Structs2D.h"
#include "Cell.h"
#include "CellFactory.h"

namespace SimulationModel {

	struct drawEntity {
		Structs2D::Point2D<int> point;
		int size{ 0 };
		Cells::CellColor color;
	};

	class SimulationDraw
	{
	public:
		static std::vector<drawEntity> drawSimulation(std::vector<Cells::Cell*>& cells);
	};
};


