#include "pch.h"
#include "SimulationDrawingCLR.h"

using namespace System::Drawing;
using namespace SimulationModelCLR;
using namespace SimulationModel;
using namespace SimulationModel::Cells;

DrawEntity::DrawEntity(int x, int y, int size, Color color)
{
	this->x = x;
	this->y = y;
	this->size = size;
	this->color = color;
}

DrawEntity^ SimFrameConverter::convertDrawEntity(SimulationModel::drawEntity& item)
{
	return gcnew DrawEntity(item.point.x, item.point.y, item.size, convertColor(item.color));
}

Color SimFrameConverter::convertColor(CellColor cellcolor)
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

array<DrawEntity^>^ SimFrameConverter::convert(std::vector<SimulationModel::drawEntity>& frame_vector)
{
	int size = frame_vector.size();
	array<DrawEntity^>^ arr = gcnew array<DrawEntity^>(size);
	for (int i = 0; i < size; i++) {
		arr[i] = convertDrawEntity(frame_vector[i]);
	};
	return arr;
}
