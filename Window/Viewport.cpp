#include "Viewport.h"

namespace Window {
    void Viewport::Draw(MVCLibrary::Window::Image^ image)
    {
        for (int y = 0; y < image->GetHeight(); y++)
            for (int x = 0; x < image->GetWidth(); x++) {
                _bitmap->SetPixel(x, y, image->GetColor(x, y));
            }
        Update();
    }

    void Window::Viewport::OnSizeChanged(EventArgs^ ea)
    {
        PictureBox::OnSizeChanged(ea);
        delete _bitmap, _graphics;

        _bitmap = gcnew Bitmap(Width, Height);
        _graphics = Graphics::FromImage(_bitmap);
        Clear();
        Update();
    }

    void Viewport::Update()
    {
        this->Image = _bitmap;
    }

    void Viewport::Clear()
    {
        _graphics->Clear(Color::Aqua);
    }
}