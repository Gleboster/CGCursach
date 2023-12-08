#include "MainWindow.h"
#include "Viewport.h"
#include "TransformPanel.h"

namespace Window {

	ATransformPanel^ MainWindow::GetTransformPanel()
	{
		return _transformPanel;
	}

	AViewPort^ MainWindow::GetViewport()
	{
		return _viewPort;
	}

	void MainWindow::InitializeComponent(void)
	{
		this->components = gcnew System::ComponentModel::Container();
		this->WindowState = FormWindowState::Maximized;
		this->MaximizeBox = false;
		this->Width = Screen::PrimaryScreen->Bounds.Width;
		this->Height = Screen::PrimaryScreen->Bounds.Height;
		this->Text = L"";
		this->Padding = System::Windows::Forms::Padding(0);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	}

	void MainWindow::InitializeViewport(void)
	{
		_viewPort = gcnew Viewport();
		_viewPort->Size = Drawing::Size(this->Width * partViewport, this->Height);
		_viewPort->Location = Drawing::Point(0, 0);
		Controls->Add(_viewPort);
	}

	void MainWindow::InitializeTransformPanel(void)
	{
		_transformPanel = gcnew TransformPanel();
		_transformPanel->Size = Drawing::Size(this->Width * (1 - partViewport), this->Height);
		_transformPanel->Location = Drawing::Point(this->Width * partViewport, 0);
		Controls->Add(_transformPanel);
	}
}