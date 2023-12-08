#include "GeneratorTransformMatrix.h"

Matrix^ GeneratorMatrix::GetPosition(Vector3 shifts)
{
	BaseMatrix^ source = gcnew BaseMatrix(4, 4);
	source->FillMainDiagonal();

	source[0, 3] = shifts.X;
	source[1, 3] = shifts.Y;
	source[2, 3] = shifts.Z;

	return  gcnew Matrix(source);
}

double radinas(double angle) {
	return angle * 3.1415 / 180;
}

Matrix^ GeneratorMatrix::GetRotation(Vector3 angles)
{
	double cx = cos(radinas(angles.X));
	double sx = sin(radinas(angles.X));
	double cy = cos(radinas(angles.Y));
	double sy = sin(radinas(angles.Y));
	double cz = cos(radinas(angles.Z));
	double sz = sin(radinas(angles.Z));

	BaseMatrix^ source = gcnew BaseMatrix(4, 4);
	source->FillMainDiagonal();

	source[0, 0] = cy * cz;
	source[0, 1] = -cy * sz;
	source[0, 2] = sy;

	source[1, 0] = cx * sz + cz * sx * sy;
	source[1, 1] = cx * cz - sx * sy * sz;
	source[1, 2] = -cy * sx;

	source[2, 0] = -cx * cz * sy + sx * sz;
	source[2, 1] = cz * sx + cx * sy * sz;
	source[2, 2] = cx * cy;

	return gcnew Matrix(source);
}

Matrix^ GeneratorMatrix::GetScale(Vector3 ratios)
{
	BaseMatrix^ source = gcnew BaseMatrix(4, 4);
	source->FillMainDiagonal();

	source[0, 0] = ratios.X;
	source[1, 1] = ratios.Y;
	source[2, 2] = ratios.Z;
	
	return gcnew Matrix(source);
}
