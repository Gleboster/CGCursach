#include "pch.h"
#include "Matrix.h"
#include "BuilderMatrix.h"

using namespace System;

namespace MathMatrix {
	Matrix::Matrix(BuilderMatrix^ builderMatrix)
	{
		_base = builderMatrix;
	}

	int Matrix::CountColumns::get()
	{
		return _base->CountColumns;
	}

	int Matrix::CountRows::get()
	{
		return _base->CountRows;
	}

	double Matrix::default::get(int iRows, int iColumn)
	{
		return _base[iRows, iColumn];
	}

	Matrix Matrix::operator*(Matrix other)
	{
		if (CountColumns != other.CountRows)
		{
			throw gcnew Exception("Matrix dimensions do not match");
		}

		BuilderMatrix^ result = gcnew BuilderMatrix(CountRows, other.CountColumns);

		for (int i = 0; i < CountRows; i++)
		{
			for (int j = 0; j < other.CountColumns; j++)
			{
				double sum = 0;

				for (int k = 0; k < CountColumns; k++)
				{
					sum += this->default[i, k] * other[k, j];
				}

				result[i, j] = sum;
			}
		}

		return result->Build();
	}
}