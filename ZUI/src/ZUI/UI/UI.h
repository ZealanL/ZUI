#pragma once
#include "../Types/Area.h"

namespace ZUI {
	void StartWindow(Area windowArea);
	void EndWindow();

	// Area in which we are currently drawing UI
	Area GetUIArea();

	// Get the area for an item of a certain height, will increment g_FrameState.drawUIHeight and pad
	// If height is 0, will be set to g_Config.sizes.baseItemHeight
	Area ConsumeItemArea(float height = 0);
}