#pragma once
#include "../Framework.h"

namespace ZUI {
	typedef byte KeyCode;

	enum EventType : byte {
		E_KEYDOWN,
		E_KEYUP,
		E_MOUSEMOVE,
	};

	struct Event {
		EventType type;

		// Only for key events
		KeyCode key;

		// If these are set, they will update known mouse position regardless of EventType
		int mouseX = -1, mouseY = -1;
	};

	typedef std::queue<Event> EventQueue;
}