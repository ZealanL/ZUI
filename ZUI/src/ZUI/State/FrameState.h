#pragma once
#include "../Draw/DrawCMD.h"

namespace ZUI {
	// State created for and maintained during a frame
	struct FrameState {

		Area drawArea;

		// clipAreaStack.top is current clipping area when a DrawCmd is created
		std::stack<Area> clipAreaStack;

		FrameState() {}

		FrameState(Area drawArea) {
			clipAreaStack.push(drawArea);
		}

		void PushClipArea(Area area) {
			clipAreaStack.push(area);
		}

		void PopClipArea() {
			clipAreaStack.pop();
		}
	};
}