#pragma once
#include "Coordinate.h"
#include "Transformation.h"

namespace MVCLibrary {

	public ref class TransformValue {
		Transformation _transformation;
		Coordinate _coordinate;
	public:
		TransformValue(const Transformation transformation, const Coordinate coordinate)
			: _transformation(transformation), _coordinate(coordinate) {	}
	};


	public ref class TransformValueDelta : public TransformValue {
		float _delta;
	public:
		TransformValueDelta(const Transformation transformation, const Coordinate coordinate, float delta)
			: TransformValue(transformation, coordinate), _delta(delta) {};
	};


	public ref class TransformValueAbsolute : public TransformValue {
		float value;
	public:
		TransformValueAbsolute(const Transformation transformation, const Coordinate coordinate, float _value)
			: TransformValue(transformation, coordinate), value(_value) {};

		float GetValue() {
			return value;
		}
	};
}