#include "GameMain_leg.h"
#include "Scenes/SampleScene.h"

bool Game_leg::Init() {

	SetGraphMode(ScreenSize.x, ScreenSize.y, ColorBit);

	DXSystem.MainWindow
		.FullScreenFlag(System.FullScreenFlag)
		.Text(Title.c_str());

	if (!DXSystem
		.AlwaysRunFlag(true)
		.DoubleStartFlag(true)
		.CharCodeFormat(DxLibSystem::CharCodeFormat::UTF8)
		.CharSet(DxLibSystem::CharSet::UTF8)
		.SysCommandOffFlag(true)
		.WaitVSyncFlag(System.VSyncFlag)
		.UseSoundDevice(
			magic_enum::enum_cast<SoundDevice::SoundDeviceType>(Sound.Device.Type.Get()).value(),
			Sound.Device.ExclusiveFlag,
			Sound.Device.BufferSize,
			Sound.Device.SampleRate
		)
		.Init()) {
		MessageBox(NULL, TEXT("Initialize Error, restart again."), TEXT("sorry..."), MB_ICONERROR);
		return false;
	}

	DXSystem.SoundDevice.SetVolume(Sound.Mastar);

	SetDrawScreen(DX_SCREEN_BACK);

	Scene->Regist<SampleScene>();
	
	return true;
}

void Game_leg::Proc() {
	while (ProcessMessage() == 0) {
		Scene->Proc();
		Scene->Draw();
		ScreenFlip();
		ClearDrawScreen();
	}
}

void Game_leg::Draw() {
	// notuse
}

void Game_leg::End() {
	DXSystem.End();
}