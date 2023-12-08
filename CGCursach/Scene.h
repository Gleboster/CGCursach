#pragma once
#include "SceneObject.h"
#include "Edge.h"

using namespace System::Collections::Generic;

ref class Scene abstract {
protected:
	SceneObject^ _currentSceneObject;

public:
	void SetTransformObject(Manipulation manipulation, Coordinate coordinate, double value);
	void ChangeTransformObject(Manipulation manipulation, Coordinate coordinate, double delta);

	property Vector3 CameraPosition {
		Vector3 get() { return Vector3(0, 0, 1); }
	}

	property array<Segment>^ AllSegments {
		virtual array<Segment>^ get() abstract;
	};

	property array<Surface>^ AllSurfaces {
		virtual array<Surface>^ get() abstract;
	};

	property TransformPanel^ CurrentTransform {
		TransformPanel^ get() { return _currentSceneObject->transform->Ratios; }
	}
};

ref class SceneOnce : public Scene {
public:
	SceneOnce(SceneObject^ obj)
	{
		_currentSceneObject = obj;
	}

	property array<Segment>^ AllSegments {
		array<Segment>^ get() override { return _currentSceneObject->GetGeometryScene()->GetSegments(); }
	};

	property array<Surface>^ AllSurfaces {
		array<Surface>^ get() override { return _currentSceneObject->GetGeometryScene()->GetSurfaces(); }
	}
};