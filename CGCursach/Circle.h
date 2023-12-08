#pragma once
#include "Node.h"
#include "Edge.h"
#include "Track.h"

ref class Circle {
	array<Node^>^ _nodes;
	array<Edge^>^ _edges;

public:
	Circle(Track^ track)
	{
		auto tracknodes = _nodes = track->Nodes;
		
		_edges = gcnew array<Edge^>(tracknodes->Length);
		for (int i = 0; i < tracknodes->Length; i++)
			_edges[i] = gcnew Edge(tracknodes[i], tracknodes[(i + 1) % tracknodes->Length]);
	}

	property int Len {
		int get() { return _nodes->Length; }
	}

	property array<Node^>^ Nodes {
		array<Node^>^ get() {
			array<Node^>^ result = gcnew array<Node^>(_nodes->Length);
			_nodes->CopyTo(result, 0);
			return result;
		}
	}
	property array<Edge^>^ Edges {
		array<Edge^>^ get() {
			array<Edge^>^ result = gcnew array<Edge^>(_edges->Length);
			_edges->CopyTo(result, 0);
			return result;
		}
	}



	String^ ToString() override {
		auto result = gcnew System::Text::StringBuilder();

		for each (int a in _nodes) {
			result->Append(a);
			result->Append(" -> ");
		}
		
		return result->ToString();
	}
};