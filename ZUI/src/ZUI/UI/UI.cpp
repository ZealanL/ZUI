#include "UI.h"

#include "../ZUI.h"
#include "../Draw/DrawHelper/DrawHelper.h"
using namespace ZUI;

// TODO: Move (?)
bool inWindow = false;
void ZUI::StartWindow(Area windowArea) {
	if (inWindow) {
		return ZUI_ERROR("Cannot call ZUI::StartWindow() again before ZUI::EndWindow()");
	} else {
		ZUI::g_FrameState.windowIndex++;
		inWindow = true;
	}

	g_FrameState.windowArea = windowArea;
	g_FrameState.drawUIHeight = 0;
	g_FrameState.clipAreaStack.push(windowArea);

	DrawHelper::FillRect(windowArea, g_Config.colors.windowBg);

	g_FrameState.drawLevel++;
	
}

void ZUI::EndWindow() {
	if (!inWindow) {
		return ZUI_ERROR("Cannot call ZUI::EndWindow() before ZUI::StartWindow()");
	} else {
		inWindow = false;
	}

	g_FrameState.drawLevel--;

	g_FrameState.clipAreaStack.pop();
}

Area ZUI::GetUIArea() {
	return g_FrameState.windowArea.Expand(-g_Config.sizes.padding);
}

Area ZUI::ConsumeItemArea(float height) {
	if (height == 0)
		height = g_Config.sizes.baseItemHeight;

	Area resultArea = GetUIArea().Row(height, false);
	resultArea.Move(Vec(0, g_FrameState.drawUIHeight));
	g_FrameState.drawUIHeight += height + g_Config.sizes.padding.y;
	return resultArea;
}
