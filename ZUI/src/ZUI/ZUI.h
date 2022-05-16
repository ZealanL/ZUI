#include "Framework.h"
#include "Draw/DrawList.h"
#include "Event/Event.h"

#include "ClientFuncs/ClientFuncs.h"
#include "State/FrameState.h"
#include "Config/Config.h"

#include "UI/UI.h"
#include "UI/Items/Items.h"

namespace ZUI {

	// Global variables
	extern FrameState g_FrameState;
	extern Config g_Config;

	DrawList& GetDrawList();

	EventQueue& GetEventQueue();
	void AddEvent(Event event);

	void StartFrame();
	void EndFrame();

	void SetCurrentFontIndex(FontIndex newIndex);
	FontIndex GetCurrentFontIndex();
}