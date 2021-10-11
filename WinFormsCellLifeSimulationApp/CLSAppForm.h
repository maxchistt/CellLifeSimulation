#pragma once
#include "SimulationModel.h"

namespace WinFormsCellLifeSimulationApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ CLSAppForm
	/// </summary>
	public ref class CLSAppForm : public System::Windows::Forms::Form
	{
	private:
		SimulationModel::Simulation* sim = nullptr;
	public:

		void OnInitMainForm();
		void draw(Windows::Forms::PictureBox^ pictureBox, std::vector<SimulationModel::drawEntity> entities);
		void redraw();
		CLSAppForm(void)
		{
			InitializeComponent();
			OnInitMainForm();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~CLSAppForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox;

	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(23, 38);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(962, 505);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;

			// 
			// CLSAppForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1052, 593);
			this->Controls->Add(this->pictureBox);
			this->Name = L"CLSAppForm";
			this->Text = L"CLSAppForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


	};
}
