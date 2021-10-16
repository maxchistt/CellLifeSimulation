#include "CellFactory.h"
#include "SimulationModel.h"

using namespace SimulationModel;
using namespace Cells;
using namespace Structs2D;

struct Plant :CellOptions {
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
		this->neardistance_calcfactor = 50;
		this->dupl_nearsamecells_limit = 10;
	}
};

struct Hunter :CellOptions {
	Hunter() {
		this->color = CellColor::RED;
		this->max_speed = rand() % 10 + 30;
		this->colors_hunt.push_back(CellColor::BLUE);
		this->food_generation = 0;
		this->feed_damage = 1.5;
		this->feed_damage = 2;
		this->size = rand() % 3 + 10;
		this->detect_radius = rand() % 100 + 200;
		this->dupl_chanse_percent = 2;
		this->foods_to_duplicate = 40;
		this->neardistance_calcfactor = 60;
		this->dupl_nearsamecells_limit = 8;
	}
};

void CellFactory::createStartOptions()
{
	for (int i = 0; i < 30; i++)
	{
		this->addOption(Plant(), generationTypes::Plant);
	}

	for (int i = 0; i < 5; i++)
	{
		this->addOption(Planter(), generationTypes::Planter);
	}

	for (int i = 0; i < 2; i++)
	{
		this->addOption(Hunter(), generationTypes::Hunter);
	}
}

void CellFactory::createCell(CellOptions opt)
{
	new Cells::Cell(this->simulation, opt);
}

void CellFactory::addOption(CellOptions option,generationTypes type)
{
	this->options_arr.push_back(generateOption{option,type});
}

CellFactory::CellFactory(Simulation* sim)
{
	this->simulation = sim;
	this->createStartOptions();
	generationTypeSetting = generationTypes::Any;
}

void CellFactory::generateCells()
{
	int size = rand() % 40 + 1;
	generateCells(size);
}

void CellFactory::generateCells(int n)
{
	std::vector<CellOptions> cellOptionsArr;
	for (auto option : options_arr) {
		if (generationTypeSetting == generationTypes::Any || option.type == generationTypeSetting)cellOptionsArr.push_back(option.options);
	}
	if (cellOptionsArr.size() > 0) {
		for (int i = 0; i < n; i++) {
			int opt_id = rand() % cellOptionsArr.size();
			createCell(cellOptionsArr[opt_id]);
		}
	}
}

void CellFactory::setGenerationType(int type)
{
	switch (type)
	{
	case 1:
		generationTypeSetting = generationTypes::Plant;
		break;
	case 2:
		generationTypeSetting = generationTypes::Planter;
		break;
	case 3:
		generationTypeSetting = generationTypes::Hunter;
		break;
	default:
		generationTypeSetting = generationTypes::Any;
		break;
	}
}
