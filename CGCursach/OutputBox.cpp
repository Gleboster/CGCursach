#include "OutputBox.h"

void OutputBox::OnSizeChanged(EventArgs^ ea)
{
	PictureBox::OnSizeChanged(ea);
	delete _bitmap, _graphics;

	_bitmap = gcnew Bitmap(Width, Height);
	_graphics = Graphics::FromImage(_bitmap);
	Clear();
	this->Image = _bitmap;
}

void OutputBox::Clear() {
	_graphics->Clear(_colorBackground);
}

void OutputBox::Update()
{
	this->Image = _bitmap;
}

OutputBox::OutputBox()
{
	_colorBackground = Color::White;
	_pen = gcnew Pen(Color::Black, 3);

	_bitmap = gcnew Bitmap(Width, Height);
	_graphics = Graphics::FromImage(_bitmap);
	Clear();
	this->Image = _bitmap;
}

void OutputBox::DrawingSegment(Segment segment)
{
	_graphics->DrawLine(_pen, ConvertPoint(segment.Start), ConvertPoint(segment.End));
}

Drawing::Point OutputBox::ConvertPoint(Vector3 v_point)
{
	return Drawing::Point(ConvertX(v_point.X), ConvertY(v_point.Y));
}

int OutputBox::ConvertX(double x)
{
	return x * unit + this->Width / 2;
}

int OutputBox::ConvertY(double y)
{
	return -y * unit + this->Height / 2;
}


