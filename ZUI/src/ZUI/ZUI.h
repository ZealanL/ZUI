#include "Framework.h"
#include "Draw/DrawList.h"
#include "Event/Event.h"

namespace ZUI {
	DrawList& GetDrawList();
	EventQueue& GetEventQueue();

	void AddEvent(Event event);

	void StartFrame();
	void EndFrame();

	void SetCurrentFontIndex(FontIndex newIndex);
	FontIndex GetCurrentFontIndex();
}