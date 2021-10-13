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
		int timer_scale_counter = 0, quality_scale_counter = 0;

		Color convertColor(Cells::CellColor cell_color);
		void draw(std::vector<drawEntity> entities);
		void redraw();
		void connectTimer();
		Void tick(System::Object^ sender, System::EventArgs^ e);
	public:
		void fitSimSize();
		void setTimeSettings(int interval, int timelapse);
		void start();
		void stop();
		bool timerEnabled();
		void clear();
		void generateCells();
		void generateCells(int n);
		void changeQuality(float factor);
		void changeTimerSpeed(float factor);

		SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox, Windows::Forms::Timer^ timer);
		SimDrawController(SimulationModel::Simulation* sim, Windows::Forms::PictureBox^ pictureBox);
	};
}
