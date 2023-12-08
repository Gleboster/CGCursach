#include "SceneObject.h"

SceneObject::SceneObject(ReadOnlyGeometric^ geometry)
{
	_geometry = geometry;
	_transform = gcnew Transform();
}

SceneObject::SceneObject(ReadOnlyGeometric^ geometry, Vector3 anchor)
{
	_geometry = geometry;
	_transform = gcnew Transform();
}

TransformableGeometric^ SceneObject::GetGeometryScene()
{
	TransformableGeometric^ result = gcnew TransformableGeometric(_geometry);



	result->TransformMatrix(_transform->TransformationMatrix);

	return result;
}
