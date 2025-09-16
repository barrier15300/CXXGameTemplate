#pragma once
#include "Include.hpp"
#include "Game/GameMain_leg.h"
#include "Game/GameMain.h"

class Main {
public:

	Main() { Init(); }
	~Main() { End(); }

	void Init();
	void End();

	int _InitCheckProc() {
		if (!InitSuccessFlag) {
			End();
			return 1;
		}
		return Proc();
	}

	int Proc();

	Game_leg GameMain;
	SceneManager RootManager;

	bool InitSuccessFlag = false;
};