#include "pch.h"
#include "Cell.h"
#include "SimulationModel.h"

using namespace SimulationModel;
using namespace Cells;
using namespace Structs2D;

Cell::doType Cell::howToDo(Cell* cell_finder, Cell* cell_to_find)
{
	auto mycolor = cell_to_find->dna_options.color;

	for (auto color : cell_finder->dna_options.colors_beware)
	{
		if (color == mycolor)return doType::beware;
	}

	for (auto color : cell_finder->dna_options.colors_hunt)
	{
		if (color == mycolor)return doType::hunt;
	}

	return doType::nothing;
}

void Cell::scanClosestCellsOnField()
{
	Vect2D<float> resDistVect(this->getSearchRadius() * 2, this->getSearchRadius() * 2);
	this->nearCellsCounter = this->nearSameCellsCounter = 0;
	for (auto other_cell : this->parentSimulation->cells)
	{
		doType todo = Cell::howToDo(this, other_cell);
		if (other_cell == nullptr || other_cell->isAlive() == false || this == other_cell) {
			continue;
		}
		else {
			Vect2D<float> curDistVect = this->getPosition().getDistanceVect(other_cell->getPosition());
			double neardistnce = (static_cast<double>(this->getSize()) + static_cast<double>(other_cell->getSize())) / 2.0;
			if (curDistVect.getAbs() < (neardistnce * this->dna_options.neardistance_calcfactor)) {
				this->nearCellsCounter++;
				if (this->getColor() == other_cell->getColor())this->nearSameCellsCounter++;
			};
			if (curDistVect.getAbs() < this->getSearchRadius()) {
				if (curDistVect.getAbs() < resDistVect.getAbs()) {
					if (todo == doType::nothing) {
						resDistVect /= static_cast<float>(resDistVect.getAbs() / curDistVect.getAbs()) / 3;
					}
					else {
						resDistVect = curDistVect;
					}
					if (curDistVect.getAbs() < neardistnce) {
						this->interactWith(other_cell, todo, curDistVect);
					}
					else {
						this->seeClosest(curDistVect, todo);
					}
				}
			}
		}
	}
}

void Cell::generateFood()
{
	float generatedFood = dna_options.food_generation / (1 + nearCellsCounter * dna_options.foodgen_nearcells_factor);
	this->food += generatedFood / parentSimulation->timelapse;
}

void Cell::checkSpeed(Vect2D<float>& speed)
{
	if (speed.getAbs() > dna_options.max_speed) {
		const double ofMax = speed.getAbs() / dna_options.max_speed;
		speed /= ofMax;
	}
}

void Cell::checkBorder()
{
	if (position.x >= parentSimulation->fieldSize.x - this->getSize() / 2) {
		position.x = (parentSimulation->fieldSize.x - 1) - this->getSize() / 2;
		speed.x = -0.2 * speed.x;
	};
	if (position.y >= parentSimulation->fieldSize.y - this->getSize() / 2) {
		position.y = (parentSimulation->fieldSize.y - 1) - this->getSize() / 2;
		speed.y = -0.2 * speed.y;
	};
	if (position.x < 0 + this->getSize() / 2) {
		position.x = 0 + this->getSize() / 2;
		speed.x = -0.2 * speed.x;
	};
	if (position.y < 0 + this->getSize() / 2) {
		position.y = 0 + this->getSize() / 2;
		speed.y = -0.2 * speed.y;
	};
}

void Cell::move()
{
	accelerate();
	auto speed_lapsed = speed;
	speed_lapsed /= parentSimulation->timelapse;
	position += speed_lapsed;
	checkBorder();
	speed /= 1 + dna_options.stoping_param / parentSimulation->timelapse;
}

void Cell::seeClosest(Vect2D<float> vectorToOther, doType how)
{
	if (how == doType::hunt)accelerateByVectTarget(vectorToOther, false);
	else if (how == doType::beware)accelerateByVectTarget(vectorToOther, true);
}

