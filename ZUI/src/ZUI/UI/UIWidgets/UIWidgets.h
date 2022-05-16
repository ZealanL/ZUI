#pragma once
#include "../../Types/Area.h"

namespace ZUI {
	namespace UIWidgets {
		// Returns true if clicked this frame
		bool Button(string text);

		// Returns true if changed this frame
		bool Checkbox(string text, bool* value);

		// Returns true if being used
		// suffix: Text to append to the value string (e.x. "%")
		bool SliderInt(string text, int* value, int min, int max, string suffix = "");

		// Returns true if being used
		// suffix: Text to append to the value string (e.x. "%")
		bool SliderFloat(string text, float* value, float min, float max, string suffix = "");
	}
}