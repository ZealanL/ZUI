#pragma once
#include "../DrawCMD.h"

namespace ZUI {
	namespace DrawUtil {
		// Client needs to implement this
		Vec GetTextSize(FontIndex font, string text);
	}
}