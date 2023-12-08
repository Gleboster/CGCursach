#pragma once
using namespace System;

public ref class BaseMatrix
{
private:
	array<double, 2>^ _values;
	int _rows;
	int _cols;

public:
	BaseMatrix(int rows, int cols)
	{
		_rows = rows;
		_cols = cols;
		_values = gcnew array<double, 2>(rows, cols);
	}

	property int Rows
	{
		int get() { return _rows; }
	}

	property int Cols
	{
		int get() { return _cols; }
	}

	property double default[int, int]
	{
		double get(int index1, int index2)
		{
			return _values[index1, index2];
		}
		void set(int index1, int index2, double value)
		{
			_values[index1, index2] = value;
		}
	}

	value struct ConstMatrix
	{
	private:
		BaseMatrix^ _base;

	public:

		ConstMatrix(BaseMatrix^ mt) {
			_base = mt;
		};

		property int Rows
		{
			int get() { return _base->_rows; }
		}

		property int Columns
		{
			int get() { return _base->_cols; }
		}

		property double default[int, int]
		{
			double get(int index1, int index2)
			{
				return _base->_values[index1, index2];
			}
		}

		ConstMatrix^ operator*(ConstMatrix^ other)
		{
			if (Columns != other->Rows)
			{
				throw gcnew Exception("Matrix dimensions do not match");
			}

			BaseMatrix^ result = gcnew BaseMatrix(Rows, other->Columns);

			for (int i = 0; i < Rows; i++)
			{
				for (int j = 0; j < other->Columns; j++)
				{
					double sum = 0;

					for (int k = 0; k < Columns; k++)
					{
						sum += this->default[i, k] * other[k, j];
					}

					result->_values[i, j] = sum;
				}
			}

			return gcnew ConstMatrix(result);
		}
	};

	void FillMainDiagonal() {
		if (_cols != _rows)
			throw gcnew Exception("Matrix is not square");

		for (int i = 0; i < _cols; i++)
			_values[i, i] = 1;
	}
};

using Matrix = BaseMatrix::ConstMatrix;