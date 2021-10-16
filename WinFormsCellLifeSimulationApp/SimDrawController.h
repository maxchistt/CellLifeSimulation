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
		Simulation* sim = nullptr;
		PictureBox^ pictureBox;
		Timer^ timer;
		Cells::CellFactory* cellFactory();
		String^ header = "";

		Color convertColor(Cells::CellColor cell_color);
		void draw(std::vector<drawEntity> entities);
		void redraw();
		void connectTimer();
		Void tick(System::Object^ sender, System::EventArgs^ e);
		void catchException(Exception^ e);
	public:
		void fitSimSize();
		void time_setTimeSettings(int interval, float timelapse);
		void start();
		void stop();
		bool timerEnabled();
		void clear();
		void generateCells();
		void generateCells(int n);
		void time_changeQuality(float factor);
		void time_changeTimerSpeed(float factor);
		void setCellsLimit(int cellslimit);
		void setGenerationType(int type);

		SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox, Windows::Forms::Timer^ timer);
		SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox);
	};
}
