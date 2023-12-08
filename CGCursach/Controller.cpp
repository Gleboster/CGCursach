#include "Controller.h"

namespace MVC {

	Controller::Controller()
	{
	}

	void Controller::InputFromPanel(String^ value)
	{
		_model->TrySetTransform(curManipulation, curCoordinate, value);
	}
	void Controller::InputfromKeyBoard(int offset)
	{
		_model->ChangeTransform(curManipulation, curCoordinate, offset);
	}
	void Controller::ChangeSourceBox(Manipulation manipulation, Coordinate coordinate)
	{
		curManipulation = manipulation;
		curCoordinate = coordinate;
	}

	void Controller::ChangeModel(Controller^ controller, Model^ model)
	{
		controller->_model = model;
	}
}