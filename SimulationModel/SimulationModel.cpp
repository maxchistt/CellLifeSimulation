#include "SimulationModel.h"
#include <ctime> // для функции time()

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

int Simulation::cellsCount()
{
	return cells.size();
}

void Simulation::setTimelapse(float val)
{
	this->timelapse = val;
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
	std::vector<drawEntity> drawings;
	update();

	for (auto cell : cells) {
		auto drawentity = drawEntity{
			Structs2D::Point2D<int>(cell->getPosition().x,cell->getPosition().y),
			cell->getSize(),
			cell->getColor(),
		};
		drawings.push_back(drawentity);
	}

	return drawings;
}

