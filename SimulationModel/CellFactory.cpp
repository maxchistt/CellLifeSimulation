#include "CellFactory.h"

using namespace SimulationModel;
using namespace Cells;
using namespace structs;

CellOptions plant() {
	CellOptions plant = CellOptions();
	plant.color = CellColor::GREEN;
	plant.max_speed = rand()%3+4;
	plant.colors_beware.push_back(CellColor::BLUE);
	plant.detect_radius = rand() % 3+10;
	plant.food_generation = 0.5;
	plant.feed_damage = 0.1;
	plant.size = rand() % 3 + 5;
	plant.dupl_chanse_percent = rand() % 10+ 65;

	return plant;
}

CellOptions planter() {
	CellOptions planter = CellOptions();
	planter.color = CellColor::BLUE;
	planter.colors_beware.push_back(CellColor::RED);
	planter.colors_hunt.push_back(CellColor::GREEN);
	planter.size = rand() % 3 +7;
	planter.max_speed = rand() % 3+17;

	return planter;
}

CellOptions hunter() {
	CellOptions hunter = CellOptions();
	hunter.color = CellColor::RED;
	hunter.max_speed = rand() % 13 +50;
	hunter.colors_hunt.push_back(CellColor::BLUE);
	hunter.food_generation = 0;
	hunter.feed_damage = 1.5;
	hunter.size = rand() % 3+10;

	return hunter;
}

void CellFactory::createStartOptions()
{
	for (int i = 0; i < 7; i++)
	{
		this->addOption(plant());
	}

	for (int i = 0; i < 4; i++)
	{
		this->addOption(planter());
	}

	for (int i = 0; i < 2; i++)
	{
		this->addOption(hunter());
	}
	
}

void CellFactory::createCell(CellOptions opt)
{
	new Cells::Cell(this->simulation, opt);
}

void CellFactory::addOption(CellOptions option)
{
	this->options_arr.push_back(option);
}

CellFactory::CellFactory(Simulation* sim)
{
	this->simulation = sim;
	this->createStartOptions();
}

void CellFactory::generate()
{
	int size = rand()% 40 +1;
	
	for (int i = 0; i < size; i++) {
		int opt_id = rand() % this->options_arr.size();
		createCell(options_arr[opt_id]);
	}
}
