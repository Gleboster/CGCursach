#pragma once
#include "TransformValue.h"

using namespace System::Collections::Generic;

namespace MVCLibrary {

	generic<typename T>
	public ref class TransformGrid {
	public:
		TransformGrid() {
			_rowsGrid = gcnew Dictionary<Transformation, RowGrid^>();

			for each (Transformation transformation in Enum::GetValues(Transformation::typeid))
				_rowsGrid[transformation] = gcnew RowGrid();
		}

	public:
		ref class RowGrid {
		private:
			Dictionary<Coordinate, T>^ _values;
		public:
			RowGrid() {
				_values = gcnew Dictionary<Coordinate, T>();
			}

			T operator[](Coordinate coordinate) {
				return _values[coordinate];
			}

			void SetValue(Coordinate coordinate, T value) {
				_values[coordinate] = value;
			}
		};

	private:
		Dictionary<Transformation, RowGrid^>^ _rowsGrid;

	public:
		RowGrid^ operator[](Transformation transformation) {
			return _rowsGrid[transformation];
		}

		T GetValue(Transformation transformation, Coordinate coordinate) {
			return _rowsGrid[transformation]->operator[](coordinate);
		}

		void SetValue(Transformation transformation, Coordinate coordinate, T value) {
			_rowsGrid[transformation]->SetValue(coordinate, value);
		}

		Dictionary<Transformation, RowGrid^>::ValueCollection^ GetRows() {
			return _rowsGrid->Values;
		}
	};
}