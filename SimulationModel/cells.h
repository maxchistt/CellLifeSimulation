#pragma once
#include <vector>
#include "structs.h"

#define BASIC_CELL_SIZE				6;
#define BASIC_FEED_DAMAGE			1;
#define BASIC_START_FOOD_AMOUNT		30;
#define BASIC_MAX_FOOD_AMOUNT		100;
#define BASIC_MAX_SPEED				10;
#define BASIC_DETECT_RADIUS			90;
#define BASIC_FEEDS_TO_DUPLICATE	10;
#define STOPING_PARAM				1.1;
#define DUPLICATE_CHANSE_PERCENT	25;

namespace SimulationModel {
	class Simulation;
	namespace Cells {
		class Cell
		{
		protected:
			struct CellOptions {
				const int feed_damage = BASIC_FEED_DAMAGE;
				const int max_food = BASIC_MAX_FOOD_AMOUNT;
				const float max_speed = BASIC_MAX_SPEED;
				const float detect_radius = BASIC_DETECT_RADIUS;
				const int feeds_to_duplicate = BASIC_FEEDS_TO_DUPLICATE;
				const float stoping_param = STOPING_PARAM;
				const int dupl_chanse_percent = DUPLICATE_CHANSE_PERCENT;
			};
			int food = BASIC_START_FOOD_AMOUNT;
			structs::Vect2D<float> position{ 0,0 };
			structs::Vect2D<float> speed{ 0,0 };
			CellOptions options;
			Simulation* parentField = nullptr;
			int size = BASIC_CELL_SIZE;
			
			void checkSpeed();
			void checkBorder();
			void move();
			void find();
			void duplicate();
			void foodDamage();
			void accelerate(structs::Vect2D<float> speed_delta);

		public:
			virtual void seeClosest(structs::Vect2D<float> vector);
			virtual void iteract(Cell* other);

			bool isAlive();
			structs::Vect2D<float> getPosition();
			int getSearchRadius();
			int getSize();
			int beEaten();
			void eat(int food);

			Cell(Simulation* parentSimulation);
			Cell(Cell& parentCell);

			void lifeCircle() ;
		};
	};
};
