#pragma once
#include "InputPanel.h"
#include "ViewPanel.h"

namespace FormPanelInput {

	ref class Panel : UserControl {
	public:
		initonly InputPanel^ inputPanel;
		initonly ViewPanel^ viewPanel;

		Panel()
		{
			inputPanel = gcnew InputPanel();
			Controls->Add(inputPanel);
			viewPanel = gcnew ViewPanel(inputPanel->Boxes);
			Controls->Add(viewPanel);
		}

		void OnSizeChanged(EventArgs^ ea) override {
			UserControl::OnSizeChanged(ea);
			viewPanel->Width = Width * 0.9;
		}

	private:

	};
}