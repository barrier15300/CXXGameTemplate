#pragma once
#include "DxLib.h"
#include "SoundDevice.h"
#include "Struct.h"

class DxLibSystem final {
public:

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

	DxLibSystem &AlwaysRunFlag(				bool flag)						{ SetAlwaysRunFlag(flag); return *this; }
	DxLibSystem &FullScreenFlag(			bool flag)						{ ChangeWindowMode(!flag); return *this; }
	DxLibSystem &CharSet(					int mode)						{ SetUseCharSet(mode); return *this; }
	DxLibSystem &PauseGraph(				const TCHAR* path)				{ LoadPauseGraph(path); return *this; }
	DxLibSystem &WindowText(				const TCHAR *str)				{ SetMainWindowText(str); return *this; }
	DxLibSystem &WindowStyle(				WindowStyles mode)				{ SetWindowStyleMode((int)mode); return *this; }
	DxLibSystem &WindowIcon(				int id)							{ SetWindowIconID(id); return *this; }
	DxLibSystem &WindowSizeChangeFlag(		bool flag)						{ SetWindowSizeChangeEnableFlag(flag); return *this; }
	DxLibSystem &WindowExtendRate(			const Size2D<double> &size)		{ SetWindowSizeExtendRate(size.width, size.height); return *this; }
	DxLibSystem &WindowSize(				const Size2D<int> &size)		{ SetWindowSize(size.width, size.height); return *this; }
	DxLibSystem &WindowMaxSize(				const Size2D<int> &size)		{ SetWindowMaxSize(size.width, size.height); return *this; }
	DxLibSystem &WindowMinSize(				const Size2D<int> &size)		{ SetWindowMinSize(size.width, size.height); return *this; }
	DxLibSystem &WindowPos(					const Pos2D<int> &pos)			{ SetWindowPosition(pos.x, pos.y); return *this; }
	DxLibSystem &SysCommandOffFlag(			bool flag)						{ SetSysCommandOffFlag(flag); return *this; }
	DxLibSystem &HookWndproc(				WNDPROC wndproc)				{ SetHookWinProc(wndproc); return *this; }
	DxLibSystem &DoubleStartFlag(			bool flag)						{ SetDoubleStartValidFlag(flag); return *this; }
	DxLibSystem &WindowDispFlag(			bool flag)						{ SetWindowVisibleFlag(flag); return *this; }
	DxLibSystem &WindowMinimizeFlag(		bool flag)						{ SetWindowMinimizeFlag(flag); return *this; }
	DxLibSystem &BackgroundColor(			Color3 color, int alpha = 0)	{ SetBackgroundColor(color.r, color.g, color.b, alpha); return *this; }
	DxLibSystem &WaitVSyncFlag(				bool flag)						{ SetWaitVSyncFlag(flag); return *this; }
	DxLibSystem &UseSoundDevice(SoundDevice::SoundDeviceType type, bool exclusive, int bufsize, int samplerate) {
		SoundDevice.SetDevice(type, exclusive, bufsize, samplerate); return *this;
	}

	SoundDevice SoundDevice{};
};