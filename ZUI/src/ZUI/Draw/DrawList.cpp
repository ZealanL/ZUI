#include "DrawList.h"

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
	for (auto cmd : sortedCmds)
		cmd->Execute();
}