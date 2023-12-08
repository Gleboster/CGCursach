#include "Geometric.h"

ReadOnlyGeometric::ReadOnlyGeometric(array<Vector3>^ points, array<Segment>^ segments)
{
	_matrixPoint = GetMatrixPoint(points);

	_links = BuildGraph(segments);
	_anchor = GetCenter();
}

ReadOnlyGeometric::ReadOnlyGeometric(array<Segment>^ segments)
{
	auto points = Segment::GetAllPointsFrom(segments);

	_matrixPoint = GetMatrixPoint(points);

	_links = BuildGraph(segments);
	_anchor = GetCenter();
}

ReadOnlyGeometric::~ReadOnlyGeometric()
{
	delete _matrixPoint;
	delete _links;
}
