#include "cells.h"
#include "SimulationModel.h"

using namespace SimulationModel;

void Simulation::update()
{
	// Erase deleted
	for (auto it = cells.begin(); it != cells.end(); ) {
		if (*it == nullptr) {
			it = cells.erase(it);
		}
		else {
			Cells::Cell* cell = *it;
			cell->lifeCircle();
			++it;
		}
	}
}

void Simulation::findClosest(Cells::Cell* cell_finder)
{
	structs::Vect2D<int> resDistVect(0, 0);

	for (auto it = cells.begin(); it != cells.end(); ) {
		if (*it == nullptr) {
			it = cells.erase(it);
		}
		else {

			Cells::Cell* cell_to_find = *it;

			if (cell_finder != cell_to_find) {
				structs::Vect2D<int> curDistVect = cell_finder->getPosition().getDistanceVect(cell_to_find->getPosition());

				if (curDistVect.getAbs() < cell_finder->getSearchRadius()) {
					if ((resDistVect.getAbs() == 0) || (curDistVect.getAbs() < resDistVect.getAbs())) {
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

			++it;
		}
	}
}

void SimulationModel::Simulation::add(Cells::Cell* cell)
{
	cells.push_back(cell);
}
;

Simulation::Simulation():Simulation(600,800){}

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
	// Erase deleted
	for (auto it = cells.begin(); it != cells.end(); ) {
		if (*it == nullptr) {
			it = cells.erase(it);
		}
		else {
			++it;
		}
	}

	for each (Cells::Cell * cell in cells)
	{
		drawings.push_back(drawEntity{ cell->getPosition(),cell->getSize() });
	}

	return drawings;
}

