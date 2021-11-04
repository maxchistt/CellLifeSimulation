#pragma once
#include <vector>
#include "Cell.h"

namespace SimulationModel {
	class Simulation;
	namespace Cells {
		class CellFactory
		{
			struct generateOption {
				Cells::CellDNA dna_options;
				int typeID;
			};
		protected:
			virtual enum basicGenerationTypes
			{
				Any, Plant, Planter, Hunter
			};
			virtual void createStartOptions();
		private:
			int generationTypeID_Setting;
			Simulation* simulation;
			std::vector<generateOption>options_arr;
			void createCell(Cells::CellDNA opt);
		public:
			void addOption(Cells::CellDNA option, int typeID);
			void clearOptions();
			std::vector<generateOption> getOptions();
			void deleteOption(int index);

			void generateCells();
			void generateCells(int n);
			void setGenerationType(int typeID);
			CellFactory(Simulation* sim);
		};
	}
}
