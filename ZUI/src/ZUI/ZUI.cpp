#include "ZUI.h"
#include "../ZUI/Draw/DrawHelper/DrawHelper.h"
using namespace ZUI;

FrameState ZUI::g_FrameState;

DrawList& ZUI::GetDrawList() {
	static DrawList frameDrawList;
	return frameDrawList;
}

EventQueue& ZUI::GetEventQueue() {
	static EventQueue eventQueue;
	return eventQueue;
}

void ZUI::AddEvent(Event event) {
	GetEventQueue().push(event);
}

static std::mutex frameRenderMtx;

void ZUI::StartFrame() {
	if (!frameRenderMtx.try_lock()) {
		ZUI_ERROR("ZUI::StartFrame() cannot start a frame before another thread ends one!");
	}

	GetDrawList().Clear();
	DrawHelper::ResetDrawLevel();
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
