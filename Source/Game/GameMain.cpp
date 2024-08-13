#include "GameMain.h"
#include "Scenes/SampleScene.h"

bool Game::Init() {

	if (!System.
		AlwaysRunFlag(true).
		FullScreenFlag(Config.Get("system/windowmode", false)).
		WaitVSyncFlag(Config.Get("system/waitvsync", true)).
		WindowText(Name.c_str()).
		UseSoundDevice(
			magic_enum::enum_cast<SoundDevice::SoundDeviceType>(Config.Get<std::string>("sound/device/type", "WASAPI")).value(),
			Config.Get("sound/device/is_exclusive", false),
			Config.Get<int64_t>("sound/device/bufsize", 480),
			Config.Get<int64_t>("sound/device/samplerate", 192000)
			).
		Init()) {
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	Scene->Regist("Sample", new SampleScene());
	
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
	System.End();
}