#include "Geometric.h"

Matrix^ Geometric::GetMatrixPoint(array<Vector3>^ points)
{
	BaseMatrix^ matrixPoint = gcnew BaseMatrix(4, points->Length);
	for (int i = 0; i < points->Length; i++)
		SetPointInMatrix(i, points[i], matrixPoint);

	return Matrix(matrixPoint);
}

Vector3 Geometric::GetPointFromMatrix(int index)
{
	return Vector3(_matrixPoint[0, index], _matrixPoint[1, index], _matrixPoint[2, index]);
}

void Geometric::SetPointInMatrix(int index, Vector3 point, BaseMatrix^ matrix)
{
	matrix[0, index] = point.X;
	matrix[1, index] = point.Y;
	matrix[2, index] = point.Z;
	matrix[3, index] = 1;
}

int Geometric::FindPointInMatrix(Vector3 point)
{
	for (int i = 0; i < CountPointInMatrix; i++)
		if (GetPointFromMatrix(i) == point)
			return i;

	throw gcnew System::NotImplementedException();
}

Vector3 Geometric::GetCenter()
{
	Vector3 sumAll;
	for (int i = 0; i < CountPointInMatrix; i++)
		sumAll += GetPointFromMatrix(i);

	return sumAll / CountPointInMatrix;
}

Graph^ Geometric::BuildGraph(array<Segment>^ segments)
{
	Graph^ result = gcnew Graph(CountPointInMatrix);
	for each (Segment s in segments)
		result->Connect(FindPointInMatrix(s.Start), FindPointInMatrix(s.End));

	auto checkedCircles = gcnew List<Circle^>();
	for each (Circle^ circle in result->Circles)
	{
		Surface s;
		if (TryConvertToSurface(circle, s))
			checkedCircles->Add(circle);
	}

	result->Circles = checkedCircles->ToArray();

	return result;
}

bool Geometric::TryConvertToSurface(Circle^ circle, Surface% surfcace)
{
	auto edges = circle->Edges;
	array<Segment>^ segments = gcnew array<Segment>(circle->Len);
	for (int i = 0; i < segments->Length; i++)
		segments[i] = ConvertToSegment(edges[i]);

	auto nodes = circle->Nodes;
	array<Vector3>^ points = gcnew array<Vector3>(circle->Len);
	for (int i = 0; i < points->Length; i++)
		points[i] = ConvertToPoint(nodes[i]);

	try {
		surfcace = Surface(points, segments);
	}
	catch (System::ArgumentException^ ae) {
		return false;
	}

	return true;
}

Segment Geometric::ConvertToSegment(Edge^ edge)
{
	return Segment(ConvertToPoint(edge->From), ConvertToPoint(edge->To));
}

Vector3 Geometric::ConvertToPoint(Node^ node)
{
	return GetPointFromMatrix(node);
}



