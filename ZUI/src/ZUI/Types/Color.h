#pragma once
#include "../Framework.h"

namespace ZUI {
	// An RGBA color
	struct Color {
		byte r, g, b, a;

		Color(byte r = 0, byte g = 0, byte b = 0, byte a = 255) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		// Add a brightness to all RGB values
		// NOTE: Negative brightness is permitted
		Color LinearBrighten(int amount) {
			return Color(
				std::clamp(r + amount, 0, 255),
				std::clamp(g + amount, 0, 255),
				std::clamp(b + amount, 0, 255),
				a
			);
		}

		// Multiply all RGB values by a brightness ratio
		Color RatioBrighten(float ratio) {
			return Color(
				std::clamp(r * ratio, 0.f, 255.f),
				std::clamp(g * ratio, 0.f, 255.f),
				std::clamp(b * ratio, 0.f, 255.f),
				a
			);
		}

		Color WithAlpha(byte alpha) {
			return Color(r, g, b, alpha);
		}

		string ToString() {
			return ZUI_FMT("(%i, %i, %i, %i)", r, g, b, a);
		}
	};

	// Global colors
#define ZUI_COL_WHITE		Color(255, 255, 255)
#define ZUI_COL_BLACK		Color(  0,   0,   0)
#define ZUI_COL_GRAY		Color(100, 100, 100)
#define ZUI_COL_DARK_GRAY	Color( 50,  50,  50)
#define ZUI_COL_RED			Color(255,   0,   0)
#define ZUI_COL_ORANGE		Color(255, 150,   0)
#define ZUI_COL_YELLOW		Color(255, 255,   0)
#define ZUI_COL_GREEN		Color(  0, 255,   0)
#define ZUI_COL_BLUE		Color(  0, 100, 255)
#define ZUI_COL_MAGENTA		Color(  0, 255, 255)

// Color as HSVA ([hue, saturation, value, alpha] aka normal HSV with alpha byte)
	struct HSVColor {
		float h = 0, s = 1, v = 1;
		byte alpha = 255;

		HSVColor() {}

		HSVColor(float hue, float sat = 1, float val = 1) : h(hue), s(sat), v(val) {}

		HSVColor(const Color& color) {
			float r = color.r / 255;
			float g = color.g / 255;
			float b = color.b / 255;

			float max = Max(r, Max(g, b)), min = Min(r, Min(g, b));
			h, s, v = max;

			float d = max - min;
			s = max == 0 ? 0 : d / max;

			if (max == min) {
				h = 0; // achromatic
			} else {
				if (max == r) {
					h = (g - b) / d + (g < b ? 6 : 0);
				} else if (max == b) {
					h = (b - r) / d + 2;
				} else {
					h = (r - g) / d + 4;
				}

				h /= 6;
			}

			this->alpha = color.a;
		}

		operator Color() {
			return GetColor();
		}

		Color GetColor() {
			float r, g, b;

			int i = floor(h * 6);
			float f = h * 6 - i;
			float p = v * (1 - s);
			float q = v * (1 - f * s);
			float t = v * (1 - (1 - f) * s);

			switch (i % 6) {
			case 0: r = v, g = t, b = p; break;
			case 1: r = q, g = v, b = p; break;
			case 2: r = p, g = v, b = t; break;
			case 3: r = p, g = q, b = v; break;
			case 4: r = t, g = p, b = v; break;
			case 5: r = v, g = p, b = q; break;
			}

			return Color(r * 255.f, g * 255.f, b * 255.f, alpha);
		}
	};
}