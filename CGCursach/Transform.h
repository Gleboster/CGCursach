#pragma once
#include <cmath>
#include "Vector3.h"
#include "Matrix.h"
#include "Manipulations.h"
#include "GeneratorTransformMatrix.h"

using namespace System::Collections::Generic;

using TransformPanel = Dictionary<Manipulation, Vector3>;

public ref class Transform {

	ref class PanelValues;

	GeneratorMatrix^ _generator;

	Matrix^ _position;
	Matrix^ _rotation;
	Matrix^ _scale;

	Matrix^ _transformation;

	PanelValues^ _ratios; //Замени второй дик на вектор3
public:
	Transform();

	void SetRatio(Manipulation manipulation, Coordinate coordinate, double value);
	void ChangeRatioDelta(Manipulation manipulation, Coordinate coordinate, double delta);

	property Matrix^ TransformationMatrix { Matrix^ get() { return _transformation; }}
	property TransformPanel^ Ratios { TransformPanel^ get() { return _ratios->GetInput(); } };

private:
	void ChangeMatrixTransformation(Manipulation manipulation, Coordinate coordinate, double delta);
	//Matrix^ BuildNewMatrixTransformation(Manipulation manipulation, Coordinate coordinate, double delta);

	ref class PanelValues {
		Dictionary<Manipulation, Dictionary<Coordinate, double>^>^ _values;

	public:
		PanelValues();

		property double default[Manipulation, Coordinate]
		{
			double get(Manipulation manipulation, Coordinate coordinate)
			{
				return _values[manipulation]->default[coordinate];
			}

			void set(Manipulation manipulation, Coordinate coordinate, double val) {
				_values[manipulation]->default[coordinate] = val;
			}
		};

		Vector3 GetShifts(Manipulation manipulation) {
			auto p = _values[manipulation];
			return Vector3(p[Coordinate::X], p[Coordinate::Y], p[Coordinate::Z]);
		}

		Dictionary<Manipulation, Vector3>^ GetInput() {
			auto result = gcnew Dictionary<Manipulation, Vector3>();

			for each (Manipulation manip in Enum::GetValues(Manipulation::typeid))
				result[manip] = GetShifts(manip);

			return result;
		}
	};
};