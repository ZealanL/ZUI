// Configuration state for ZUI

#pragma once
#include "../Types/Area.h"
#include "../Types/Color.h"

namespace ZUI {
	struct Config {
		struct {
			Color text = Color(255, 255, 255);
			Color outline = Color(255, 255, 255, 100);
			
			Color windowBg = Color(30, 30, 30);
			Color sectionBg = Color(38, 38, 38);

			Color itemBg = Color(25, 25, 25, 255);
			Color itemHoverOverlay = Color(255, 255, 255, 20);
		} colors;

		struct {
			float baseItemHeight = 20;
			Vec padding = Vec(8, 8);
		} sizes;
	};
}
