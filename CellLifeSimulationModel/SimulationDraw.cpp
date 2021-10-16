#include "pch.h"
#include "SimulationDraw.h"

using namespace SimulationModel;

std::vector<drawEntity> SimulationDraw::drawSimulation(std::vector<Cells::Cell*>& cells)
{
	std::vector<drawEntity> drawings;
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
