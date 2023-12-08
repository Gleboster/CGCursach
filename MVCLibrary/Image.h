#pragma once

namespace MVCLibrary {
	namespace Window {
		using namespace System;
		using namespace System::Drawing;

		public ref class Image {
			int _height;
			int _width;
			array<array<Color>^>^ _base;
		public:
			Image(int height, int width)
				: _height(height), _width(width) {
				_base = gcnew array<array<Color>^>(height);

				for (int y = 0; y < height; y++)
					_base[y] = gcnew array<Color>(width);
			}

			int GetHeight() {
				return _height;
			}

			int GetWidth() {
				return _width;
			}

			Color GetColor(int x, int y) {
				return _base[x][y];
			}

			void SetColor(int x, int y, Color color) {
				_base[x][y] = color;
			}
		};
	}
}