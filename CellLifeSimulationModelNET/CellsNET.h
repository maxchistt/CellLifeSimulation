#pragma once
#include "SimulationModel.h"

using namespace System;

namespace SimulationModelNET {
	namespace CellsNET {
		public ref class CellFactoryNET sealed
		{
		private:
			SimulationModel::Cells::CellFactory* factory;
		public:
			void generateCells(int amount);
			void setGenerationType(int typeId);
			CellFactoryNET(SimulationModel::Cells::CellFactory* factory_ptr);
		};
	};
};
