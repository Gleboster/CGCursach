#pragma once
#include "SceneObject.h"
#include "Geometric.h"
#include "View.h"
#include "Scene.h"

namespace MVC {
	ref class Model {
	protected:
		Scene^ _scene;

		View^ _view;
	private:
		static Dictionary<Manipulation, double>^ offsets;

		static Model() {
			offsets = gcnew Dictionary<Manipulation, double>();
			offsets->Add(Manipulation::Position, 0.2);
			offsets->Add(Manipulation::Rotation, 10);
			offsets->Add(Manipulation::Scale, 0.2);
		}

	public:
		Model(Scene^ scene)
		{
			_scene = scene;
		}

		void TrySetTransform(Manipulation manipulation, Coordinate coordinate, String^ value);
		void ChangeTransform(Manipulation manipulation, Coordinate coordinate, double delta);

		void Show();
	protected:
		void Show(bool succes);

	public:
		static void ChangeView(Model^ model, View^ view);
	};
}