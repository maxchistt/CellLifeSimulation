#pragma once
#include <vector>
#include "Cell.h"

namespace SimulationModel {
	class Simulation;
	namespace Cells {
		class CellFactory
		{
		public:
			struct GenerateOption {
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
			std::vector<GenerateOption>options_arr;
			void createCell(Cells::CellDNA opt);
		public:
			void addOption(Cells::CellDNA dna_option, int typeID);
			void addOption(GenerateOption option);
			void updateOption(int index, GenerateOption option);
			void clearOptions();
			std::vector<GenerateOption> getOptions();
			void deleteOption(int index);

			void generateCells();
			void generateCells(int n);
			void setGenerationType(int typeID);
			int getGenerationType();
			CellFactory(Simulation* sim);
		};
	}
}
