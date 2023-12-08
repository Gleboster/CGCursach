#include "Geometric.h"

TransformableGeometric::TransformableGeometric(ReadOnlyGeometric^ source)
{
	_matrixPoint = source->MatrixPoint;
	_links = source->GeometricLinks;
	_anchor = source->Anchor;

}

void TransformableGeometric::TransformMatrix(Matrix^ matrixMultiplier)
{
	Matrix^ shistsToZero = _matrixes.GetPosition(-_anchor);
	_matrixPoint = shistsToZero * _matrixPoint;
	_anchor = shistsToZero * _anchor;

	_matrixPoint = matrixMultiplier * _matrixPoint;
	_anchor = matrixMultiplier * _anchor;

	Matrix^ shistsFromZero = _matrixes.GetPosition(_anchor);
	_matrixPoint = shistsFromZero * _matrixPoint;
	_anchor = shistsFromZero * _anchor;
}

array<Segment>^ TransformableGeometric::GetSegments()
{
	array<Segment>^ result = gcnew array<Segment>(_links->Edges->Length);
	int i = 0;
	auto r = _matrixPoint;
	for each (Edge ^ edge in _links->Edges)
	{
		Segment newsegment = Segment(GetPointFromMatrix(edge->From), GetPointFromMatrix(edge->To));
		result[i++] = newsegment;
	}

	return result;
}

array<Surface>^ TransformableGeometric::GetSurfaces()
{
	array<Circle^>^ circles = _links->Circles;
	array<Surface>^ surfaces = gcnew array<Surface>(circles->Length);

	for (int i = 0; i < circles->Length; i++)
		TryConvertToSurface(circles[i], surfaces[i]); //ѕравильно их размещать относительно центра

	ExpandSurfaces(surfaces);

	return surfaces;
}

/// <summary>
/// ѕоворачивает нормали всех плоскостей от центра наружу.... 
/// </summary>
/// <param name="surfaces"></param>
void TransformableGeometric::ExpandSurfaces(array<Surface>^ surfaces)
{
	Matrix^ checkedMatrix = GetCenter() * Surface::GetMatrix(surfaces);

	for (int i = 0; i < checkedMatrix->Columns; i++)
		if (checkedMatrix[0, i] > 0)
			surfaces[i].Expand();
	
}
