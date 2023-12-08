#pragma once

namespace Window {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace MVCLibrary::Window;

	public ref class MainWindow : public System::Windows::Forms::Form, public IMVCCorrectWindow
	{
	private:
		static const float partViewport = 0.8;

		ATransformPanel^ _transformPanel;
		AViewPort^ _viewPort;
	public:
		MainWindow(void)
		{
			InitializeComponent();
			InitializeViewport();
			InitializeTransformPanel();
		}

		ATransformPanel^ GetTransformPanel() override;
		AViewPort^ GetViewport() override;

	protected:
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

		void OnMouseClick(MouseEventArgs^ e) override
		{
			Console::WriteLine(e->Location);
		}

	private:
		System::ComponentModel::Container^ components;

		void InitializeComponent(void);

		void InitializeTransformPanel(void);
		void InitializeViewport(void);
	};
}
