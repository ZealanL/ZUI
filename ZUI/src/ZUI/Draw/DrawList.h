#pragma once
#include "DrawCMD.h"

namespace ZUI {
	// Storage struct for draw commands
	struct DrawList {
		vector<DrawCMD_Base*> cmds;

		// Template type must be a DrawCMD subclass
		template<class T>
		std::enable_if<std::is_base_of<DrawCMD_Base, void>::value, void> Add(T cmd) {
			cmds.push_back(new T(cmd));
		}

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