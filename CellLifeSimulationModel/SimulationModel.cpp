#include "pch.h"
#include "SimulationModel.h"
#include <ctime> // ??? ??????? time()

using namespace SimulationModel;

void Simulation::cleardied()
{
	cleardied(nullptr);
}

void Simulation::cleardied(Cells::Cell* target)
{
	for (auto it = cells.begin(); it != cells.end(); ) {
		Cells::Cell* cell = *it;
		if (cell == nullptr || cell == target || cell->isAlive() == false) {
			it = cells.erase(it);
			delete cell;
		}
		else {
			++it;
		}
	}
}

void Simulation::clearAll()
{
	cells.clear();
	cellsnext.clear();
}

void Simulation::update()
{
	//srand(static_cast<unsigned int>(time(0)));
	cells.insert(
		cells.end(), cellsnext.begin(), cellsnext.end()
	);
	cellsnext.clear();
	for (auto cell : cells)
	{
		if (cell == nullptr || cell->isAlive() == false) {
			continue;
		}
		else {
			cell->lifeCircle();
		}
	}

	cleardied();
}

void Simulation::add(Cells::Cell* cell)
{
	cellsnext.push_back(cell);
}

int Simulation::cellsCount()
{
	return cells.size();
}

void Simulation::setTimelapse(float val)
{
	if (timelapse > 0) {
		this->timelapse = val;
	}
	else if (timelapse < 0) {
		this->timelapse = -1.0 / val;
	}
	else {
		this->timelapse = TIMELAPSE;
	}
}

Simulation::Simulation() {
	cellFactory = new Cells::CellFactory(this);
	srand(static_cast<unsigned int>(time(0)));
}

Simulation::Simulation(int x, int y) :Simulation()
{
	setSize(x, y);
}

Simulation::~Simulation() {
	delete cellFactory;
}

void SimulationModel::Simulation::setSize(int x, int y)
{
	this->fieldSize = Structs2D::Point2D<int>(x, y);
}

std::vector<drawEntity> Simulation::getNextFrame()
{
	update();
	return SimulationDraw::drawSimulation(cells);
}

