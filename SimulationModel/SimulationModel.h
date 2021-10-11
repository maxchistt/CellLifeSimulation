#pragma once
#include "structs.h"
#include <vector>
#include "cells.h"

namespace SimulationModel {

	struct drawEntity {
		structs::Point2D<int> point;
		int size{ 0 };
	};


	class Simulation {
	public:
		void update();
		void findClosest(Cells::Cell* cell_finder);
		void add(Cells::Cell* cell);

		std::vector<Cells::Cell*> cells;

		structs::Point2D<int> fieldSize{100,100};
		std::vector<drawEntity> drawSimulation();

		Simulation();
		Simulation(int x, int y);

		void fillCells();
		void setSize(int x, int y);
	};

};




