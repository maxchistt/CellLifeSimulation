#pragma once
#include "SimulationModel.h"

using namespace System;

namespace SimulationModelCLR {
	namespace CellsCLR {
		public ref class CellFactoryCLR sealed
		{
		private:
			SimulationModel::Cells::CellFactory* factory;
		public:
			void generateCells(int amount);
			void setGenerationType(int typeId);
			CellFactoryCLR(SimulationModel::Cells::CellFactory* factory_ptr);
		};
	};
};
