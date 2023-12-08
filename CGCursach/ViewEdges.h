#pragma once
#include "View.h"

namespace MVC {
	public ref class ViewEdges : View {
	public:
		ViewEdges()
		{

		}

		void ShowScene(Scene^ scene) override {
			ShowSegments(scene->AllSegments);
		}

	private:
		void ShowSegments(array<Segment>^ segmets) {
			_outputDisplay->Clear();
			for each (Segment s in segmets)
				_outputDisplay->DrawingSegment(s);
			_outputDisplay->Update();
		};
	};
}