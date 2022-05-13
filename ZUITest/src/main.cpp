// The client needs to implement:
// - All ZUI DrawCMD Execute() functions
// - DrawUtil::GetTextSize(FontIndex font, string text)

#include "Framework.h"
#include <ZUI/Draw/DrawUtil/DrawUtil.h>

ZUI::Vec ZUI::DrawUtil::GetTextSize(ZUI::FontIndex fontIndex, std::string text) {
	// TODO: Implement
	return ZUI::Vec();
}

int main() {
	using namespace ZUI;

	StartFrame();
	EndFrame();
}