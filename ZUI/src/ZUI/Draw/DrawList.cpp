#include "DrawList.h"
#include "../ClientFuncs/ClientFuncs.h"

#include "../ZUI.h"

void ZUI::DrawList::Add(DrawCMD_Base* cmd) {
	cmd->clipArea = g_FrameState.clipAreaStack.top();
	cmds.push_back(cmd);
}

void ZUI::DrawList::ExecuteAll() {
	vector<DrawCMD_Base*> sortedCmds = cmds;

	// Sort in drawing order
	// Using stable_sort to maintain original order for consecutive same-drawlevel cmds
	std::stable_sort(sortedCmds.begin(), sortedCmds.end(), 
		[](DrawCMD_Base* a, DrawCMD_Base* b) {
			return a->drawLevel > b->drawLevel;
		}
	);

	// Execute all
	for (auto cmd : sortedCmds) {
		ZUI::CF_SetClipArea(cmd->clipArea);
		cmd->Execute();
	}
}