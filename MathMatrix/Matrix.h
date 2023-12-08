#pragma once


namespace MathMatrix {
	ref class BuilderMatrix;

	public value struct Matrix {

	private:
		BuilderMatrix^ _base;

	public:

		Matrix(BuilderMatrix^ builderMatrix);

		property int CountRows
		{
			int get();
		}

		property int CountColumns
		{
			int get();
		}

		property double default[int, int]
			{
				double get(int iRows, int iColumn);
			}

		Matrix operator*(Matrix other);
	};
}