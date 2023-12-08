#pragma once
#include "Segment.h"
#include "Panel.h"
#include "OutputBox.h"
#include "Scene.h"

namespace MVC {
	public ref class View abstract{
	protected:
		ViewPanel^ _panelTransform;
		OutputBox^ _outputDisplay;
	public:
		property ViewPanel^ PanelTransform { void set(ViewPanel^ pt) { _panelTransform = pt; } };
		property OutputBox^ OutputDisplay { void set(OutputBox^ od) { _outputDisplay = od; } };

		virtual void ShowScene(Scene^ scene) abstract;
		virtual void ShowTransform(Dictionary<Manipulation, Vector3>^ rations) {
			_panelTransform->FillTransform(rations);
		};
		//virtual void ShowSurfaces(array<Surface>^ surfaces) abstract;
	};
}