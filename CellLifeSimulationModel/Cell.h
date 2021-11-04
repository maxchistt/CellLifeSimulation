#pragma once
#include <vector>
#include "Structs2D.h"

#define BASIC_CELL_SIZE					10
#define BASIC_FEED_DAMAGE				1
#define BASIC_FOOD_GENERATION			0.1
#define BASIC_START_FOOD_AMOUNT			30
#define BASIC_MAX_FOOD_AMOUNT			100
#define BASIC_MAX_SPEED					10
#define BASIC_DETECT_RADIUS				190
#define FOODS_TO_DUPLICATE				10
#define STOPING_FACTOR					0.1
#define DUPLICATE_CHANSE_PERCENT		10
#define DUPLICATE_NEARSAMECELLS_LIMIT	35
#define FOODGEN_NEARCELLS_FACTOR		0.1
#define NEARDISTANCE_CALCFACTOR			14

#define ENUM_CellColors RED, GREEN, BLUE, GRAY, ORANGE, YELLOW, BROWN

namespace SimulationModel {
	class Simulation;
	namespace Cells {
		using namespace Structs2D;

		enum CellColor { ENUM_CellColors };
		static const CellColor ALL_CELL_COLORS[] = { ENUM_CellColors };

		struct CellDNA {
			float feed_damage = BASIC_FEED_DAMAGE;
			float max_food = BASIC_MAX_FOOD_AMOUNT;
			float max_speed = BASIC_MAX_SPEED;
			float detect_radius = BASIC_DETECT_RADIUS;
			float foods_to_duplicate = FOODS_TO_DUPLICATE;
			float stoping_factor = STOPING_FACTOR;
			int dupl_chanse_percent = DUPLICATE_CHANSE_PERCENT;
			int dupl_nearsamecells_limit = DUPLICATE_NEARSAMECELLS_LIMIT;
			float foodgen_nearcells_factor = FOODGEN_NEARCELLS_FACTOR;
			float neardistance_calcfactor = NEARDISTANCE_CALCFACTOR;
			int size = BASIC_CELL_SIZE;
			float food_generation = BASIC_FOOD_GENERATION;
			CellColor color = CellColor::BROWN;
			std::vector<CellColor> colors_beware{  };
			std::vector<CellColor> colors_hunt{  };
		};

		class Cell
		{
		private:
			static enum class doType { nothing = false, beware = 1, hunt = 2 };
			static doType howToDo(Cell* cell_finder, Cell* cell_to_find);
			float food = BASIC_START_FOOD_AMOUNT;
			Vect2D<float> position{ 0,0 };
			Vect2D<float> speed{ 0,0 };
			Vect2D<float> acceleration{ 0,0 };
			CellDNA dna_options;
			Simulation* parentSimulation = nullptr;
			int nearCellsCounter = 0, nearSameCellsCounter = 0;
			void generateFood();
			void checkSpeed(Vect2D<float>& speed);
			void checkBorder();
			void move();
			void duplicate();
			void foodDamage();
			void accelerate();
			void accelerateByVectTarget(Vect2D<float> vectorToPoint, bool inversion = false);
			void scanClosestCellsOnField();
			virtual void seeClosest(Vect2D<float> vectorToOther, doType how);
			virtual void interactWith(Cell* other, doType how, Vect2D<float> vectorToOther = Vect2D<float>{ 0,0 });
			int getSearchRadius();
			void eat(float food);
			void eat(Cell* other);
			float beEaten();
			Cell(Simulation* parentSimulation);
			Cell(Cell& parentCell);
		public:
			bool isAlive();
			Vect2D<float> getPosition();
			int getSize();
			CellColor getColor();
			void lifeCircle();
			Cell(Simulation* parentSimulation, CellDNA dna_options);
		};
	};
};
