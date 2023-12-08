#include "pch.h"

#include "Vector3.h"
#include "BuilderMatrix.h"
#include "Matrix.h"

namespace MathMatrix {
	namespace Vectors {

		Vector3::Vector3(double x, double y, double z) : _x(x), _y(y), _z(z) {}
		Vector3::Vector3(double x, double y) : _x(x), _y(y), _z(0) {}

		double Vector3::default::get(Coordinate coordinate) {
			switch (coordinate) {
			case Coordinate::X:
				return _x;
			case Coordinate::Y:
				return _y;
			case Coordinate::Z:
				return _z;
			}

			throw gcnew System::ArgumentException();
		}

		Vector3 Vector3::operator +(Vector3 other) {
			return Vector3(_x + other._x, _y + other._y, _z + other._z);
		}

		Vector3 Vector3::operator-(Vector3 other)
		{
			return Vector3(_x - other._x, _y - other._y, _z - other._z);
		}

		Matrix Vector3::GorizontalMatrix(Vector3 vector) {
			BuilderMatrix^ result = gcnew BuilderMatrix(1, 4);

			result[0, 0] = vector._x;
			result[0, 1] = vector._y;
			result[0, 2] = vector._z;
			result[0, 3] = 1;

			return result->Build();
		}

		Matrix Vector3::operator *(Matrix matrix) {
			return GorizontalMatrix(*this) * matrix;
		}

		Vector3 Vector3::operator*(double scalar)
		{
			return Vector3(_x * scalar, _y * scalar, _z * scalar);
		}

		Vector3 Vector3::operator/(double scalar)
		{
			return this->operator*(1 / scalar);
		}

		bool Vector3::operator ==(Vector3 other) {
			return this->Equals(other);
		}

		Vector3 Vector3::operator-() {
			return Vector3(-_x, -_y, -_z);
		}

		System::String^ Vector3::ToString() {
			return System::String::Format("{{0}, {1}, {2}}", _x, _y, _z);
		}
	}
}