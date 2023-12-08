#pragma once
#include "Model.h"
#include "Controller.h"
#include "View.h"

namespace MVC {

	public ref class ModelViewController {
	public:
		initonly Model^ model;
		initonly View^ view;
		initonly Controller^ controller;
		
		ModelViewController(Model^ model, View^ view, Controller^ controller) //Я тут был
		{
			this->model = model;
			this->view = view;
			this->controller = controller;

			Model::ChangeView(model, view); //Когда меняешь вью у модели надо менять все связи с вьюхой
			Controller::ChangeModel(controller, model); //Когда меняешь контроллер тоже надо менять все связи кнтроллера и интпут бокса
		}
	};
}