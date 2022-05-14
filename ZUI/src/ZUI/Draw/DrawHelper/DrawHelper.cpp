#include "DrawHelper.h"
#include "../../ZUI.h"

#include "../../ClientFuncs/ClientFuncs.h"
using namespace ZUI;

#define DL GetDrawList()

bool inOverlayMode = false;
void ZUI::DrawHelper::SetOverlayMode(bool newOverlayMode) {
	inOverlayMode = newOverlayMode;
}

int curDrawLevel = 0;

int ZUI::DrawHelper::GetCurrentDrawLevel() {
	return curDrawLevel;
}

int ZUI::DrawHelper::GetTrueDrawLevel() {
	return curDrawLevel + (inOverlayMode ? 0 : 0x10000);
}

void ZUI::DrawHelper::IncDrawLevel() {
	curDrawLevel++;
}

void ZUI::DrawHelper::DecDrawLevel() {
	ZUI_ASSERT(curDrawLevel > 0);
	curDrawLevel--;
}

void ZUI::DrawHelper::ResetDrawLevel() {
	curDrawLevel = 0;
}

void Rect(Area area, Color color, float rounding, bool filled) {
	auto cmd = new DrawCMD_Rect(DrawHelper::GetTrueDrawLevel());
	cmd->area = area;
	cmd->color = color;
	cmd->rounding = rounding;
	cmd->filled = filled;

	DL.Add(cmd);
}

void ZUI::DrawHelper::FillRect(Vec start, Vec end, Color color, float rounding) {
	return Rect(Area(start, end), color, rounding, true);
}

void ZUI::DrawHelper::FillRect(Area area, Color color, float rounding) {
	return Rect(area, color, rounding, true);
}

void ZUI::DrawHelper::OutlineRect(Vec start, Vec end, Color color, float rounding) {
	return Rect(Area(start, end), color, rounding, false);
}

void ZUI::DrawHelper::OutlineRect(Area area, Color color, float rounding) {
	return Rect(area, color, rounding, false);
}

void ZUI::DrawHelper::Line(Vec start, Vec end, Color color, float width) {
	auto cmd = new DrawCMD_Line(GetTrueDrawLevel());
	cmd->start = start;
	cmd->end = end;
	cmd->color = color;
	cmd->width = width;

	DL.Add(cmd);
}

void ZUI::DrawHelper::Text(string text, Vec pos, Color color, Vec centering) {
	if (text.empty())
		return;

	auto cmd = new DrawCMD_Text(GetTrueDrawLevel());
	cmd->text = text;
	cmd->font = GetCurrentFontIndex();
	cmd->pos = pos - CF_GetTextSize(GetCurrentFontIndex(), text) * centering;
	cmd->color = color;

	DL.Add(cmd);
}