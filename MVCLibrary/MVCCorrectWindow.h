#pragma once
#include "ATransformPanel.h"
#include "AViewPort.h"

namespace MVCLibrary {
	namespace Window {
		public interface class IMVCCorrectWindow
		{
		public:
			ATransformPanel^ GetTransformPanel();
			AViewPort^ GetViewport();
		};
	}
}