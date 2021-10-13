#pragma once
#include "structs.h"
#include <vector>
#include "Cell.h"
#include "CellFactory.h"

#define TIMELAPSE 10

namespace SimulationModel {

	struct drawEntity {
		structs::Point2D<int> point;
		int size{ 0 };
		Cells::CellColor color;
	};

	class Simulation {
		std::vector<Cells::Cell*> cellsnext;
		std::vector<Cells::Cell*> cells;
		Cells::CellFactory cellFactory = Cells::CellFactory(this);
	public:

		friend static void Cells::Cell::findClosest(SimulationModel::Simulation* sim, Cells::Cell* cell_finder);
		float timelapse = TIMELAPSE;

		void cleardied();
		void cleardied(Cells::Cell* target);
		void clearAll();
		void update();
		void add(Cells::Cell* cell);
		void setTimelapse(float val = TIMELAPSE);

		structs::Point2D<int> fieldSize{ 100,100 };
		std::vector<drawEntity> drawSimulation();

		Simulation();
		Simulation(int x, int y);

		void generateCells();
		void generateCells(int n);
		void setSize(int x, int y);
	};

};




