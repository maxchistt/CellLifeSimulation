#include "cells.h"
#include "SimulationModel.h"

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

void Simulation::findClosest(Cells::Cell* cell_finder)
{
	structs::Vect2D<float> resDistVect(cell_finder->getSearchRadius() * 2, cell_finder->getSearchRadius() * 2);

	for (auto it = cells.begin(); it != cells.end(); it++) {
		Cells::Cell* cell_to_find = *it;

		if (cell_to_find == nullptr || cell_to_find->isAlive() == false || cell_finder == cell_to_find) {
			continue;
		}
		else {
			structs::Vect2D<float> curDistVect = cell_finder->getPosition().getDistanceVect(cell_to_find->getPosition());

			if (curDistVect.getAbs() < cell_finder->getSearchRadius()) {
				if (curDistVect.getAbs() < resDistVect.getAbs()) {
					resDistVect = curDistVect;

					if (curDistVect.getAbs() <= (cell_finder->getSize() + cell_to_find->getSize()) / 2) {
						cell_finder->iteract(cell_to_find);
					}
					else {
						cell_finder->seeClosest(resDistVect);
					}
				}
			}

		}
	}
}

void SimulationModel::Simulation::add(Cells::Cell* cell)
{
	cellsnext.push_back(cell);
}
;

Simulation::Simulation() :Simulation(600, 800) {}

Simulation::Simulation(int x, int y)
{
	setSize(x, y);
	fillCells();
}

void Simulation::fillCells()
{
	for (int i = 0; i < 40; i++) {
		new Cells::Cell(this);
	}
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
		drawings.push_back(drawEntity{ structs::Point2D<int>(cell->getPosition().x,cell->getPosition().y),cell->getSize() });
	}

	return drawings;
}

