#pragma once
#include "../Helper/DXHandle.h"
#include "../Value/Value.h"

class MainWindowSetting {
public:

	using ThisT = MainWindowSetting;

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

	//SetUseBackBufferTransColorFlag(true);
	//SetUseUpdateLayerdWindowFlag(true);

	ThisT &PauseGraph(				const TCHAR* path)				{ LoadPauseGraph(path); return *this; }
	ThisT &FullScreenFlag(			bool flag)						{ ChangeWindowMode(!flag); return *this; }
	ThisT &WindowText(				const TCHAR *str)				{ SetMainWindowText(str); return *this; }
	ThisT &WindowStyle(				WindowStyles mode)				{ SetWindowStyleMode((int)mode); return *this; }
	ThisT &WindowIcon(				int id)							{ SetWindowIconID(id); return *this; }
	ThisT &WindowSizeChangeFlag(	bool flag)						{ SetWindowSizeChangeEnableFlag(flag); return *this; }
	ThisT &WindowExtendRate(		const Val2D<double> &size)		{ SetWindowSizeExtendRate(size.x, size.y); return *this; }
	ThisT &WindowSize(				const Val2D<int> &size)			{ SetWindowSize(size.x, size.y); return *this; }
	ThisT &WindowMaxSize(			const Val2D<int> &size)			{ SetWindowMaxSize(size.x, size.y); return *this; }
	ThisT &WindowMinSize(			const Val2D<int> &size)			{ SetWindowMinSize(size.x, size.y); return *this; }
	ThisT &WindowPos(				const Val2D<int> &pos)			{ SetWindowPosition(pos.x, pos.y); return *this; }
	ThisT &WindowDispFlag(			bool flag)						{ SetWindowVisibleFlag(flag); return *this; }
	ThisT &WindowMinimizeFlag(		bool flag)						{ SetWindowMinimizeFlag(flag); return *this; }
	ThisT &HookWndproc(				WNDPROC wndproc)				{ SetHookWinProc(wndproc); return *this; }
	ThisT &BackgroundColor(			Color3 color, int alpha = 0)	{ SetBackgroundColor(color.r, color.g, color.b, alpha); return *this; }
	ThisT &BackgroundColor(			Color4 color)					{ SetBackgroundColor(color.r, color.g, color.b, color.a); return *this; }

};

class ChildWindow {
public:



};