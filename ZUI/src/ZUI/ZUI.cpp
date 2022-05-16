#include "ZUI.h"

#include "../ZUI/Draw/DrawHelper/DrawHelper.h"
using namespace ZUI;

FrameState	ZUI::g_FrameState;
InputState	ZUI::g_InputState;
Config		ZUI::g_Config;

DrawList& ZUI::GetDrawList() {
	static DrawList frameDrawList;
	return frameDrawList;
}

EventQueue& ZUI::GetEventQueue() {
	// TODO: Move(?)
	static EventQueue eventQueue;
	return eventQueue;
}

void ZUI::AddEvent(Event event) {
	GetEventQueue().push(event);
}

void ProcessEvents() {
	auto& eventQueue = GetEventQueue();
	if (eventQueue.empty())
		return;

	for (Event& e = eventQueue.front(); !eventQueue.empty(); eventQueue.pop()) {

		if (e.mouseX >= 0 && e.mouseY >= 0)
			g_InputState.mousePos = Vec(e.mouseX, e.mouseY);

		switch (e.type) {
		case EventType::E_MOUSEMOVE:
			break;
		case EventType::E_KEYDOWN:
		case EventType::E_KEYUP:
			// TODO: Implement
			break;
		default:
			ZUI_ERROR("Invalid event type");
		}
	}
}

// TODO: Move(?)
static std::mutex frameRenderMtx;
void ZUI::StartFrame() {
	if (!frameRenderMtx.try_lock()) {
		ZUI_ERROR("ZUI::StartFrame() cannot start a frame before another thread ends one!");
	}

	ProcessEvents();

	GetDrawList().Clear();
	g_FrameState = FrameState();
}

void ZUI::EndFrame() {
	GetDrawList().ExecuteAll();

	if (frameRenderMtx.try_lock()) {
		ZUI_ERROR("ZUI::EndFrame() called without ZUI::StartFrame()!");
	}
	frameRenderMtx.unlock();
}

static FontIndex curFontIndex;
void ZUI::SetCurrentFontIndex(FontIndex newIndex) {
	curFontIndex = newIndex;
}

FontIndex ZUI::GetCurrentFontIndex() {
	return curFontIndex;
}
