#pragma once
#include "../DrawCMD.h"

namespace ZUI {
	namespace DrawHelper {
		void FillRect(Vec start, Vec end, Color color, float rounding = 0);
		void FillRect(Area area, Color color, float rounding = 0);
		void OutlineRect(Vec start, Vec end, Color color, float rounding = 0);
		void OutlineRect(Area area, Color color, float rounding = 0);

		void Line(Vec start, Vec end, Color color, float width = 1);

		void Text(string text, Vec pos, Color color, Vec centering = Vec(0.5f, 0.5f));
	}
}