#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace MVCLibrary;

namespace Window {

	public ref class TransformPanel : public MVCLibrary::Window::ATransformPanel
	{
	public:
		TransformPanel() {
			CreateTrasformBoxes();
			DeployTrasformPanel();
		}

		void ShowTransform(TransformGrid<TransformValueAbsolute^>^ transformGrid) override;

		void ChangeTransform(TransformValue^ transformChanges);

	private:
		ref class TransformBox : public TextBox {
			Transformation _transformation;
			Coordinate _coordinate;

			TransformPanel^ _parentPanel;

		public:
			TransformBox(const Transformation& transformation, const Coordinate& coordinate, TransformPanel^ parentPanel)
				: _transformation(transformation), _coordinate(coordinate), _parentPanel(parentPanel) {};

		protected:
			String^ _beforeInput;
			
			void OnEnter(EventArgs^ ea) override;

			void OnKeyDown(KeyEventArgs^ kea) override;

			void OnLeave(EventArgs^ ea) override;


		private:
			void TryChangeValue();
			void ChangeValueDelta(int delta);
		};

		TransformGrid<TransformBox^>^ _boxes;

		void CreateTrasformBoxes();
		void DeployTrasformPanel();

		
		ref class DeployerTrasformPanel {
			static const int GapBehindTransformBoxes = 12;
			static const int CountTransformBoxesRow = 3;

			Drawing::Font^ FontTitleManipulation = gcnew Drawing::Font("Verdana", 12, Drawing::FontStyle::Bold);
			Drawing::Font^ FontTitleCoordinate = gcnew Drawing::Font("Verdana", 10, Drawing::FontStyle::Regular);

			TransformGrid<TransformBox^>^ _boxes;
			TransformPanel^ _transformPanel;

			int height;
		public:
			DeployerTrasformPanel(TransformPanel^ transformPanel, TransformGrid<TransformBox^>^ boxes) :
				_transformPanel(transformPanel), _boxes(boxes) {};

			void DeployPanel();
		private:
			void DeployRowTransformation(Transformation transformation, TransformGrid<TransformBox^>::RowGrid^ row);
			Control^ DeployTitle(Transformation transformation);
			Control^ DeployBoxes(TransformGrid<TransformBox^>::RowGrid^ rowTransform);

			Label^ GetTitleTransformation(Transformation transformation);
			Label^ GetTitleCoordinate(Coordinate coordinate);
		};

		DeployerTrasformPanel^ _deployerTransformPanel;

	protected:
		void OnSizeChanged(EventArgs^ ea) override;
	};

}