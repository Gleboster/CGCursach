#pragma once

namespace Window {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	public ref class Viewport : public MVCLibrary::Window::AViewPort
	{
		Bitmap^ _bitmap;
		Graphics^ _graphics;

	public:
		Viewport()
		{
			_bitmap = gcnew Bitmap(Width, Height);
			_graphics = Graphics::FromImage(_bitmap);

			Clear();
			Update();
		}

		virtual void Draw(MVCLibrary::Window::Image^ image) override;

	protected:
		void OnSizeChanged(EventArgs^ ea) override;

	private:
		void Update();
		void Clear();
	};

}