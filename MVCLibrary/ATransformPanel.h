#pragma once
#include "TransformGrid.h"

namespace MVCLibrary {
	namespace Window {
		public ref class ATransformPanel : System::Windows::Forms::UserControl {
		public:
			event System::Action<TransformValue^>^ TransformChanged;

			virtual void ShowTransform(TransformGrid<TransformValueAbsolute^>^ transformGrid) = 0;
		};
	}
}