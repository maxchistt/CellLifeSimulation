#include "pch.h"
#include "CellsNET.h"

using namespace SimulationModelNET;
using namespace CellsNET;
using namespace SimulationModel;

void CellFactoryNET::generateCells(int amount)
{
	factory->generateCells(amount);
}

void CellFactoryNET::setGenerationType(int typeId)
{
	factory->setGenerationType(typeId);
}

CellFactoryNET::CellFactoryNET(Cells::CellFactory* factory_ptr)
{
	factory = factory_ptr;
}
