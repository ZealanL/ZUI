#pragma once
#include "../Types/Area.h"
#include "../Types/Color.h"
// Functions that the client needs to implement (prefixed with CF)

namespace ZUI {
	void CF_RenderRect(Area area, Color color, bool filled);
	void CF_RenderLine(Vec start, Vec end, Color color, float width);
	void CF_RenderText(string text, FontIndex fontIndex, Vec pos, Color color);
	void CF_RenderPolygon(SList<Vec> points, Color color, bool filled);

	// Returns what size some text would be, of a given font
	Vec	CF_GetTextSize(FontIndex font, string text);
}