#include "Model.h"

namespace MVC {
	void Model::TrySetTransform(Manipulation manipulation, Coordinate coordinate, String^ value)
	{
		double dvalue;
		bool succes = Double::TryParse(value, Globalization::NumberStyles::Float, Globalization::CultureInfo::InvariantCulture, dvalue); 
		if (succes)
			_scene->SetTransformObject(manipulation, coordinate, dvalue);

		Show(succes);
	}

	void Model::ChangeTransform(Manipulation manipulation, Coordinate coordinate, double delta)
	{
		_scene->ChangeTransformObject(manipulation, coordinate, delta * offsets[manipulation]);

		Show();
	}

	void Model::Show()
	{
		Show(true);
	}

	void Model::Show(bool succes)
	{
		if (succes)
			_view->ShowScene(_scene);

		_view->ShowTransform(_scene->CurrentTransform);
	}
	void Model::ChangeView(Model^ model, View^ view)
	{
		model->_view = view;
	}
}