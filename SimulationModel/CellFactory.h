#pragma once
#include "Cell.h"

namespace SimulationModel {
	namespace Cells {

		class CellFactory
		{
			Simulation* simulation;
			std::vector<CellOptions> options_arr;
			void createStartOptions();
			void createCell(CellOptions opt);
		public:
			void addOption(Cells::CellOptions option);
			void generate();
			void generate(int n);
			CellFactory(Simulation* sim);
		};
	}
}
