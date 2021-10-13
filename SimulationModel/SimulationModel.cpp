#include "Cell.h"
#include "SimulationModel.h"
#include "CellFactory.h"
#include <ctime> // ��� ������� time()

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
	srand(static_cast<unsigned int>(time(0)));
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

void Simulation::setTimelapse(float val)
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
void SimulationModel::Simulation::generateCells(int n)
{
	cellFactory.generate(n);
}

void SimulationModel::Simulation::setSize(int x, int y)
{
	this->fieldSize = structs::Point2D<int>(x, y);
}

std::vector<drawEntity> Simulation::drawSimulation()
{
	std::vector<drawEntity> drawings;
	update();

	for (auto cell : cells) {
		auto drawentity = drawEntity{
			structs::Point2D<int>(cell->getPosition().x,cell->getPosition().y),
			cell->getSize(),
			cell->getColor(),
		};
		drawings.push_back(drawentity);
	}

	return drawings;
}

