#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	if (!MainInit()) { return -1; }

	SCENE.Set(new S_Sample());

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() != -1) {

		SCENE.Get().Draw();

		ScreenFlip();
		ClearDrawScreen();

		FRAMEWAIT.Sleep();
	}

	MainEnd();

	return 0;
}

inline bool MainInit() {
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetMainWindowText("GameTemplate");
	SetGraphMode(1280, 720, 32, GetRefreshRate());

	SetDoubleStartValidFlag(TRUE);
	SetAlwaysRunFlag(TRUE);
	SetWaitVSyncFlag(FALSE);
	
	if (DxLib_Init() == -1) { return false; }
	
	SPRITE;

	return true;
}

inline void MainEnd() {
	DxLib_End();
}