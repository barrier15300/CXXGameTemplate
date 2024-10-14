#include "GameMain.h"
#include "Scenes/SampleScene.h"

bool Game::Init() {

	SetGraphMode(ScreenSize.x, ScreenSize.y, ColorBit);

	if (!DXSystem.
		AlwaysRunFlag(true).
		FullScreenFlag(System.FullScreenFlag).
		WaitVSyncFlag(System.VSyncFlag).
		WindowText(Title.c_str()).
		UseSoundDevice(
			magic_enum::enum_cast<SoundDevice::SoundDeviceType>(Sound.Device.Type.Get()).value(),
			Sound.Device.ExclusiveFlag,
			Sound.Device.BufferSize,
			Sound.Device.SampleRate
			).
		Init()) {
		return false;
	}

	DXSystem.SoundDevice.SetVolume(Sound.Mastar);

	SetDrawScreen(DX_SCREEN_BACK);

	Scene->Regist<SampleScene>();
	
	return true;
}

void Game::Proc() {
	while (ProcessMessage() == 0) {
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
	Scene.reset(nullptr);
	DXSystem.End();
}