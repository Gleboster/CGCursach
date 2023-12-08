#include "TransformPanel.h"

//using namespace System::Collections::Generic;

namespace Window {

	void TransformPanel::ShowTransform(TransformGrid<TransformValueAbsolute^>^ transformGrid)
	{
		for each (Transformation transformation in Enum::GetValues(Transformation::typeid))
			for each (Coordinate coordinate in Enum::GetValues(Coordinate::typeid)) {
				auto newValue = transformGrid->GetValue(transformation, coordinate)->GetValue().ToString();
				_boxes->GetValue(transformation, coordinate)->Text = newValue;
			}
	}

	void TransformPanel::ChangeTransform(TransformValue^ transformChanges)
	{
		TransformChanged(transformChanges);
	}

	void TransformPanel::CreateTrasformBoxes()
	{
		_boxes = gcnew TransformGrid<TransformBox^>();
		for each (Transformation transformation in Enum::GetValues(Transformation::typeid))
			for each (Coordinate coordinate in Enum::GetValues(Coordinate::typeid))
			{
				TransformBox^ transformBox = gcnew TransformBox(transformation, coordinate, this);
				_boxes->SetValue(transformation, coordinate, transformBox);
			}
	}

	void TransformPanel::DeployTrasformPanel()
	{
		_deployerTransformPanel = gcnew DeployerTrasformPanel(this, _boxes);
		_deployerTransformPanel->DeployPanel();
	}

	void TransformPanel::OnSizeChanged(EventArgs^ ea)
	{
		ATransformPanel::OnSizeChanged(ea);
		this->Controls->Clear();
		_deployerTransformPanel->DeployPanel();
	}

	void TransformPanel::DeployerTrasformPanel::DeployPanel()
	{
		height = 0;

		for each (Transformation transformation in Enum::GetValues(Transformation::typeid))
			DeployRowTransformation(transformation, _boxes[transformation]);
	}

	void TransformPanel::DeployerTrasformPanel::DeployRowTransformation(Transformation transformation, TransformGrid<TransformBox^>::RowGrid^ rowTransformation)
	{
		height += DeployTitle(transformation)->Height;
		height += DeployBoxes(rowTransformation)->Height;
		height += GapBehindTransformBoxes;
	}

	Control^ TransformPanel::DeployerTrasformPanel::DeployTitle(Transformation transformation)
	{
		Label^ titleLabel = GetTitleTransformation(transformation);
		titleLabel->Location = System::Drawing::Point(0, height);
		_transformPanel->Controls->Add(titleLabel);
		return titleLabel;
	}

	Control^ TransformPanel::DeployerTrasformPanel::DeployBoxes(TransformGrid<TransformBox^>::RowGrid^ rowTransform)
	{
		int width = 0;
		int widthBox = _transformPanel->Width / CountTransformBoxesRow;
		Label^ coordTitle;
		for each (Coordinate coordinate in Enum::GetValues(Coordinate::typeid)) {
			auto box = rowTransform[coordinate];
			coordTitle = GetTitleCoordinate(coordinate);
			coordTitle->Location = System::Drawing::Point(width, height);
			_transformPanel->Controls->Add(coordTitle);

			width += coordTitle->Width;

			box->Location = System::Drawing::Point(width, height);
			box->Size = Drawing::Size(widthBox - coordTitle->Width, coordTitle->Height);
			_transformPanel->Controls->Add(box);
			width += box->Width;
		}
		return coordTitle;
	}

	Label^ TransformPanel::DeployerTrasformPanel::GetTitleTransformation(Transformation transformation)
	{
		Label^ title = gcnew Label();
		title->Font = FontTitleManipulation;
		title->Text = Enum::GetName(Transformation::typeid, transformation);
		title->AutoSize = true;
		return title;
	}

	Label^ TransformPanel::DeployerTrasformPanel::GetTitleCoordinate(Coordinate coordinate)
	{
		Label^ title = gcnew Label();
		title->Font = FontTitleCoordinate;
		title->Text = Enum::GetName(Coordinate::typeid, coordinate) + ":";
		title->AutoSize = true;
		return title;
	}



	void TransformPanel::TransformBox::OnEnter(EventArgs^ ea)
	{
		_beforeInput = Text;
	}

	void TransformPanel::TransformBox::OnKeyDown(KeyEventArgs^ kea)
	{
		switch (kea->KeyCode)
		{
		case Keys::Enter:
			TryChangeValue();
			break;
		case Keys::Up:
		case Keys::W:
			ChangeValueDelta(1);
			break;
		case Keys::Down:
		case Keys::S:
			ChangeValueDelta(-1);
			break;
		}
	}

	void TransformPanel::TransformBox::OnLeave(EventArgs^ ea)
	{
		TryChangeValue();
	}

	void TransformPanel::TransformBox::TryChangeValue()
	{
		String^ currentInput = Text;

		float currentValue;
		if (float::TryParse(currentInput, Globalization::NumberStyles::Float, Globalization::CultureInfo::InvariantCulture, currentValue))
			_parentPanel->ChangeTransform(gcnew TransformValueAbsolute(_transformation, _coordinate, currentValue));
		else
			Text = _beforeInput;
	}
	void TransformPanel::TransformBox::ChangeValueDelta(int delta)
	{
		delta = delta < 0 ? -1 : 1;
		_parentPanel->ChangeTransform(gcnew TransformValueDelta(_transformation, _coordinate, delta));
	}
}