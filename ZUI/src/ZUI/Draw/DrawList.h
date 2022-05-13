#pragma once
#include "DrawCMD.h"

namespace ZUI {
	// Storage struct for draw commands
	struct DrawList {
		vector<DrawCMD_Base*> cmds;

		void Add(DrawCMD_Base* cmd) {
			cmds.push_back(cmd);
		}

		void Clear() {
			for (auto drawCmd : cmds)
				delete drawCmd;
			cmds.clear();
		}

		void ExecuteAll();

		~DrawList() {
			Clear();
		}
	};
}