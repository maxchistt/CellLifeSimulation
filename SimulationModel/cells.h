#pragma once
#include <vector>
#include "structs.h"

#define BASIC_CELL_SIZE				10;
#define BASIC_FEED_DAMAGE			1;
#define BASIC_FOOD_GENERATION		0.1;
#define BASIC_START_FOOD_AMOUNT		30;
#define BASIC_MAX_FOOD_AMOUNT		100;
#define BASIC_MAX_SPEED				10;
#define BASIC_DETECT_RADIUS			190;
#define BASIC_FEEDS_TO_DUPLICATE	10;
#define STOPING_PARAM				1.1;
#define DUPLICATE_CHANSE_PERCENT	25;

namespace SimulationModel {
	class Simulation;
	namespace Cells {
		enum class CellColor
		{
			RED, GREEN, BLUE, GRAY, ORANGE, YELLOW, BROWN
		};

		struct CellOptions {
			float feed_damage = BASIC_FEED_DAMAGE;
			float max_food = BASIC_MAX_FOOD_AMOUNT;
			float max_speed = BASIC_MAX_SPEED;
			float detect_radius = BASIC_DETECT_RADIUS;
			int feeds_to_duplicate = BASIC_FEEDS_TO_DUPLICATE;
			float stoping_param = STOPING_PARAM;
			int dupl_chanse_percent = DUPLICATE_CHANSE_PERCENT;
			int size = BASIC_CELL_SIZE;
			float food_generation = BASIC_FOOD_GENERATION;
			CellColor color = CellColor::GREEN;
			//CellColor
		};

		class Cell
		{
		protected:
			int food = BASIC_START_FOOD_AMOUNT;
			structs::Vect2D<float> position{ 0,0 };
			structs::Vect2D<float> speed{ 0,0 };
			CellOptions options;
			Simulation* parentField = nullptr;
			int& size = options.size;

			void generate();
			void checkSpeed(structs::Vect2D<float>& speed);
			void checkBorder();
			void move();
			void find();
			void duplicate();
			void foodDamage();
			void accelerate(structs::Vect2D<float> speed_delta);
			void accelerateByVectTarget(structs::Vect2D<float> vectorToPoint, bool inversion = false);

		public:
			virtual void seeClosest(structs::Vect2D<float> vector);
			virtual void iteract(Cell* other);

			bool isAlive();
			structs::Vect2D<float> getPosition();
			int getSearchRadius();
			int getSize();
			CellColor getColor();
			int beEaten();
			void eat(int food);

			Cell(Simulation* parentSimulation);
			Cell(Cell& parentCell);
			Cell(Simulation* parentSimulation, CellOptions options);

			void lifeCircle();
		};
	};
};
