#include "DrawCMD.h"

#include "../ClientFuncs/ClientFuncs.h"

void ZUI::DrawCMD_Rect::Execute() {
	// TODO: Support rounded rects (RenderPolygon)
	CF_RenderRect(this->area, this->color, this->filled);
}

void ZUI::DrawCMD_Line::Execute() {
	CF_RenderLine(this->start, this->end, this->color, this->width);
}

void ZUI::DrawCMD_Polygon::Execute() {
	CF_RenderPolygon(this->points, this->color, this->filled);
}

void ZUI::DrawCMD_Text::Execute() {
	CF_RenderText(this->text, this->font, this->pos, this->color);
}