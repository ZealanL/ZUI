#pragma once
#include "../Framework.h"

#include "../Types/Vec.h"
#include "../Types/Area.h"
#include "../Types/Color.h"
#include "../Types/SList.h"

namespace ZUI {
	class DrawCMD_Base {
	public:
		// Controls the execution order priority of this command
		int drawLevel; 

		DrawCMD_Base(int drawLevel) : drawLevel(drawLevel) {}

		virtual void Execute() = NULL;
	};

	class DrawCMD_Rect : public DrawCMD_Base {
	public:
		Area area;
		Color color;
		float rounding;
		bool filled;

		DrawCMD_Rect(int drawLevel) : DrawCMD_Base(drawLevel) {}
		virtual void Execute();
	};

	class DrawCMD_Line : public DrawCMD_Base {
	public:
		Vec start, end;
		Color color;
		float width;

		DrawCMD_Line(int drawLevel) : DrawCMD_Base(drawLevel) {}
		virtual void Execute();
	};

	class DrawCMD_Polygon : public DrawCMD_Base {
	public:
		SList<Vec> points;
		Color color;
		bool filled;

		DrawCMD_Polygon(int drawLevel) : DrawCMD_Base(drawLevel) {}
		virtual void Execute();
	};

	class DrawCMD_Text : public DrawCMD_Base {
	public:
		string text;
		FontIndex font;
		Vec pos;
		Color color;

		DrawCMD_Text(int drawLevel) : DrawCMD_Base(drawLevel) {}
		virtual void Execute();
	};
}