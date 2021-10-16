#pragma once
#include <vector>
#include "Structs2D.h"
#include "Cell.h"
#include "CellFactory.h"

#define TIMELAPSE	10
#define CELLSLIMIT	300

namespace SimulationModel {

	struct drawEntity {
		Structs2D::Point2D<int> point;
		int size{ 0 };
		Cells::CellColor color;
	};

	class Simulation {
		friend class Cells::Cell;
		std::vector<Cells::Cell*> cellsnext;
		std::vector<Cells::Cell*> cells;
		void add(Cells::Cell* cell);
		int cellsCount();
		void cleardied();
		void cleardied(Cells::Cell* target);
		void update();
	public:
		Cells::CellFactory* cellFactory;
		Structs2D::Point2D<int> fieldSize{ 600,800 };
		int cellsLimit = CELLSLIMIT;
		float timelapse = TIMELAPSE;
		void clearAll();
		void setTimelapse(float val = TIMELAPSE);
		void setSize(int x, int y);
		std::vector<drawEntity> getNextFrame();
		Simulation();
		Simulation(int x, int y);
		~Simulation();
	};
};




