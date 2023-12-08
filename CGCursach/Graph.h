#pragma once
#include "Node.h"
#include "Edge.h"
#include "Circle.h"

public ref class Graph {
private:
	array<Node^>^ _nodes;
	List<Edge^>^ _edges;
	List<Circle^>^ _circles;

public:
	Graph(int nodesCount)
	{
		_nodes = gcnew array<Node^>(nodesCount);
		_edges = gcnew List<Edge^>();
		_circles = gcnew List<Circle^>();

		for (int i = 0; i < nodesCount; i++)
			_nodes[i] = gcnew Node(i);
	}

	property int Length { int get() { return _nodes->Length; } }

	property array<Edge^>^ Edges {array<Edge^>^ get() { return _edges->ToArray(); }}

	property array<Circle^>^ Circles {
		array<Circle^>^ get() { return _circles->ToArray(); }
		void set(array<Circle^>^ value) {
			_circles->Clear();

			for each (auto circle in value)
				_circles->Add(circle);
		}
	}

	Node^ operator()(int index) {
		return _nodes[index];
	}

	void Connect(int index1, int index2)
	{
		for each (Track ^ track in FindPathes(_nodes[index1], _nodes[index2]))
			_circles->Add(gcnew Circle(track));

		_edges->Add(gcnew Edge(_nodes[index1], _nodes[index2]));
	}

	static Graph^ MakeGraph(... array<int>^ incidentNodes)
	{
		int maxNode = incidentNodes[0];
		for each (int val in incidentNodes)
			if (val > maxNode)
				maxNode = val;

		auto graph = gcnew Graph(maxNode + 1);
		for (int i = 0; i < incidentNodes->Length - 1; i += 2)
			graph->Connect(incidentNodes[i], incidentNodes[i + 1]);
		return graph;
	}

private:
	List<Track^>^ FindPathes(Node^ from, Node^ to) {
		auto tracks = gcnew List<Track^>();

		for each (Node ^ incidentNode in GetIncidentNodes(from)) {
			auto direction = gcnew Track(from, incidentNode);
			for each (Track ^ track in GetMinPathesTo(direction, to))
				tracks->Add(track);

		}

		return tracks;
	}

	array<Track^>^ GetMinPathesTo(Track^ direction, Node^ to) {
		Queue<Track^>^ queue = gcnew Queue<Track^>();

		queue->Enqueue(direction);
		while (queue->Count != 0)
		{
			Track^ currentTrack = queue->Dequeue();

			for each (Node ^ incindent in GetIncidentNodes(currentTrack->Last))
			{

				if (!currentTrack->isStepBack(incindent))
					queue->Enqueue(currentTrack->Add(incindent));
			}

			for each (Track ^ current in queue)
				if (current->Last == to)
					goto endSearch;
		}

	endSearch:

		auto result = gcnew List<Track^>();
		for each (Track ^ current in queue)
			if (current->Last == to)
				result->Add(current);

		return result->ToArray();
	}

	List<Edge^>^ GetIncidentEdges(Node^ node) {
		auto result = gcnew List<Edge^>();

		for each (Edge ^ e in _edges)
			if (e->From == node || e->To == node)
				result->Add(e);

		return result;
	}

	List<Node^>^ GetIncidentNodes(Node^ node) {
		auto result = gcnew List<Node^>();

		for each (Edge ^ e in GetIncidentEdges(node))
			result->Add(e->GetReverse(node));

		return result;
	}
};