#pragma once
#include "../Framework.h"

#include "../Types/Vec.h"
#include "../Types/Area.h"
#include "../Types/Color.h"
#include "../Types/SList.h"

namespace ZUI {
	typedef uint32_t FontIndex;

	class DrawCMD_Base {
	public:
		// Controls the execution order priority of this command
		int drawLevel; 

		DrawCMD_Base(int drawLevel) : drawLevel(drawLevel) {}

		// Client will need to implement (will ZUI_ERROR otherwise)
		virtual void Execute() const {
			ZUI_ERROR(ZUI_FMT("{}::Execute() not implemented!", typeid(this).name()).c_str());
		}
	};

	class DrawCMD_Rect : public DrawCMD_Base {
	public:
		Area area;
		Color color;
		float rounding;
		bool filled;

		DrawCMD_Rect(int drawLevel) : DrawCMD_Base(drawLevel) {}
	};

	class DrawCMD_Line : public DrawCMD_Base {
	public:
		Vec start, end;
		Color color;
		float width;

		DrawCMD_Line(int drawLevel) : DrawCMD_Base(drawLevel) {}
	};

	class DrawCMD_Polygon : public DrawCMD_Base {
	public:
		SList<Vec> points;
		Color color;
		bool filled;

		DrawCMD_Polygon(int drawLevel) : DrawCMD_Base(drawLevel) {}
	};

	class DrawCMD_Text : public DrawCMD_Base {
	public:
		string text;
		FontIndex font;
		Vec pos;
		Color color;

		DrawCMD_Text(int drawLevel) : DrawCMD_Base(drawLevel) {}
	};
}