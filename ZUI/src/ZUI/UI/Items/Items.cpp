#include "Items.h"
#include "../../Draw/DrawHelper/DrawHelper.h"
#include "../../ZUI.h"

using namespace ZUI;
using namespace DrawHelper;

void DrawWidgetRect(Area area) {
	FillRect(area, g_Config.colors.widgetBg);

	if (g_Config.colors.outline.a > 0)
		OutlineRect(area, g_Config.colors.outline);
}

bool ZUI::Items::Button(string text) {
	Area area = ConsumeItemArea();
	DrawWidgetRect(area);
	Text(text, area.Center(), g_Config.colors.text);

	return false;
}