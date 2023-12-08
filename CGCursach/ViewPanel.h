#pragma once
#include "Manipulations.h"
#include "Vector3.h"
#include "InputPanel.h"

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

ref class ViewPanel : UserControl {
	TransformBoxes^ transformableBoxes;
	int height = 0;

	Drawing::Font^ _fontTitleManipulation = gcnew Drawing::Font("Verdana", 12, Drawing::FontStyle::Bold);
	Drawing::Font^ _fontTitleCoordinate = gcnew Drawing::Font("Verdana", 10, Drawing::FontStyle::Regular);

public:
	ViewPanel(TransformBoxes^ boxes)
	{
		transformableBoxes = boxes;
		ArrangeBoxes();
		Height = height;
	}

	void OnSizeChanged(EventArgs^ ea) override {
		UserControl::OnSizeChanged(ea);
		Controls->Clear();
		ArrangeBoxes();
	};

	void FillTransform(Dictionary<Manipulation, Vector3>^ rations);

private:
	void ArrangeBoxes();
	void SetManipulationBox(Manipulation manipulation, ManipulationBoxes^ boxes);

	Control^ SetTitle(Manipulation manipulation);
	Label^ GetDefaultTitleManipulation(Manipulation manipulation);
	Label^ GetDefaultTitleCoordinate(Coordinate coordinate);

	Control^ SetBoxes(ManipulationBoxes^ boxes);
};