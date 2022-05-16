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

		// Clipping for draw area
		Area clipArea;

		DrawCMD_Base();

		virtual void Execute() = NULL;
	};

	class DrawCMD_Rect : public DrawCMD_Base {
	public:
		Area area;
		Color color;
		float rounding;
		bool filled;

		virtual void Execute();
	};

	class DrawCMD_Line : public DrawCMD_Base {
	public:
		Vec start, end;
		Color color;
		float width;

		virtual void Execute();
	};

	class DrawCMD_Polygon : public DrawCMD_Base {
	public:
		SList<Vec> points;
		Color color;
		bool filled;

		virtual void Execute();
	};

	class DrawCMD_Text : public DrawCMD_Base {
	public:
		string text;
		FontIndex font;
		Vec pos;
		Color color;

		virtual void Execute();
	};
}