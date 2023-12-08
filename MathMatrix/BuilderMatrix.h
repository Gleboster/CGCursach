#pragma once


namespace MathMatrix {
value struct Matrix;

	ref class BuilderMatrix
	{
	private:
		array<double, 2>^ _values;
		int _rows;
		int _cols;

	public:
		BuilderMatrix(int rows, int cols);
		BuilderMatrix(Matrix baseMatrix);

		property int CountRows
		{
			int get() { return _rows; }
		}

		property int CountColumns
		{
			int get() { return _cols; }
		}

		property double default[int, int]
			{
				double get(int iRows, int iColumn);
				void set(int iRows, int iColumn, double value);
			};

		void FillMainDiagonal(int value);
		void FillMainDiagonal();
		Matrix Build();
	};
}
