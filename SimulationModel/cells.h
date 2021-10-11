#pragma once
#include <vector>
#include "structs.h"

#define BASIC_CELL_SIZE				3;
#define BASIC_FEED_DAMAGE			1;
#define BASIC_START_FOOD_AMOUNT		30;
#define BASIC_MAX_FOOD_AMOUNT		100;
#define BASIC_MAX_SPEED				10;
#define BASIC_DETECT_RADIUS			90;
#define BASIC_FEEDS_TO_DUPLICATE	40;

namespace SimulationModel {
	class Simulation;
	namespace Cells {
		class Cell
		{
		protected:
			struct CellOptions {
				const int feed_damage = BASIC_FEED_DAMAGE;
				const int max_food = BASIC_MAX_FOOD_AMOUNT;
				const int max_speed = BASIC_MAX_SPEED;
				const int detect_radius = BASIC_DETECT_RADIUS;
				const int feeds_to_duplicate = BASIC_FEEDS_TO_DUPLICATE;
			};
			CellOptions options;
			Simulation* parentField = nullptr;
			int size = BASIC_CELL_SIZE;
			int food = BASIC_START_FOOD_AMOUNT;
			structs::Vect2D<int> position{ 0,0 };
			structs::Vect2D<int> speed{ 0,0 };
			void checkSpeed();
			void checkBorder();
			void move();
			void find();
			void duplicate();
			void foodDamage();
			void die();
			void accelerate(structs::Vect2D<int> speed_delta);

		public:
			virtual void seeClosest(structs::Vect2D<int> vector);
			virtual void iteract(Cell* other);

			structs::Vect2D<int> getPosition();
			int getSearchRadius();
			int getSize();
			int beEaten();
			void eat(int food);

			Cell(Simulation* parentSimulation);
			Cell(Cell& parentCell);

			void lifeCircle() {
				find();
				move();
				duplicate();
				foodDamage();
			};
		};
	};
};
