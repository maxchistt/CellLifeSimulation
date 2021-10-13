#include "Cell.h"
#include "SimulationModel.h"

using namespace SimulationModel;
using namespace Cells;
using namespace structs;

Cell::doType Cell::howToDo(Cell* cell_finder, Cell* cell_to_find)
{
	auto mycolor = cell_to_find->options.color;

	for (auto color : cell_finder->options.colors_beware)
	{
		if (color == mycolor)return doType::beware;
	}

	for (auto color : cell_finder->options.colors_hunt)
	{
		if (color == mycolor)return doType::hunt;
	}

	return doType::nothing;
}

void Cell::findClosest(Simulation* sim, Cell* cell_finder)
{
	Vect2D<float> resDistVect(cell_finder->getSearchRadius() * 2, cell_finder->getSearchRadius() * 2);
	for (auto cell_to_find : sim->cells)
	{
		doType todo = Cell::howToDo(cell_finder, cell_to_find);
		if (cell_to_find == nullptr || cell_to_find->isAlive() == false || cell_finder == cell_to_find) {
			continue;
		}
		else {
			Vect2D<float> curDistVect = cell_finder->getPosition().getDistanceVect(cell_to_find->getPosition());
			if (curDistVect.getAbs() < cell_finder->getSearchRadius()) {
				if (curDistVect.getAbs() < resDistVect.getAbs()) {
					if (todo == doType::nothing) {
						resDistVect /= static_cast<float>(resDistVect.getAbs() / curDistVect.getAbs()) / 3;
					}
					else {
						resDistVect = curDistVect;
					}
					if (curDistVect.getAbs() < (cell_finder->getSize() + cell_to_find->getSize()) / 2) {
						cell_finder->iteract(cell_to_find, todo, curDistVect);
					}
					else {
						cell_finder->seeClosest(curDistVect, todo);
					}
				}
			}
		}
	}
}

void Cell::generate()
{
	this->food += options.food_generation / parentField->timelapse;
}

void Cell::checkSpeed(Vect2D<float>& speed)
{
	if (speed.getAbs() > options.max_speed) {
		const double ofMax = speed.getAbs() / options.max_speed;
		speed /= ofMax;
	}
}

void Cell::checkBorder()
{
	if (position.x >= parentField->fieldSize.x) {
		position.x = parentField->fieldSize.x - 1;
		speed.x = -0.5;
	};
	if (position.y >= parentField->fieldSize.y) {
		position.y = parentField->fieldSize.y - 1;
		speed.y = -0.5;
	};
	if (position.x < 0) {
		position.x = 0;
		speed.x = 0.5;
	};
	if (position.y < 0) {
		position.y = 0;
		speed.y = 0.5;
	};
}

void Cell::move()
{
	accelerate();
	auto speed_lapsed = speed;
	speed_lapsed /= parentField->timelapse;
	position += speed_lapsed;
	checkBorder();
	speed /= 1 + options.stoping_param / parentField->timelapse;
}

void Cell::find()
{
	Cell::findClosest(parentField, this);
}

void Cell::seeClosest(structs::Vect2D<float> vector, doType how)
{
	if (how == doType::hunt)accelerateByVectTarget(vector, false);
	else if (how == doType::beware)accelerateByVectTarget(vector, true);
}

void Cell::duplicate()
{
	if (isAlive() && food > options.foods_to_duplicate) {
		if (rand() % static_cast<int>(100 * parentField->timelapse) < options.dupl_chanse_percent) new Cell(*this);
	};
}

float randPositionOffset(int size) {
	return (rand() % size / 2 + size / 2) * (rand() % 10 < 5 ? 1 : -1);
};

void Cell::iteract(Cell* other, doType how, Vect2D<float> vector)
{
	if (how == doType::hunt) {
		if (isAlive()) eat(other->beEaten());
	}
	else {
		if (how == doType::nothing) {
			if (vector.getAbs() > size / 2)return;
			vector /= 2;
		}
		if (vector.getAbs() == 0) {
			vector.x = randPositionOffset(this->size);
			vector.y = randPositionOffset(this->size);
		}
		accelerateByVectTarget(vector, true);
	}
}

void Cell::foodDamage()
{
	food -= options.feed_damage / parentField->timelapse;
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

void Cell::accelerate()
{
	checkSpeed(acceleration);
	acceleration /= parentField->timelapse;
	speed += acceleration;
	checkSpeed(speed);
	acceleration *= 0;
}

void Cell::accelerateByVectTarget(structs::Vect2D<float> vectorToPoint, bool inversion)
{
	auto speed_delta = vectorToPoint;
	if (speed_delta.getAbs() == 0) {
		return;
	};

	speed_delta /= speed_delta.getAbs() / options.max_speed;

	double degree = 2;
	//double compression_factor = 1;
	double stretch_factor = 1.2;

	double ratio = 1.0 - (vectorToPoint.getAbs() / this->options.detect_radius);

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

Cell::Cell(Simulation* parentSimulation)
{
	this->parentField = parentSimulation;
	parentSimulation->add(this);

	this->position = Vect2D<float>{
		static_cast<float>(rand() % (parentSimulation->fieldSize.x ? parentSimulation->fieldSize.x : 1)),
		static_cast<float>(rand() % (parentSimulation->fieldSize.y ? parentSimulation->fieldSize.y : 1))
	};
}

Cell::Cell(Cell& parentCell) : Cell(parentCell.parentField)
{
	this->options = parentCell.options;
	this->position = parentCell.getPosition();
	parentCell.food /= 2;
	this->food = parentCell.food;
	this->position += Vect2D<float>{
		randPositionOffset(this->size),
			randPositionOffset(this->size)
	};
}

Cell::Cell(Simulation* parentSimulation, CellOptions options) : Cell(parentSimulation)
{
	this->options = options;
}

void Cell::lifeCircle()
{
	if (isAlive()) {
		duplicate();
		find();
		move();
		generate();
		foodDamage();
	}
}

