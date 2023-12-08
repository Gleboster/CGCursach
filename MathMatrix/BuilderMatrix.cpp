#include "pch.h"
#include "BuilderMatrix.h"
#include "Matrix.h"

using namespace System;

namespace MathMatrix {
	BuilderMatrix::BuilderMatrix(int rows, int cols)
	{
		_rows = rows;
		_cols = cols;
		_values = gcnew array<double, 2>(rows, cols);
	}

	BuilderMatrix::BuilderMatrix(Matrix baseMatrix) : BuilderMatrix(baseMatrix.CountRows, baseMatrix.CountColumns)
	{
		for (int y = 0; y < baseMatrix.CountRows; y++)
			for (int x = 0; x < baseMatrix.CountColumns; x++)
				_values[x, y] = baseMatrix[x, y];
	}

	double BuilderMatrix::default::get(int iRows, int iColumn)
	{
		return _values[iRows, iColumn];
	}

	void BuilderMatrix::default::set(int iRows, int iColumn, double value)
	{
		_values[iRows, iColumn] = value;
	}


	void BuilderMatrix::FillMainDiagonal(int value)
	{
		if (_cols != _rows)
			throw gcnew Exception("Matrix is not square");

		for (int i = 0; i < _cols; i++)
			_values[i, i] = value;
	}

	void BuilderMatrix::FillMainDiagonal()
	{
		FillMainDiagonal(1);
	}

	Matrix BuilderMatrix::Build()
	{
		return Matrix(this);
	}
}
