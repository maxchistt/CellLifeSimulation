#include "pch.h"
#include "SimulationDrawingCLR.h"

using namespace System::Drawing;
using namespace CellLifeSimulationModelCLR;
using namespace SimulationModel;
using namespace SimulationModel::Cells;

DrawEntity::DrawEntity(int x, int y, int size, Color color)
{
	this->x = x;
	this->y = y;
	this->size = size;
	this->color = color;
}

SimFrameContainer::SimFrameContainer(std::vector<drawEntity>& vector_entities)
{
	frame_vector = new std::vector<drawEntity>(vector_entities);
}

SimFrameContainer::~SimFrameContainer()
{
	delete frame_vector;
}

int SimFrameContainer::Size()
{
	return frame_vector->size();
}

DrawEntity^ SimFrameContainer::getByIndex(const int index)
{
	return makeDrawEntity(frame_vector->operator[](index));
}

DrawEntity^ SimFrameContainer::makeDrawEntity(drawEntity& item)
{
	return gcnew DrawEntity(item.point.x, item.point.y, item.size, convertColor(item.color));
}

Color SimFrameContainer::convertColor(CellColor cellcolor)
{
	Color color;
	switch (cellcolor)
	{
	case CellColor::RED:
		color = Color::Red;
		break;
	case CellColor::GREEN:
		color = Color::Green;
		break;
	case CellColor::BLUE:
		color = Color::Blue;
		break;
	case CellColor::GRAY:
		color = Color::Gray;
		break;
	case CellColor::ORANGE:
		color = Color::Orange;
		break;
	case CellColor::YELLOW:
		color = Color::Yellow;
		break;
	case CellColor::BROWN:
		color = Color::Brown;
		break;
	default:
		color = Color::Black;
		break;
	}
	return color;
}
