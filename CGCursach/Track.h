#pragma once
#include "Node.h"

ref class Track {
	List<Node^>^ _nodes;
public:
	Track(... array<Node^>^ nodes)
	{
		_nodes = gcnew List<Node^>();

		for each (auto node in nodes)	
			_nodes->Add(node);
	}

	property int Len {
		int get() { return _nodes->Count; }
	}

	property Node^ Last {
		Node^ get() { return _nodes[_nodes->Count - 1]; }
	}

	property array<Node^>^ Nodes {
		array<Node^>^ get() { return _nodes->ToArray(); }
	}

	Track^ Add(Node^ node) {
		auto newNodes = gcnew array<Node^>(_nodes->Count + 1);

		for (int i = 0; i < _nodes->Count; i++)
			newNodes[i] = _nodes[i];
			
		newNodes[_nodes->Count] = node;
		
		return gcnew Track(newNodes);
	}

	bool isStepBack(Node^ node) {
		return _nodes->Contains(node);
	}
};