#include "ColorConverter.h"

QColor ColorConverter::convertColor(SimulationModel::Cells::CellColor cellcolor)
{
	switch (cellcolor)
	{
	case SimulationModel::Cells::CellColor::RED:
		return Qt::red;
	case SimulationModel::Cells::CellColor::GREEN:
		return Qt::darkGreen;
	case SimulationModel::Cells::CellColor::BLUE:
		return Qt::blue;
	case SimulationModel::Cells::CellColor::GRAY:
		return Qt::gray;
	case SimulationModel::Cells::CellColor::ORANGE:
		return Qt::darkYellow;
	case SimulationModel::Cells::CellColor::YELLOW:
		return Qt::yellow;
	case SimulationModel::Cells::CellColor::BROWN:
		return Qt::darkRed;
	default:
		return Qt::black;
	}
}

QString ColorConverter::convertColorToString(SimulationModel::Cells::CellColor cellcolor)
{
	switch (cellcolor)
	{
	case SimulationModel::Cells::CellColor::RED:
		return "red";
	case SimulationModel::Cells::CellColor::GREEN:
		return "darkGreen";
	case SimulationModel::Cells::CellColor::BLUE:
		return "blue";
	case SimulationModel::Cells::CellColor::GRAY:
		return "gray";
	case SimulationModel::Cells::CellColor::ORANGE:
		return "darkYellow";
	case SimulationModel::Cells::CellColor::YELLOW:
		return "yellow";
	case SimulationModel::Cells::CellColor::BROWN:
		return "darkRed";
	default:
		return "black";
	}
}
