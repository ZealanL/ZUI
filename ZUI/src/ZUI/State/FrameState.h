#pragma once
#include "../Draw/DrawCMD.h"

namespace ZUI {
	// State created for and maintained during a frame
	struct FrameState {

		int windowIndex = -1; // Incremented when window is started
		int drawLevel = 0;
		bool inOverlayMode = false;

		// Current UI draw level
		int GetCurrentDrawLevel() {
			return drawLevel;
		}

		// Actual draw level that will be used for new DrawCMDs
		int GetTrueDrawLevel() {
			// First priority: overlay mode
			// Second priority: window index
			// Third priority: current UI draw level
			return drawLevel + (windowIndex << 20) + (inOverlayMode << 30);
		}

		Area windowArea; // Area of the current window
		float drawUIHeight; // Starts at 0 when window is started, extends down as we add things to the window

		// clipAreaStack.top is current clipping area when a DrawCmd is created
		std::stack<Area> clipAreaStack;

		FrameState() {}

		FrameState(Area drawArea) {
			clipAreaStack.push(drawArea);
		}
	};
}