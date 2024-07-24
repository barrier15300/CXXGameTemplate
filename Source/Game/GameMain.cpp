#include "GameMain.h"
#include "Scenes/SampleScene.h"

bool Game::Init() {

	ChangeWindowMode(Config.Get("system/windowmode", true));
	SetWaitVSyncFlag(Config.Get("system/waitvsync", true));
	SetMainWindowText(Name.c_str());

	if (DxLib_Init() == -1) { return false; }

	SetDrawScreen(DX_SCREEN_BACK);

	Scene->Regist("Sample", new SampleScene());
	
	return true;
}

void Game::Proc() {
	while (ProcessMessage() != -1) {
		Scene->Proc();
		Scene->Draw();
		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", (int)GetFPS());
		ScreenFlip();
		ClearDrawScreen();
	}
}

void Game::Draw() {
	// notuse
}

void Game::End() {
	DxLib_End();
}