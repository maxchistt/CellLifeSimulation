#pragma once
#include "SimulationModel.h"

namespace WinFormsCellLifeSimulationApp {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace SimulationModel;

	ref class SimDrawController
	{
	private:
		Simulation * sim;
		PictureBox^ pictureBox ;
		Timer^ timer;
		Color convertColor(Cells::CellColor cell_color);
		void draw(std::vector<drawEntity> entities);
		void fitSimSize();
		void redraw();
		void connectTimer();
		System::Void tick(System::Object^ sender, System::EventArgs^ e);
	public:
		void setTimeSettings(int interval, int timelapse);
		void start();
		void stop();
		void generateCells();
		SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox, Windows::Forms::Timer^ timer);
		SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox);
	};
}