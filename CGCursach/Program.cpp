#include "MyForm.h"
#include "Geometric.h"
#include "Transform.h"
#include "ModelOnce.h"
#include "ViewEdges.h"
#include "ViewSurfaces.h"

using namespace System;
using namespace System::Windows::Forms;

double len(Vector3 a, Vector3 b) {
	return std::sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y) + (a.Z - b.Z) * (a.Z - b.Z));
}

ReadOnlyGeometric^ CreateCub();
ReadOnlyGeometric^ CreatePyramid();
ReadOnlyGeometric^ CreateTriangle() {
	List<Vector3>^ points = gcnew List<Vector3>();

	points->Add(Vector3(1, 1, 1));
	points->Add(Vector3(1, 1, -1));
	points->Add(Vector3(-1, -1, 1));
	points->Add(Vector3(-1, -1, -1));

	List<Segment>^ segments = gcnew List<Segment>();
	for (int i = 0; i < 4; i++)
		segments->Add(Segment(points[i], points[(i + 1) % 4]));

	return gcnew ReadOnlyGeometric(points->ToArray(), segments->ToArray());
}

//TODO: ебни сюда Translate Anchor 
int main() {
	Model^ model = gcnew Model(gcnew SceneOnce(gcnew SceneObject(CreatePyramid())));
	MVC::View^ view = gcnew MVC::ViewSurfaces();
	Controller^ controller = gcnew Controller();

	ModelViewController^ mvc = gcnew ModelViewController(model, view, controller);
	CGCursach::MyForm^ form = gcnew CGCursach::MyForm();

	controller->inputPanel = form->panel->inputPanel;
	view->PanelTransform = form->panel->viewPanel;

	view->OutputDisplay = form->outputBox;

	model->Show();

	Application::Run(form);
}

ReadOnlyGeometric^ CreateCub() {
	List<Vector3>^ points = gcnew List<Vector3>();

	for (int x = -1; x <= 1; x += 2)
		for (int y = -1; y <= 1; y += 2)
			for (int z = -1; z <= 1; z += 2)
				points->Add(Vector3(x, y, z));

	List<Segment>^ segments = gcnew List<Segment>();
	for each (auto u in points)
		for each (auto v in points) {
			if (v == u) continue;
			if ((u.X == v.X && u.Y == v.Y) ||
				(u.X == v.X && u.Z == v.Z) ||
				(u.Z == v.Z && u.Y == v.Y))
			{
				if (segments->Contains(Segment(v, u))) continue;
				segments->Add(Segment(u, v));
			}
		}

	return gcnew ReadOnlyGeometric(points->ToArray(), segments->ToArray());
}


ReadOnlyGeometric^ CreatePyramid() {
	List<Vector3>^ points = gcnew List<Vector3>();

	for (int x = -1; x <= 1; x += 2)
		for (int y = -1; y <= 1; y += 2)
			points->Add(Vector3(x, y , 0));

	List<Segment>^ segments = gcnew List<Segment>();
	for each (auto u in points)
		for each (auto v in points) {
			if (v == u) continue;
			if ((u.X == v.X && u.Y == v.Y) ||
				(u.X == v.X && u.Z == v.Z) ||
				(u.Z == v.Z && u.Y == v.Y))
			{
				if (segments->Contains(Segment(v, u))) continue;
				segments->Add(Segment(u, v));
			}
		}

	auto upPoint = Vector3(0, 0, 1);

	for each (auto u in points) {
		segments->Add(Segment(u, upPoint));
	}

	points->Add(upPoint);

	return gcnew ReadOnlyGeometric(points->ToArray(), segments->ToArray());
}