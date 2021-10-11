#include "cells.h"
#include "SimulationModel.h"

using namespace SimulationModel;
using namespace Cells;
using namespace structs;

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
	speed /= 1.1;
}

void Cell::find()
{
	parentField->findClosest(this);
}

void Cell::seeClosest(structs::Vect2D<int> vector)
{
	accelerate(vector);
}

void Cell::duplicate()
{
	if (isAlive() && food > options.feed_damage * options.feeds_to_duplicate) {
		if (rand() % 10 > 5)new Cell(*this);
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

Vect2D<int> Cell::getPosition()
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

void Cell::accelerate(Vect2D<int> speed_delta)
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
	this->position = Vect2D<int>{
		rand() % (parentSimulation->fieldSize.x),
		rand() % (parentSimulation->fieldSize.y)
	};
}

Cell::Cell(Cell& parentCell) : Cell(parentCell.parentField)
{
	this->position = parentCell.getPosition();
	parentCell.food /= 2;
	this->food = parentCell.food;
	this->position += Vect2D<int>{
		rand() % (this->size * 3 + 1),
			rand() % (this->size * 3 + 1)
	};
}

void Cell::lifeCircle()
{
	if (isAlive()) {
		find();
		move();
		duplicate();
		foodDamage();
	}
	if (!isAlive()) {
		//parentField->cleardied();
	}


}

