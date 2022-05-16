#include "UI.h"

#include "../ZUI.h"
#include "../Draw/DrawHelper/DrawHelper.h"
using namespace ZUI;

// TODO: Move (?)
void ZUI::StartWindow(Area windowArea) {
	if (g_FrameState.inWindow) {
		return ZUI_ERROR("Cannot call StartWindow() again before EndWindow()");
	} else {
		g_FrameState.windowIndex++;
		g_FrameState.inWindow = true;
	}

	g_FrameState.windowArea = windowArea;
	g_FrameState.drawUIHeight = 0;
	g_FrameState.clipAreaStack.push(windowArea);

	DrawHelper::FillRect(windowArea, g_Config.colors.windowBg);

	g_FrameState.drawLevel++;
	
}

void ZUI::EndWindow() {
	if (!g_FrameState.inWindow) {
		return ZUI_ERROR("Cannot call EndWindow() before StartWindow()");
	} else {
		g_FrameState.inWindow = false;
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

bool ZUI::IsMouseInArea(Area area) {
	return area.Contains(g_InputState.mousePos);
}