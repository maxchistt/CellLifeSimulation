#pragma once
#include "Cell.h"

namespace SimulationModel {
	namespace Cells {
		enum class generationTypes
		{
			Any, Plant, Planter, Hunter
		};
		class CellFactory
		{
			struct generateOption {
				CellOptions cellOptions;
				generationTypes type;
			};
			generationTypes generationTypeSetting = generationTypes::Any;
			Simulation* simulation;
			std::vector<generateOption> options_arr;
			void createStartOptions();
			void createCell(CellOptions opt);
		public:
			void addOption(Cells::CellOptions option, generationTypes type);
			void generate();
			void generate(int n);
			void setGenerationType(int type);
			CellFactory(Simulation* sim);
		};
	}
}
