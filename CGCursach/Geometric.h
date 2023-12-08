#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "Segment.h"
#include "Surface.h"
#include "Graph.h"
#include "GeneratorTransformMatrix.h"

using namespace System::Collections::Generic;

ref class Geometric {
protected:
	Graph^ _links;
	Matrix^ _matrixPoint;
	Vector3 _anchor;
protected:
	Matrix^ GetMatrixPoint(array<Vector3>^ vertices);
	Graph^ BuildGraph(array<Segment>^ segments);

	bool TryConvertToSurface(Circle^ circle, Surface% surfcace);
	Segment ConvertToSegment(Edge^ edge);
	Vector3 ConvertToPoint(Node^ node);

	property int CountPointInMatrix {int get() { return _matrixPoint->Columns; }};
	Vector3 GetPointFromMatrix(int index);
	void SetPointInMatrix(int index, Vector3 point, BaseMatrix^ matrix);
	int FindPointInMatrix(Vector3 point);

public:
	property Vector3 Anchor {Vector3 get() { return _anchor; }};
	property Matrix^ MatrixPoint { Matrix^ get() { return _matrixPoint; }};
	property Graph^ GeometricLinks { Graph^ get() { return _links; }};

	Vector3 GetCenter();
};


ref class ReadOnlyGeometric : public Geometric {
public:
	ReadOnlyGeometric(array<Vector3>^ points, array<Segment>^ segments);
	ReadOnlyGeometric(array<Segment>^ segments);


	~ReadOnlyGeometric();
};


ref class TransformableGeometric : public Geometric {
	GeneratorMatrix _matrixes;
public:
	TransformableGeometric(ReadOnlyGeometric^ source);

	void TransformMatrix(Matrix^ matrixMultiplier);

	array<Segment>^ GetSegments();
	array<Surface>^ GetSurfaces();

private:
	void ExpandSurfaces(array<Surface>^ surfaces);
};