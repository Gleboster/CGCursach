#pragma once
#include "View.h"

namespace MVC {
	public ref class ViewSurfaces : View {
	public:
		ViewSurfaces()
		{

		}

		void ShowScene(Scene^ scene) override {
			ShowSurfaces(FindVisibleSurfaces(scene->AllSurfaces, scene->CameraPosition));
		}

	private:
		array<Surface>^ FindVisibleSurfaces(array<Surface>^ source, Vector3 positionCamera) {
			Matrix^ matrixVolume = Surface::GetMatrix(source);

			BaseMatrix^ matrixCamera = Vector3::GorizontalMatrix(positionCamera);
			matrixCamera[0, 3] = 0;

			Matrix^ checkedMatrix = gcnew Matrix(matrixCamera) * matrixVolume;

			List<Surface>^ visibleSurfaces = gcnew List<Surface>();
			for (int i = 0; i < checkedMatrix->Columns; i++)
				if (checkedMatrix[0, i] > 0)
					visibleSurfaces->Add(source[i]);

			return visibleSurfaces->ToArray();
		}

		void ShowSurfaces(array<Surface>^ surfaces) {
			_outputDisplay->Clear();
			for each (Surface s in surfaces)
			{
				ShowSegments(s.AllSegments);

			}
			_outputDisplay->Update();
		}

		void ShowSegments(array<Segment>^ segmets) {
			for each (Segment s in segmets)
				_outputDisplay->DrawingSegment(s);
		};
	};
}