#pragma once
#include "Panel.h"
#include "OutputBox.h"
#include "MVC.h"

using namespace MVC;

namespace CGCursach {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
		FormPanelInput::Panel^ _panel;
		OutputBox^ _outputBox;

		const double partDisplayOut = 0.8;
	public:

		MyForm()
		{
			InitializeComponent();

			InitializeInputPanel();

			InitializeOutputDisplay();
		}

		property FormPanelInput::Panel^ panel { FormPanelInput::Panel^ get() { return _panel; } }
		property OutputBox^ outputBox { OutputBox^ get() { return _outputBox; } }

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->WindowState = FormWindowState::Maximized;
			//this->MaximizeBox = false;
			this->Width = Screen::PrimaryScreen->Bounds.Width;
			this->Height = Screen::PrimaryScreen->Bounds.Height;
			this->Text = L"";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}

		void InitializeInputPanel() {
			_panel = gcnew FormPanelInput::Panel();
			_panel->Size = Drawing::Size(this->Width * (1 - partDisplayOut), this->Height);
			_panel->Location = Drawing::Point(this->Width * partDisplayOut, 0);
			Controls->Add(_panel);
		}
		void InitializeOutputDisplay() {
			_outputBox = gcnew OutputBox();
			_outputBox->Size = Drawing::Size(this->Width * partDisplayOut, this->Height);
			_outputBox->Location = Drawing::Point(0, 0);

			_outputBox->ColorBackground = Color::Black;
			_outputBox->ColorLine = Color::Yellow;
			_outputBox->WidthLine = 2;

			Controls->Add(_outputBox);
		}


	};
}
