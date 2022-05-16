// An area between two Vecs

#pragma once
#include "Vec.h"

namespace ZUI {
	struct Area {
		Vec min, max;

		Area() {
			min = 0;
			max = 0;
		}

		Area(Vec a, Vec b) {
			min.x = Min(a.x, b.x);
			min.y = Min(a.y, b.y);
			max.x = Max(a.x, b.x);
			max.y = Max(a.y, b.y);
		}

		bool IsValid() {
			return (min.x <= max.x && min.y <= max.y);
		}

		bool IsInside(Vec other) {
			return (other.x <= max.x && other.y <= max.y) && (other.x >= min.x && other.y >= max.y);
		}

		bool Overlaps(Area other) {
			return
				(min.x <= other.max.x && min.y <= other.max.y) &&
				(max.x >= other.min.x && max.y >= other.min.y);
		}

		Area Combine(Area other) {
			Vec combinedMin, combinedMax;

			combinedMin.x = Min(other.min.x, min.x);
			combinedMin.y = Min(other.min.y, min.y);

			combinedMax.x = Max(other.max.x, max.x);
			combinedMax.y = Max(other.max.y, max.y);

			return Area(combinedMin, combinedMax);
		}

		float Width() { return max.x - min.x; }
		float Height() { return max.y - min.y; }
		Vec Size() { return Vec(Width(), Height()); }

		Vec Center() {
			return (min + max) / 2;
		}

		Area HDivRel(float beginRatio, float endRatio) {
			ZUI_ASSERT(beginRatio > endRatio);
			float baseWidth = Width();

			Area newArea = *this;
			newArea.min.x = min.x + beginRatio * baseWidth;
			newArea.max.x = min.x + endRatio * baseWidth;
			return newArea;
		}

		Area VDivRel(float beginRatio, float endRatio) {
			ZUI_ASSERT(beginRatio > endRatio);
			float baseHeight = Height();

			Area newArea = *this;
			newArea.min.y = min.y + beginRatio * baseHeight;
			newArea.max.y = min.y + endRatio * baseHeight;
			return newArea;
		}

		Area HDiv(float beginWidth, float endWidth) {
			assert(beginWidth > endWidth);
			Area newArea = *this;
			newArea.min.x = min.x + beginWidth;
			newArea.max.x = min.x + endWidth;
			return newArea;
		}

		Area VDiv(float beginHeight, float endHeight) {
			ZUI_ASSERT(beginHeight > endHeight);
			Area newArea = *this;
			newArea.min.y = min.y + beginHeight;
			newArea.max.y = min.y + endHeight;
			return newArea;
		}

		// Get a horizontal row from the top, down a specific height
		Area Row(float height, bool clip = false) {
			Area newArea = *this;
			newArea.max.y = newArea.min.y + (clip ? Min(Height(), height) : height);
			return newArea;
		}

		// Area is expanded outwards by a certain amount (or shrunk if negative)
		Area Expand(float amount) {
			Vec expandVec = Vec(Min(amount, Width() / 2), Min(amount, Height() / 2));
			return Area(min - expandVec, max + expandVec);
		}

		// Area is expanded outwards by a certain vec amount (or shrunk if negative)
		Area Expand(Vec amount) {
			Vec expandVec = Vec(Min(amount.x, Width() / 2), Min(amount.y, Height() / 2));
			return Area(min - expandVec, max + expandVec);
		}

		// Width or height is clamped such that the area is a square
		Area SquareShrink(bool center = false) {
			float smallestSize = Min(Width(), Height());

			if (center) {
				auto centerPos = Center();
				auto sizeVec = Vec(smallestSize / 2);
				return Area(centerPos - sizeVec, centerPos + sizeVec);
			} else {
				return Area(min, min + smallestSize);
			}
		}

		Vec PosRel(float widthRatio, float heightRatio) {
			return Vec(min.x + Width() * widthRatio, min.y + Height() * heightRatio);
		}

		Vec TopLeft() { return PosRel(0, 0); }
		Vec TopRight() { return PosRel(1, 0); }
		Vec Left() { return PosRel(0, 0.5f); }
		Vec Right() { return PosRel(1, 0.5f); }
		Vec BottomLeft() { return PosRel(0, 1); }
		Vec BottomRight() { return PosRel(1, 1); }

		Area Move(Vec delta) {
			Area newArea = *this;
			newArea.min += delta;
			newArea.max += delta;
			return newArea;
		}

		Area MoveRel(float xRel, float yRel) {
			Vec moveVec = Vec(xRel * Width(), yRel * Height());
			return Move(moveVec);
		}

		Area MoveTo(Vec pos, bool center = false) {
			Area newArea = *this;

			if (center)
				pos -= Size() / 2;

			newArea.min = pos;
			newArea.max = pos + Size();

			return newArea;
		}
	};
}