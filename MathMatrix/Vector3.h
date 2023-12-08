#include "Coordinate.h"

namespace MathMatrix {
	value struct Matrix;
	namespace Vectors {

		public value struct Vector3 {
		private:
			double _x, _y, _z;

		public:
			Vector3(double x, double y, double z);
			Vector3(double x, double y);

			property double X {
				double get() { return _x; };
			};
			property double Y {
				double get() { return _y; };
			};
			property double Z {
				double get() { return _z; };
			};

			property double default[Coordinate] {
				double get(Coordinate coordinate);
				};

			Vector3 operator-();

			Vector3 operator +(Vector3 other);
			Vector3 operator -(Vector3 other);

			Matrix operator *(Matrix matrix);
			Vector3 operator *(double scalar);

			Vector3 operator /(double scalar);
			bool operator ==(Vector3 other);

			System::String^ ToString() override;

			static Matrix GorizontalMatrix(Vector3 vector);
		};
	}
}