#pragma once
#include "Vector3.h"

public value struct Surface {
	array<Vector3>^ _points;
	array<Segment>^ _segments;
	double a, b, c, d;
public:
	Surface(array<Vector3>^ points, array<Segment>^ segments)
	{
		_points = points;
		_segments = segments;

		CalculateRatios(_points, _segments);
	}

	Surface(array<Segment>^ segments) {
		_points = Segment::GetAllPointsFrom(segments);
		_segments = segments;

		CalculateRatios(_points, _segments);
	}

	property double A {
		double get() { return a; }
	}
	property double B {
		double get() { return b; }
	}
	property double C {
		double get() { return c; }
	}
	property double D {
		double get() { return d; }
	}

	property array<Segment>^ AllSegments {
		array<Segment>^ get() { return _segments; }
	}

	void Expand() {
		a *= -1;
		b *= -1;
		c *= -1;
		d *= -1;
	}

	static Matrix^ GetMatrix(array<Surface>^ surfaces) {
		BaseMatrix^ matrixSurfaces = gcnew BaseMatrix(4, surfaces->Length);
		int i = 0;
		for each (Surface s in surfaces)
		{
			matrixSurfaces[0, i] = s.A;
			matrixSurfaces[1, i] = s.B;
			matrixSurfaces[2, i] = s.C;
			matrixSurfaces[3, i] = s.D;

			i++;
		}

		return gcnew Matrix(matrixSurfaces);
	}

private:
	void CalculateRatios(array<Vector3>^ points, array<Segment>^ segments)
	{
		if (points->Length < 3 || points->Length != segments->Length)
			throw gcnew System::ArgumentException();

		a = b = c = 0;
		for (int i = 0; i < 3; i++) {
			Vector3 p1 = points[i];
			Vector3 p2 = points[(i + 1) % 3];

			a += (p1.Y - p2.Y) * (p1.Z + p2.Z);
			b += (p1.Z - p2.Z) * (p1.X + p2.X);
			c += (p1.X - p2.X) * (p1.Y + p2.Y);
		}

		d = -(a * points[2].X + b * points[2].Y + c * points[2].Z);
		double divisor = d == 0 ? 1 : d;
		a /= divisor;
		b /= divisor;
		c /= divisor;
		d /= divisor;

		for (int i = 3; i < points->Length; i++)
			if (!isIncludingPoint(points[i]))
				throw gcnew System::ArgumentException();
	}

	bool isIncludingPoint(Vector3 point) {
		double value = a * point.X + b * point.Y + c * point.Z + d;
		return Math::Abs(value) < 0.001;
	}
};
