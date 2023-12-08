#pragma once
#include "Node.h"

public ref class Edge {
public:
	initonly Node^ From;
	initonly Node^ To;

	Edge(Node^ node1, Node^ node2)
	{
		From = node1;
		To = node2;
	}

	Node^ GetReverse(Node^ node) {
		if (node == From)
			return To;
		else if (node == To)
			return From;
		else
			throw gcnew System::ArgumentException();
	}

	System::String^ ToString() override {
		return System::String::Format("{0} <-> {1}", From, To);
	}
};