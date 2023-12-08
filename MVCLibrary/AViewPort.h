#pragma once
#include "Image.h"

namespace MVCLibrary {
	namespace Window {
		public ref class AViewPort abstract : public System::Windows::Forms::PictureBox {
		public:
			virtual void Draw(MVCLibrary::Window::Image^ image) = 0;
		};
	}
}