#pragma once
#include "Model.h"
#include "InputPanel.h"
using namespace System::Windows::Forms;

namespace MVC {
	//Наблюдатель за боксами ввода подписывается на текст боксы
	ref class Controller {
		Model^ _model;

		Manipulation curManipulation;
		Coordinate curCoordinate;

	public:
		property InputPanel^ inputPanel {
			void set(InputPanel^ ip) { //Когда меняешь контроллер надо это как-то подчищать
				ip->ChoicedSourceBox += gcnew ChoiceBox(this, &Controller::ChangeSourceBox);
				ip->InputEntered += gcnew Action<String^>(this, &Controller::InputFromPanel);
				ip->OffsetBeen += gcnew Action<int>(this, &Controller::InputfromKeyBoard);
			}
		}

		Controller();
		void ChangeSourceBox(Manipulation manipulation, Coordinate coordinate);

		void InputFromPanel(String^ value);
		void InputfromKeyBoard(int offset);

		static void ChangeModel(Controller^ controller, Model^ model);
	};
}