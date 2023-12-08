#include "ViewPanel.h"

void ViewPanel::FillTransform(Dictionary<Manipulation, Vector3>^ rations)
{
	for each (Manipulation manip in Enum::GetValues(Manipulation::typeid))
		for each (Coordinate coord in Enum::GetValues(Coordinate::typeid))
			transformableBoxes[manip]->default[coord]->Text = rations[manip].default[coord].ToString();
}

void ViewPanel::ArrangeBoxes()
{
	height = 0;
	for each (auto tupleboxes in transformableBoxes)
		SetManipulationBox(tupleboxes.Key, tupleboxes.Value);
}

void ViewPanel::SetManipulationBox(Manipulation manipulation, ManipulationBoxes^ boxes)
{
	height += SetTitle(manipulation)->Height;
	height += SetBoxes(boxes)->Height;
	height += 10;
}

Control^ ViewPanel::SetTitle(Manipulation manipulation)
{
	Label^ titleLabel = GetDefaultTitleManipulation(manipulation);
	titleLabel->Location = System::Drawing::Point(0, height);
	this->Controls->Add(titleLabel);
	return titleLabel;
}

Label^ ViewPanel::GetDefaultTitleManipulation(Manipulation manipulation)
{
	Label^ title = gcnew Label();
	title->Font = _fontTitleManipulation;
	title->Text = Enum::GetName(Manipulation::typeid, manipulation);
	title->AutoSize = true;
	return title;
}

Label^ ViewPanel::GetDefaultTitleCoordinate(Coordinate coordinate)
{
	Label^ title = gcnew Label();
	title->Font = _fontTitleCoordinate;
	title->Text = Enum::GetName(Coordinate::typeid, coordinate) + ":";
	title->AutoSize = true;
	return title;
}

Control^ ViewPanel::SetBoxes(ManipulationBoxes^ boxes)
{
	int width = 0;
	int widthBox = Width / boxes->Count;
	Label^ coordTitle;
	for each (auto box in boxes)
	{
		coordTitle = GetDefaultTitleCoordinate(box.Key);
		coordTitle->Location = System::Drawing::Point(width, height);
		Controls->Add(coordTitle);

		width += coordTitle->Width;

		auto textBox = box.Value;
		textBox->Location = System::Drawing::Point(width, height);
		textBox->Size = Drawing::Size(widthBox - coordTitle->Width, coordTitle->Height);
		Controls->Add(textBox);
		width += textBox->Width;
	}
	return coordTitle;
}


