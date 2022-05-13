#pragma once
#include "../DrawCMD.h"

namespace ZUI {
	namespace DrawHelper {

		// If true, we increase drawcount a bunch to render on top of everything as an (overlay)
		void SetOverlayMode(bool overlayMode);

		int GetCurrentDrawLevel();
		int GetTrueDrawLevel(); // Like GetCurrentDrawLevel, but accounts for overlay mode
		void IncDrawLevel();
		void DecDrawLevel();
		void ResetDrawLevel();

		void FillRect(Vec start, Vec end, Color color, float rounding = 0);
		void FillRect(Area area, Color color, float rounding = 0);
		void OutlineRect(Vec start, Vec end, Color color, float rounding = 0);
		void OutlineRect(Area area, Color color, float rounding = 0);

		void Line(Vec start, Vec end, Color color, float width = 1);

		void Text(string text, Vec pos, Color color, Vec centering = Vec(0.5f, 0.5f));
	}
}