#include "pch.h"
#include "CellFactory.h"
#include "SimulationModel.h"

using namespace SimulationModel;
using namespace Cells;
using namespace Structs2D;

struct PlantDNA :CellDNA {
	PlantDNA() {
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

struct PlanterDNA :CellDNA {
	PlanterDNA() {
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

struct HunterDNA :CellDNA {
	HunterDNA() {
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
		this->addOption(PlantDNA(), basicGenerationTypes::Plant);
	}

	for (int i = 0; i < 5; i++)
	{
		this->addOption(PlanterDNA(), basicGenerationTypes::Planter);
	}

	for (int i = 0; i < 2; i++)
	{
		this->addOption(HunterDNA(), basicGenerationTypes::Hunter);
	}
}

void CellFactory::createCell(CellDNA opt)
{
	new Cells::Cell(this->simulation, opt);
}

void CellFactory::addOption(CellDNA option, int typeID)
{
	this->options_arr.push_back(generateOption{ option,typeID });
}

void CellFactory::clearOptions()
{
	this->options_arr.clear();
}

std::vector<CellFactory::generateOption> CellFactory::getOptions()
{
	return options_arr;
}

void CellFactory::deleteOption(int index)
{
	if (index >= 0 && index < options_arr.size()) {
		options_arr.erase(options_arr.begin() + index);
	}
}

CellFactory::CellFactory(Simulation* sim)
{
	this->simulation = sim;
	this->createStartOptions();
	generationTypeID_Setting = basicGenerationTypes::Any;
}

void CellFactory::generateCells()
{
	int size = rand() % 40 + 1;
	generateCells(size);
}

void CellFactory::generateCells(int n)
{
	std::vector<CellDNA> cellDnaOptionsArr;

	for (auto option : options_arr) {
		if (generationTypeID_Setting == basicGenerationTypes::Any || option.typeID == generationTypeID_Setting) {
			cellDnaOptionsArr.push_back(option.dna_options);
		}
	}

	if (cellDnaOptionsArr.size() > 0) {
		for (int i = 0; i < n; i++) {
			int opt_id = rand() % cellDnaOptionsArr.size();
			createCell(cellDnaOptionsArr[opt_id]);
		}
	}
}

void CellFactory::setGenerationType(int typeID)
{
	bool contains = false;

	for (auto option : options_arr) {
		if (option.typeID == typeID) contains = true;
	}

	if (contains) {
		generationTypeID_Setting = typeID;
	}
	else {
		generationTypeID_Setting = basicGenerationTypes::Any;
	}
}
