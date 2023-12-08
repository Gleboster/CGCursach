#pragma once
#include "Geometric.h"
#include "Transform.h"

ref class SceneObject {
	ReadOnlyGeometric^ _geometry;
	Transform^ _transform;

public:
	SceneObject(ReadOnlyGeometric^ geometry);
	SceneObject(ReadOnlyGeometric^ geometry, Vector3 anchor);

	property Transform^ transform {Transform^ get() { return _transform; }	}

	TransformableGeometric^ GetGeometryScene();
};