#include "Framework.h"
#include "Draw/DrawList.h"
#include "Event/Event.h"

#include "ClientFuncs/ClientFuncs.h"
#include "State/FrameState.h"

namespace ZUI {

	// Global variables
	extern FrameState g_FrameState;

	DrawList& GetDrawList();
	EventQueue& GetEventQueue();

	void AddEvent(Event event);

	void StartFrame();
	void EndFrame();

	void SetCurrentFontIndex(FontIndex newIndex);
	FontIndex GetCurrentFontIndex();

}