void Cell::duplicate()
{
	if (isAlive() && food > dna_options.foods_to_duplicate && nearSameCellsCounter < dna_options.dupl_nearsamecells_limit && parentSimulation->cellsCount() < parentSimulation->cellsLimit) {
		if (rand() % static_cast<int>(100 * parentSimulation->timelapse) < dna_options.dupl_chanse_percent) new Cell(*this);
	};
}

float randPositionOffset(int size) {
	return (rand() % size / 2 + size / 2) * (rand() % 10 < 5 ? 1 : -1);
};

void Cell::interactWith(Cell* other, doType how, Vect2D<float> vectorToOther)
{
	if (how == doType::hunt) {
		if (isAlive()) eat(other);
	}
	else {
		if (how == doType::nothing) {
			if (vectorToOther.getAbs() > (getSize() + other->getSize()) / 3)return;
			if (vectorToOther.getAbs() > (getSize() + other->getSize()) / 4)vectorToOther /= 2;
		}
		if (vectorToOther.getAbs() == 0) {
			vectorToOther.x = randPositionOffset(this->getSize());
			vectorToOther.y = randPositionOffset(this->getSize());
		}
		accelerateByVectTarget(vectorToOther, true);
	}
}

void Cell::foodDamage()
{
	food -= dna_options.feed_damage / parentSimulation->timelapse;
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
	return dna_options.detect_radius;
}

int Cell::getSize()
{
	return dna_options.size;
}

CellColor Cell::getColor()
{
	return this->dna_options.color;
}

void Cell::accelerate()
{
	checkSpeed(acceleration);
	acceleration /= parentSimulation->timelapse;
	speed += acceleration;
	checkSpeed(speed);
	acceleration *= 0;
}

void Cell::accelerateByVectTarget(Vect2D<float> vectorToPoint, bool inversion)
{
	auto speed_delta = vectorToPoint;
	if (speed_delta.getAbs() == 0) {
		return;
	};

	speed_delta /= speed_delta.getAbs() / dna_options.max_speed;

	double degree = 2;
	//double compression_factor = 1;
	double stretch_factor = 1.2;

	double ratio = 1.0 - (vectorToPoint.getAbs() / this->dna_options.detect_radius);

	ratio = 1.0 + (ratio - 1) / stretch_factor; //stretch
	ratio = pow(ratio, degree); //power
	//ratio = 1.0 + (ratio - 1.0) / compression_factor; //compress

	speed_delta *= ratio;

	checkSpeed(speed_delta);

	if (inversion)speed_delta *= -1;

	acceleration += speed_delta;
	checkSpeed(acceleration);
}

float Cell::beEaten()
{
	float res = isAlive() ? this->food : 0;
	this->food -= res;
	return res;
}

void Cell::eat(float food)
{
	if (isAlive())this->food += food;
}

void Cell::eat(Cell* other)
{
	if (isAlive())this->eat(other->beEaten());
}

Cell::Cell(Simulation* parentSimulation)
{
	this->parentSimulation = parentSimulation;
	parentSimulation->add(this);
}

Cell::Cell(Cell& parentCell) : Cell(parentCell.parentSimulation)
{
	this->dna_options = parentCell.dna_options;
	this->position = parentCell.getPosition();
	parentCell.food /= 2;
	this->food = parentCell.food;
	this->position += Vect2D<float>{
		randPositionOffset(this->getSize()),
			randPositionOffset(this->getSize())
	};
}

Cell::Cell(Simulation* parentSimulation, CellDNA dna_options) : Cell(parentSimulation)
{
	this->dna_options = dna_options;
	this->food = (BASIC_START_FOOD_AMOUNT * 2 + dna_options.feed_damage * 10 + dna_options.foods_to_duplicate) / 4;
	this->position = Vect2D<float>{
	static_cast<float>(rand() % (parentSimulation->fieldSize.x ? parentSimulation->fieldSize.x : 1)),
	static_cast<float>(rand() % (parentSimulation->fieldSize.y ? parentSimulation->fieldSize.y : 1))
	};
}

void Cell::lifeCircle()
{
	if (isAlive()) {
		scanClosestCellsOnField();
		move();
		generateFood();
		foodDamage();
		duplicate();
	}
}

