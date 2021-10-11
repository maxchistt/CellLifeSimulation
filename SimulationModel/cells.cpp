#include "cells.h"
#include "SimulationModel.h"

using namespace SimulationModel;
using namespace Cells;
using namespace structs;

void Cell::generate()
{
	this->food += options.food_generation;
}

void Cell::checkSpeed()
{
	if (speed.getAbs() > options.max_speed) {
		const double ofMax = speed.getAbs() / options.max_speed;
		speed /= ofMax;
	}
}

void Cell::checkBorder()
{
	if (position.x > parentField->fieldSize.x) position.x = parentField->fieldSize.x;
	if (position.y > parentField->fieldSize.y) position.y = parentField->fieldSize.y;
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
}

void Cell::move()
{
	position += speed;
	checkBorder();
	speed /= options.stoping_param;
}

void Cell::find()
{
	parentField->findClosest(this);
}

void Cell::seeClosest(structs::Vect2D<float> vector)
{
	accelerate(vector);
}

void Cell::duplicate()
{
	if (isAlive() && food > options.feed_damage * options.feeds_to_duplicate) {
		if (rand() % 100 > options.dupl_chanse_percent)new Cell(*this);
	};
}

void Cell::iteract(Cell* other)
{
	if (isAlive()) eat(other->beEaten());
}

void Cell::foodDamage()
{
	food -= options.feed_damage;
}

bool Cell::isAlive()
{
	return this->food > 0;
}

Vect2D<float> Cell::getPosition()
{
	return position;
}

int Cell::getSearchRadius()
{
	return options.detect_radius;
}

int Cell::getSize()
{
	return size;
}

CellColor Cell::getColor()
{
	return this->options.color;
}

void Cell::accelerate(Vect2D<float> speed_delta)
{
	speed += speed_delta;
	checkSpeed();
}

int Cell::beEaten()
{
	int res = isAlive() ? this->food : 0;
	this->food -= res;
	return res;
}

void Cell::eat(int food)
{
	if (isAlive())this->food += food;
}

Cell::Cell(Simulation* parentSimulation)
{
	this->parentField = parentSimulation;
	parentSimulation->add(this);

	this->position = Vect2D<float>{
		(float)(rand() % (parentSimulation->fieldSize.x)),
		(float)(rand() % (parentSimulation->fieldSize.y))
	};

	//this->size = options.size;
}

Cell::Cell(Cell& parentCell) : Cell(parentCell.parentField)
{
	this->options = parentCell.options;
	this->position = parentCell.getPosition();
	parentCell.food /= 2;
	this->food = parentCell.food;
	this->position += Vect2D<float>{
		(float)(rand() % (this->size * 3 + 1)),
			(float)(rand() % (this->size * 3 + 1))
	};
	//this->size = options.size;
}

Cell::Cell(Simulation* parentSimulation, CellOptions options) : Cell(parentSimulation)
{
	this->options = options;
}

void Cell::lifeCircle()
{
	if (isAlive()) {
		generate();
		find();
		move();
		duplicate();
		foodDamage();
	}
}

