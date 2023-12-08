#pragma once
#include "Segment.h"

using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class OutputBox : PictureBox {
	const double unit = 3 / 0.1;

	Bitmap^ _bitmap;
	Graphics^ _graphics;

	Drawing::Color _colorBackground;
	Pen^ _pen;

	/*Drawing::Color _colorShape;*/
public:
	OutputBox();

	property Drawing::Color ColorBackground {
		Drawing::Color get() { return _colorBackground; }
		void set(Drawing::Color value) {
			_colorBackground = value;
			Clear();
		}
	};

	property Drawing::Color ColorLine {
		Drawing::Color get() { return _pen->Color; }
		void set(Drawing::Color value) { _pen->Color = value; }
	};

	property int WidthLine {
		int get() { return _pen->Width; }
		void set(int value) { _pen->Width = value; }
	}

	void DrawingSegment(Segment segment);
	void Clear();
	void Update();

	void OnSizeChanged(EventArgs^ ea) override;

private:

	Drawing::Point ConvertPoint(Vector3 v_point);
	int ConvertX(double x);
	int ConvertY(double y);

};