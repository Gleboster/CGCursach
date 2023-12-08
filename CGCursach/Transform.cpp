#include "Transform.h"

Transform::Transform()
{
	BaseMatrix^ unitMatrix = gcnew BaseMatrix(4, 4);
	unitMatrix->FillMainDiagonal();
	_transformation = gcnew Matrix(unitMatrix);
	_position = gcnew Matrix(unitMatrix);
	_rotation = gcnew Matrix(unitMatrix);
	_scale = gcnew Matrix(unitMatrix);

	_generator = gcnew GeneratorMatrix();
	_ratios = gcnew PanelValues();
}

void Transform::SetRatio(Manipulation manipulation, Coordinate coordinate, double value)
{
	_ratios[manipulation, coordinate] = value;
	ChangeMatrixTransformation(manipulation, coordinate, value);
}

void Transform::ChangeRatioDelta(Manipulation manipulation, Coordinate coordinate, double delta)
{
	SetRatio(manipulation, coordinate, _ratios[manipulation, coordinate] + delta);
}

void Transform::ChangeMatrixTransformation(Manipulation manipulation, Coordinate coordinate, double delta)
{
	Vector3 shifts = _ratios->GetShifts(manipulation);

	switch (manipulation)
	{
	case Manipulation::Position:
		_position = _generator->GetPosition(shifts);
		break;
	case Manipulation::Rotation:
		_rotation = _generator->GetRotation(shifts);
		break;
	case Manipulation::Scale:
		_scale = _generator->GetScale(shifts);
		break;
	default:
		break;
	}

	_transformation = _position * _rotation * _scale;

	//auto currentMatrix = BuildNewMatrixTransformation(manipulation, coordinate, delta);

	//if (manipulation == Manipulation::Rotation || manipulation == Manipulation::Position)
	//	_transformation = currentMatrix * _transformation; //Глобальное
	//else
	//	_transformation = _transformation * currentMatrix; //Локальный


	//if (manipulation == Manipulation::Position)
	//	_curAnchor = _curAnchor * currentMatrix;
}

//Matrix^ Transform::BuildNewMatrixTransformation(Manipulation manipulation, Coordinate coordinate, double delta)
//{
//	BaseMatrix^ newMatrix = gcnew BaseMatrix(4, 4);
//	newMatrix->FillMainDiagonal();
//
//	switch (manipulation)
//	{
//	case Manipulation::Position:
//		SetPosition(newMatrix, coordinate, delta);    //TODO: ебни сюда Translate Anchor 
//		break;
//	case Manipulation::Rotation:
//		SetRotation(newMatrix, coordinate, delta);
//		break;
//	case Manipulation::Scale:
//		SetScale(newMatrix, coordinate, delta);
//		break;
//	}
//
//	return gcnew Matrix(newMatrix);
//}

//void Transform::SetPosition(BaseMatrix^ matrix, Coordinate coordinate, double delta)
//{
//	matrix[(int)coordinate, 3] = delta;
//}
//
//void Transform::SetRotation(BaseMatrix^ matrix, Coordinate coordinate, double delta)
//{
//	double deltaRad = delta * 3.141593 / 180;
//	double cos = std::cos(deltaRad);
//	double sin = std::sin(deltaRad);
//
//	double x = Anchor.X;
//	double y = Anchor.Y;
//	double z = Anchor.Z;
//
//	if (coordinate == Coordinate::X)
//	{
//		matrix[1, 1] = cos;
//		matrix[1, 2] = -sin;
//		matrix[2, 1] = sin;
//		matrix[2, 2] = cos;
//		matrix[1, 3] = y * (1 - cos) + z * sin;
//		matrix[2, 3] = z * (1 - cos) - y * sin;
//	}
//	else if (coordinate == Coordinate::Y)
//	{
//		matrix[0, 0] = cos;
//		matrix[0, 2] = sin;
//		matrix[2, 0] = -sin;
//		matrix[2, 2] = cos;
//		matrix[0, 3] = x * (1 - cos) - z * sin;
//		matrix[2, 3] = z * (1 - cos) + x * sin;
//	}
//	else if (coordinate == Coordinate::Z) {
//		matrix[0, 0] = cos;
//		matrix[0, 1] = -sin;
//		matrix[1, 0] = sin;
//		matrix[1, 1] = cos;
//		matrix[0, 3] = x * (1 - cos) + y * sin;
//		matrix[1, 3] = y * (1 - cos) - x * sin;
//	}
//}
//
//void Transform::SetScale(BaseMatrix^ matrix, Coordinate coordinate, double delta)
//{
//	double newCurrentVal = _ratios[Manipulation::Scale]->default[coordinate];
//	double value = newCurrentVal / (newCurrentVal - delta);
//	matrix[(int)coordinate, (int)coordinate] = value;
//	//matrix[(int)coordinate, 3] = _curAnchor[coordinate] * (value - 1);
//}

Transform::PanelValues::PanelValues()
{
	_values = gcnew Dictionary<Manipulation, Dictionary<Coordinate, double>^>();

	for each (Manipulation manip in Enum::GetValues(Manipulation::typeid))
		_values[manip] = gcnew Dictionary<Coordinate, double>();

	for each (Coordinate coord in Enum::GetValues(Coordinate::typeid))
	{
		_values[Manipulation::Position]->default[coord] = 0;
		_values[Manipulation::Rotation]->default[coord] = 0;
		_values[Manipulation::Scale]->default[coord] = 1;
	}
}
