#pragma once

using namespace System::Collections::Generic;

public ref class Node {
public:
	initonly int Number;
	Node(int num) : Number(num) {};

	operator int() {
		return Number;
	}

	bool operator == (Node ^ other) {
		return Number == other->Number;
	}

	System::String^ ToString() override {
		return System::String::Format("{0}", Number);
	}
};
