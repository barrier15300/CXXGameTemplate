#pragma once
#include "DxLib.h"
#include "SoundDevice.h"

class DxLibSystem final {
public:

	using ThisT = DxLibSystem;

	bool Init() { return DxLib_Init() != -1; };
	void End() { if (DxLib_IsInit() == TRUE) { DxLib_End(); } }

	enum class WindowStyles : int {
		Default,
		NonTaskBar,
		NonTaskBer_Border,
		NonBorder,
		None,
		NonMinimize,
		Toolbar,
		MaximumButton_Normal,
		MaximumButton_Maximum,
		Non3DBorder,
		MaximumButton_Non3DBorder,
		NonClose
	};

	ThisT &AlwaysRunFlag(				bool flag)						{ SetAlwaysRunFlag(flag); return *this; }
	ThisT &CharSet(						int mode)						{ SetUseCharSet(mode); return *this; }
	ThisT &SysCommandOffFlag(			bool flag)						{ SetSysCommandOffFlag(flag); return *this; }
	ThisT &DoubleStartFlag(				bool flag)						{ SetDoubleStartValidFlag(flag); return *this; }
	ThisT &WaitVSyncFlag(				bool flag)						{ SetWaitVSyncFlag(flag); return *this; }
	ThisT &UseSoundDevice(SoundDevice::SoundDeviceType type, bool exclusive, int bufsize, int samplerate) {
		SoundDevice.SetDevice(type, exclusive, bufsize, samplerate); return *this;
	}

	SoundDevice SoundDevice{};
};