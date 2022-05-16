#include "Framework.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <ZUI/Draw/DrawHelper/DrawHelper.h>

SDL_Window* g_SDLWindow = NULL;
SDL_Renderer* g_SDLRenderer = NULL;

TTF_Font* g_Font = NULL;

// Utility for setting g_SDLRenderer's draw color to a ZUI color
void SetSDLDrawCol(ZUI::Color color) {
	SDL_SetRenderDrawColor(g_SDLRenderer, color.r, color.g, color.b, color.a);
}

// Client function implementations for SDL2 and SDL2_ttf
namespace ZUI {
	void CF_SetClipArea(Area clipArea) {
		SDL_Rect clipRect = SDL_Rect(clipArea.min.x, clipArea.min.y, clipArea.Width(), clipArea.Height());
		SDL_RenderSetClipRect(g_SDLRenderer, &clipRect);
	}

	void CF_RenderRect(Area area, Color color, bool filled) {
		SetSDLDrawCol(color);

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
		SetSDLDrawCol(color);

		ZUI_ASSERT(width == 1);// TODO: Other line widths not supported yet

		SDL_RenderDrawLineF(g_SDLRenderer, start.x, start.y, end.x, end.y);
	}

	void CF_RenderText(string text, FontIndex fontIndex, Vec pos, Color color) {
		SetSDLDrawCol(color);

		SDL_Surface* textSurface = TTF_RenderText_Blended(g_Font, text.c_str(), SDL_Color(color.r, color.g, color.b, color.a));
		assert(textSurface);

		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_SDLRenderer, textSurface);

		SDL_FRect posRect = SDL_FRect(pos.x, pos.y, textSurface->w, textSurface->h);
		SDL_RenderCopyF(g_SDLRenderer, textTexture, NULL, &posRect);

		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
	}

	void CF_RenderPolygon(SList<Vec> points, Color color, bool filled) {
		
		if (points.size < 2)
			return; // Don't even bother

		if (filled) {
			SList<SDL_Vertex> vertices = SList<SDL_Vertex>(points.size);

			for (int i = 0; i < vertices.size; i++) {
				Vec pos = points[i];
				vertices[i].position = SDL_FPoint(pos.x, pos.y);
				vertices[i].color = SDL_Color(color.r, color.g, color.b, color.a);
			}

			SDL_RenderGeometry(g_SDLRenderer, NULL, vertices.begin(), vertices.size, NULL, NULL);
		} else {
			SetSDLDrawCol(color);

			// +1 for extra point connecting the start and end
			SList<SDL_FPoint> sdlPoints = SList<SDL_FPoint>(points.size + 1);

			for (int i = 0; i < points.size; i++)
				sdlPoints[i] = SDL_FPoint(points[i].x, points[i].y);

			// Connect start and end
			sdlPoints[sdlPoints.size - 1] = sdlPoints[0];

			SDL_RenderDrawLinesF(g_SDLRenderer, sdlPoints.begin(), sdlPoints.size);
		}
	}

	Vec	CF_GetTextSize(FontIndex font, string text) {
		int w, h;
		TTF_SizeText(g_Font, text.c_str(), &w, &h);
		return Vec(w, h);
	}
}

// Converts a SDL_Event to a ZUI::Event (if there's a corresponding event) and sends it to ZUI
void SendSDLEventToZUI(SDL_Event* sdlEvent) {
	switch (sdlEvent->type) {
	case SDL_MOUSEMOTION:
	{
		ZUI::AddEvent(
			ZUI::Event(
				ZUI::EventType::E_MOUSEMOVE,
				NULL,
				sdlEvent->motion.x, sdlEvent->motion.y
			)
		);
		break;
	}
	}
}

// Draw actual UI via ZUI
void DrawTestUI() {
	ZUI::Vec windowPos = ZUI::Vec(100, 100);
	ZUI::Vec windowSize = ZUI::Vec(400, 800);
	
	ZUI::Area windowArea = ZUI::Area(windowPos, windowPos + windowSize);

	ZUI::StartWindow(windowArea);
	{
		ZUI::Items::Button("Test Button");
	}
	ZUI::EndWindow();
}

int main() {
	using namespace ZUI;

	// Set up a quick SDL window and renderer
	g_SDLWindow = SDL_CreateWindow("ZUI SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_SHOWN);
	g_SDLRenderer = SDL_CreateRenderer(g_SDLWindow, -1, 0);

	// Enable blending with transparency
	SDL_SetRenderDrawBlendMode(g_SDLRenderer, SDL_BLENDMODE_BLEND);

	{
		// Initialize SDL_ttf
		TTF_Init();


		string fontsPath;
#ifdef _WIN32
		char winDirBuf[MAX_PATH];
		GetWindowsDirectoryA(winDirBuf, MAX_PATH);
		fontsPath = winDirBuf;
		fontsPath += "\\fonts\\";
#else
		// TODO: Implement
#endif

		// Load font file
		g_Font = TTF_OpenFont((fontsPath + "verdana.ttf").c_str(), 14);
		assert(g_Font);
	}

	// Main loop
	while (true) {

		// Process SDL events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			// Window closed
			if (event.type == SDL_QUIT) {
				exit(EXIT_SUCCESS);
			} else {
				SendSDLEventToZUI(&event);
			}
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