#pragma once
#include "Vector3.h"

public value struct Segment
{
private:
	Vector3 Corner1;
	Vector3 Corner2;

public:
	property Vector3 Start {
		Vector3 get() {
			if (Corner1.Y != Corner2.Y) {
				return Corner1.Y < Corner2.Y ? Corner1 : Corner2;
			}
			return Corner1.X < Corner2.X ? Corner1 : Corner2;
		};
	};
	property Vector3 End {
		Vector3 get() { return Start == Corner1 ? Corner2 : Corner1; };
	};

	Segment(Vector3 corner1, Vector3 corner2) {
		Corner1 = corner1;
		Corner2 = corner2;
	}

	//TODO: скорее всего это не его ответсвенность поэтому удали
	Vector3^ GetPointOnSegment(double y) {
		auto k = (Corner1.X - Corner2.X) / (Corner1.Y - Corner2.Y);
		auto b = End.X - End.Y * k;
		return gcnew Vector3(k * y + b, y);
	}

	System::String^ ToString() override {
		return System::String::Format("{0} <-> {1}", Corner1, Corner2);
	}

	static array<Vector3>^ GetAllPointsFrom(array<Segment>^ segments) {
		auto points = gcnew System::Collections::Generic::List<Vector3>();

		for each (Segment s in segments)
		{
			if (!points->Contains(s.Start))
				points->Add(s.Start);

			if (!points->Contains(s.End))
				points->Add(s.End);
		}
		return points->ToArray();
	}

	//static array<Vector3>^ GetArrayPointsFrom(array<Segment>^ segments) {
	//	return GetAllPointsFrom(segments)->ToArray();
	//}

	//static 
};

