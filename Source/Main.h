#pragma once
#include "Include.hpp"
#include "Game/GameMain.h"

class Main {
public:

	Main() { Init(); }
	~Main() { End(); }

	void Init();
	void End();

	int _InitCheckProc() {
		if (!InitSuccessFlag) {
			return -1;
		}
		return Proc();
	}

	int Proc();

	Game GameMain;

	bool InitSuccessFlag = false;
};