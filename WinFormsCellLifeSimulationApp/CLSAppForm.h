#pragma once
#include "SimulationModel.h"
#include "SimDrawController.h"

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
		Simulation* simulation;
		SimDrawController^ controller;

	public:

		void OnInitMainForm();

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


	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ actionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ generateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem_add10;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem_add30;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem_add70;
	private: System::Windows::Forms::ToolStripMenuItem^ clearToolStripMenuItem_Clear;
	private: System::Windows::Forms::ToolStripMenuItem^ playPauseToolStripMenuItem;









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
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->actionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->generateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem_add10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem_add30 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem_add70 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem_Clear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->playPauseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(0, 28);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(582, 325);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->SizeChanged += gcnew System::EventHandler(this, &CLSAppForm::image_resize);
			// 
			// timer
			// 
			this->timer->Interval = 200;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->actionsToolStripMenuItem,
					this->playPauseToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(582, 28);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// actionsToolStripMenuItem
			// 
			this->actionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->generateToolStripMenuItem,
					this->clearToolStripMenuItem_Clear
			});
			this->actionsToolStripMenuItem->Name = L"actionsToolStripMenuItem";
			this->actionsToolStripMenuItem->Size = System::Drawing::Size(72, 24);
			this->actionsToolStripMenuItem->Text = L"Actions";
			// 
			// generateToolStripMenuItem
			// 
			this->generateToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem_add10,
					this->toolStripMenuItem_add30, this->toolStripMenuItem_add70
			});
			this->generateToolStripMenuItem->Name = L"generateToolStripMenuItem";
			this->generateToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->generateToolStripMenuItem->Text = L"Generate";
			// 
			// toolStripMenuItem_add10
			// 
			this->toolStripMenuItem_add10->Name = L"toolStripMenuItem_add10";
			this->toolStripMenuItem_add10->Size = System::Drawing::Size(224, 26);
			this->toolStripMenuItem_add10->Text = L"10";
			this->toolStripMenuItem_add10->Click += gcnew System::EventHandler(this, &CLSAppForm::toolStripMenuItem_add10_Click);
			// 
			// toolStripMenuItem_add30
			// 
			this->toolStripMenuItem_add30->Name = L"toolStripMenuItem_add30";
			this->toolStripMenuItem_add30->Size = System::Drawing::Size(224, 26);
			this->toolStripMenuItem_add30->Text = L"30";
			this->toolStripMenuItem_add30->Click += gcnew System::EventHandler(this, &CLSAppForm::toolStripMenuItem_add30_Click);
			// 
			// toolStripMenuItem_add70
			// 
			this->toolStripMenuItem_add70->Name = L"toolStripMenuItem_add70";
			this->toolStripMenuItem_add70->Size = System::Drawing::Size(224, 26);
			this->toolStripMenuItem_add70->Text = L"70";
			this->toolStripMenuItem_add70->Click += gcnew System::EventHandler(this, &CLSAppForm::toolStripMenuItem_add70_Click);
			// 
			// clearToolStripMenuItem_Clear
			// 
			this->clearToolStripMenuItem_Clear->Name = L"clearToolStripMenuItem_Clear";
			this->clearToolStripMenuItem_Clear->Size = System::Drawing::Size(224, 26);
			this->clearToolStripMenuItem_Clear->Text = L"Clear";
			this->clearToolStripMenuItem_Clear->Click += gcnew System::EventHandler(this, &CLSAppForm::clearToolStripMenuItem_Clear_Click);
			// 
			// playPauseToolStripMenuItem
			// 
			this->playPauseToolStripMenuItem->Name = L"playPauseToolStripMenuItem";
			this->playPauseToolStripMenuItem->Size = System::Drawing::Size(93, 24);
			this->playPauseToolStripMenuItem->Text = L"Play/Pause";
			this->playPauseToolStripMenuItem->Click += gcnew System::EventHandler(this, &CLSAppForm::playPauseToolStripMenuItem_Click);
			// 
			// CLSAppForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 17);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 353);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"CLSAppForm";
			this->Text = L"Cell Life Simulation";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void image_resize(System::Object^ sender, System::EventArgs^ e);
	private: System::Void toolStripMenuItem_add10_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void toolStripMenuItem_add30_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void toolStripMenuItem_add70_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void clearToolStripMenuItem_Clear_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void playPauseToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}
