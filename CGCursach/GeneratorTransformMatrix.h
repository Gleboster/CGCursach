#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include <cmath>

using namespace std;

ref class GeneratorMatrix {
public:
	GeneratorMatrix() {};

	Matrix^ GetPosition(Vector3 shifts);

	Matrix^ GetRotation(Vector3 angles);

	Matrix^ GetScale(Vector3 ratios);
};