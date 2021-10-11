#include "Cell.h"
#include "SimulationModel.h"
#include "CellFactory.h"
#include <ctime> // для функции time()

using namespace SimulationModel;

int Simulation::timelapse = TIMELAPSE;

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

void Simulation::update()
{
	cells.insert(
		cells.end(), cellsnext.begin(), cellsnext.end()
	);
	cellsnext.clear();

	for (auto it = cells.begin(); it != cells.end(); it++) {
		Cells::Cell* cell = *it;
		if (cell == nullptr || cell->isAlive() == false) {
			continue;
		}
		else {
			cell->lifeCircle();
		}
	}

	cleardied();
}

void SimulationModel::Simulation::add(Cells::Cell* cell)
{
	cellsnext.push_back(cell);
}

void SimulationModel::Simulation::setTimelapse(int val)
{
	this->timelapse = val;
}

Simulation::Simulation() :Simulation(600, 800) {}

Simulation::Simulation(int x, int y)
{
	srand(static_cast<unsigned int>(time(0)));
	setSize(x, y);
}

void Simulation::generateCells()
{
	cellFactory.generate();
}

void SimulationModel::Simulation::setSize(int x, int y)
{
	this->fieldSize = structs::Point2D<int>(x, y);
}

std::vector<drawEntity> Simulation::drawSimulation()
{
	std::vector<drawEntity> drawings;
	update();

	for (auto it = cells.begin(); it != cells.end(); it++) {
		Cells::Cell* cell = *it;
		drawings.push_back(drawEntity{
			structs::Point2D<int>(cell->getPosition().x,cell->getPosition().y),
			cell->getSize(),
			cell->getColor(),
			});
	}

	return drawings;
}

