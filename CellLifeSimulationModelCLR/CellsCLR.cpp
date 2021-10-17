#include "pch.h"
#include "CellsCLR.h"

using namespace CellLifeSimulationModelCLR;
using namespace CellsCLR;
using namespace SimulationModel;

void CellFactoryCLR::generateCells(int amount)
{
	factory->generateCells(amount);
}

void CellFactoryCLR::setGenerationType(int typeId)
{
	factory->setGenerationType(typeId);
}

CellFactoryCLR::CellFactoryCLR(Cells::CellFactory* factory_ptr)
{
	factory = factory_ptr;
}
