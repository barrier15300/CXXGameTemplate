#include "Main.h"

void Main::Init() {
	InitSuccessFlag = GameMain.Init();
}

void Main::End() {
	GameMain.End();
}

int Main::Proc() {
	GameMain.Proc();
	return 0;
}
