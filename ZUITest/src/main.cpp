#include "Framework.h"

#include <ZUI/Draw/DrawHelper/DrawHelper.h>

SDL_Window* g_SDLWindow = NULL;
SDL_Renderer* g_SDLRenderer = NULL;

// Utility for setting g_SDLRenderer's draw color to a ZUI color
void SetDrawCol(ZUI::Color color) {
	SDL_SetRenderDrawColor(g_SDLRenderer, color.r, color.b, color.g, color.a);
}

// Client function implementations for SDL2 and SDL2_ttf
namespace ZUI {
	void CF_RenderRect(Area area, Color color, bool filled) {
		SetDrawCol(color);

		SDL_FRect rect = SDL_FRect {
			area.min.x,
			area.min.y,
			area.max.x - area.min.x,
			area.max.y - area.min.y
		};

		if (filled) {
			SDL_RenderFillRectF(g_SDLRenderer, &rect);
		} else {
			SDL_RenderDrawRectF(g_SDLRenderer, &rect);
		}
	}

	void CF_RenderLine(Vec start, Vec end, Color color, float width) {
		SetDrawCol(color);

		ZUI_ASSERT(width == 1);// TODO: Other line widths not supported yet

		SDL_RenderDrawLineF(g_SDLRenderer, start.x, start.y, end.x, end.y);
	}

	void CF_RenderText(string text, FontIndex fontIndex, Vec pos, Color color) {
		SetDrawCol(color);

		// TODO: Implement
	}

	void CF_RenderPolygon(SList<Vec> points, Color color, bool filled) {
		SetDrawCol(color);

		// TODO: Implement
	}

	Vec	CF_GetTextSize(FontIndex font, string text) {
		// TODO: Implement
		return Vec();
	}
}

// Draw actual UI via ZUI
void DrawTestUI() {
	ZUI::DrawHelper::FillRect(0, 100, ZUI_COL_WHITE);
}

int main() {
	using namespace ZUI;

	// Set up a quick SDL window and renderer
	g_SDLWindow = SDL_CreateWindow("ZUI SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	g_SDLRenderer = SDL_CreateRenderer(g_SDLWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	// Main loop
	while (true) {

		// Process SDL events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			// Window closed
			if (event.type == SDL_QUIT)
				exit(EXIT_SUCCESS);
		}

		// Clear with black background at the start of each frame
		SDL_SetRenderDrawColor(g_SDLRenderer, 0, 0, 0, 255);
		SDL_RenderClear(g_SDLRenderer);

		// Draw a ZUI frame
		{
			StartFrame();
			DrawTestUI();
			EndFrame();
		}

		// Update SDL render
		SDL_RenderPresent(g_SDLRenderer);
	}
	
	return EXIT_SUCCESS;
}