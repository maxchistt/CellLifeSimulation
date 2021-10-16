#pragma once
#include <vector>
#include "Cell.h"

namespace SimulationModel {
	class Simulation;
	namespace Cells {
		class CellFactory
		{
			enum class generationTypes
			{
				Any, Plant, Planter, Hunter
			};
			struct generateOption {
				Cells::CellOptions options;
				generationTypes type;
			};
		private:
			generationTypes generationTypeSetting;
			Simulation* simulation;
			std::vector<generateOption>options_arr;
			void createStartOptions();
			void createCell(Cells::CellOptions opt);
		public:
			void addOption(Cells::CellOptions option, generationTypes type);
			void generateCells();
			void generateCells(int n);
			void setGenerationType(int type);
			CellFactory(Simulation* sim);
		};
	}
}
