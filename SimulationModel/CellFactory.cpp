#include "CellFactory.h"

using namespace SimulationModel;
using namespace Cells;
using namespace structs;

struct Plant :CellOptions{
	Plant() {
			this->color = CellColor::GREEN;
			this->max_speed = rand() % 3 + 4;
			this->colors_beware.push_back(CellColor::BLUE);
			this->detect_radius = rand() % 3 + 10;
			this->food_generation = 0.5;
			this->feed_damage = 0.1;
			this->size = rand() % 3 + 5;
			this->dupl_chanse_percent = rand() % 10 + 65;
	}
};

struct Planter :CellOptions {
	Planter() {
		this->color = CellColor::BLUE;
		this->colors_beware.push_back(CellColor::RED);
		this->colors_hunt.push_back(CellColor::GREEN);
		this->size = rand() % 3 + 7;
		this->max_speed = rand() % 6 + 17;
		this->detect_radius = rand() % 60 + 200;
	}
};

struct Hunter :CellOptions {
	Hunter() {
		this->color = CellColor::RED;
		this->max_speed = rand() % 13 + 50;
		this->colors_hunt.push_back(CellColor::BLUE);
		this->food_generation = 0;
		this->feed_damage = 1.5;
		this->size = rand() % 3 + 10;
		this->detect_radius = rand() % 100 + 200;
	}
};

void CellFactory::createStartOptions()
{
	for (int i = 0; i < 7; i++)
	{
		this->addOption(Plant());
	}

	for (int i = 0; i < 5; i++)
	{
		this->addOption(Planter());
	}

	for (int i = 0; i < 2; i++)
	{
		this->addOption(Hunter());
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
