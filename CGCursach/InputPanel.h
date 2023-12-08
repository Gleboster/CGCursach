#pragma once
#include "Manipulations.h"
#include "Vector3.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

delegate void ChoiceBox(Manipulation, Coordinate);

ref class InputPanel : UserControl {
public:
	event ChoiceBox^ ChoicedSourceBox;
	event Action<String^>^ InputEntered;
	event Action<int>^ OffsetBeen;

	InputPanel();
private:
	ref class CommandChangeSourceBox {
		Manipulation _manipulation;
		Coordinate _coordinate;
		InputPanel^ _inputPanel;
	public:
		CommandChangeSourceBox(Manipulation manipulation, Coordinate coordinate, InputPanel^ inputPanel)
		{
			_manipulation = manipulation;
			_coordinate = coordinate;
			_inputPanel = inputPanel;
		}

		void Execute() {
			_inputPanel->ChoicedSourceBox(_manipulation, _coordinate);
		}
	};

	ref class CommandInput {
		InputPanel^ _inputPanel;
	public:
		CommandInput(InputPanel^ inputPanel)
		{
			_inputPanel = inputPanel;
		}

		void Execute(String^ input) {
			_inputPanel->InputEntered(input);
		}
	};

	ref class CommandOffset {
		InputPanel^ _inputPanel;
	public:
		CommandOffset(InputPanel^ inputPanel)
		{
			_inputPanel = inputPanel;
		}

		void Execute(int offset) {
			_inputPanel->OffsetBeen(offset);
		}
	};

public:
	ref class InputBox : TextBox {
		CommandChangeSourceBox^ _commandChange;
		CommandInput^ _commandInput;
		CommandOffset^ _commandOffset;
	public:
		InputBox(CommandChangeSourceBox^ commandChange, CommandInput^ commandInput, CommandOffset^ commandOffset)
		{
			_commandChange = commandChange;
			_commandInput = commandInput;
			_commandOffset = commandOffset;
		}

	protected:
		bool isActive = false;

		void OnEnter(EventArgs^ ea) override {
			if (isActive == false) {
				TextBox::OnEnter(ea);
				isActive = true;
				_commandChange->Execute();
			}
		}

		void OnKeyDown(KeyEventArgs^ kea) override {
			Keys keyCode = kea->KeyCode;

			if (keyCode == Keys::Up)
				_commandOffset->Execute(1);
			else if (keyCode == Keys::Down)
				_commandOffset->Execute(-1);
			else if (keyCode == Keys::Enter)
				_commandInput->Execute(this->Text);
		}

		void OnLeave(EventArgs^ ea) override {
			if (isActive == true) {
				TextBox::OnLeave(ea);
				isActive = false;
				_commandInput->Execute(this->Text);
			}
		}
	};
	using ManipulationBoxes = Dictionary<Coordinate, InputPanel::InputBox^>;
	using TransformBoxes = Dictionary<Manipulation, ManipulationBoxes^>;

private: TransformBoxes^ _boxes;
public:
	property TransformBoxes^ Boxes {
		TransformBoxes^ get() {
			if (_boxes == nullptr)
				_boxes = CreateBoxes();
			return _boxes;
		}
	}

private:
	TransformBoxes^ CreateBoxes() {
		TransformBoxes^ result = gcnew TransformBoxes();

		for each (Manipulation manip in Enum::GetValues(Manipulation::typeid))
		{
			result[manip] = gcnew ManipulationBoxes();
			for each (Coordinate coord in Enum::GetValues(Coordinate::typeid))
			{
				result[manip]->default[coord] = gcnew InputBox(
					gcnew CommandChangeSourceBox(manip, coord, this),
					gcnew CommandInput(this),
					gcnew CommandOffset(this));
			}
		}
		return result;
	}
};

using ManipulationBoxes = Dictionary<Coordinate, InputPanel::InputBox^>;
using TransformBoxes = Dictionary<Manipulation, ManipulationBoxes^>;