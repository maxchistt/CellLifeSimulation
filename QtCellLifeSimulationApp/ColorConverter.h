#pragma once
#include "SimulationModel.h"
#include <QColor>

class ColorConverter
{
public:
	static QColor convertColor(SimulationModel::Cells::CellColor cellcolor);
};

