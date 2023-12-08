#include "Scene.h"

void Scene::SetTransformObject(Manipulation manipulation, Coordinate coordinate, double value)
{
    _currentSceneObject->transform->SetRatio(manipulation, coordinate, value);
}

void Scene::ChangeTransformObject(Manipulation manipulation, Coordinate coordinate, double delta)
{
    _currentSceneObject->transform->ChangeRatioDelta(manipulation, coordinate, delta);
}
