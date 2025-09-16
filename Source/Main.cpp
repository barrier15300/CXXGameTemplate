#include "Main.h"

void Main::Init() {
	RootManager.Regist<Game>();
	InitSuccessFlag = true;
}

void Main::End() {
	;
}

int Main::Proc() {
	RootManager.Clock();
	return 0;
}
