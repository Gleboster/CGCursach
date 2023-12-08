#pragma once
#include "Matrix.h"

public enum class Coordinate {
	X, Y, Z
};

value struct Vector3 
{
private:
	double _x, _y, _z; //TODO мб использовать матрицу для хранения??
public:
	Vector3(double x, double y, double z) : _x(x), _y(y), _z(z) {}
	Vector3(double x, double y) : _x(x), _y(y), _z(0) {}

	property double X {
		double get() { return _x; }
	}

	property double Y {
		double get() { return _y; }
	}

	property double Z {
		double get() { return _z; }
	}

	Vector3 operator +(Vector3 other) {
		return Vector3(_x + other._x, _y + other._y, _z + other._z);
	}

	static BaseMatrix^ GorizontalMatrix(Vector3 vector) {
		BaseMatrix^ result = gcnew BaseMatrix(1, 4);

		result[0, 0] = vector._x;
		result[0, 1] = vector._y;
		result[0, 2] = vector._z;
		result[0, 3] = 1;
		return result;
	}

	Matrix^ operator *(Matrix^ matrix) {
		BaseMatrix^ thisMatrix = GorizontalMatrix(*this);

		Matrix^ result = gcnew Matrix(thisMatrix) * matrix;

		return result;
	}
	
	static Vector3 operator *(Matrix^ matrix, Vector3 vector) {
		BaseMatrix^ thisMatrix = gcnew BaseMatrix(4, 1);

		thisMatrix[0, 0] = vector._x;
		thisMatrix[1, 0] = vector._y;
		thisMatrix[2, 0] = vector._z;
		thisMatrix[3, 0] = 1;

		Matrix^ result = matrix * gcnew Matrix(thisMatrix);

		return Vector3(result[0, 0], result[1, 0], result[2, 0]);
	}

	Vector3 operator /(double scalar) {
		return Vector3(_x / scalar, _y / scalar, _z / scalar);
	}

	bool operator ==(Vector3 other) {
		return this->Equals(other);
	}

	Vector3 operator-() {
		return Vector3(-_x, -_y, -_z);
	}

	property double default[Coordinate]
	{
		double get(Coordinate coordinate)
		{
			switch (coordinate)
			{
			case Coordinate::X:
				return _x;
			case Coordinate::Y:
				return _y;
			case Coordinate::Z:
				return _z;
			}

			throw gcnew System::ArgumentException();
		}
	};

	System::String^ ToString() override {
		return System::String::Format("{0}, {1}, {2}", _x, _y, _z);
	}
};

ref class Vector3Ptr {
public:
	Vector3 value;
	Vector3Ptr(Vector3 val) : value(val) {};
};