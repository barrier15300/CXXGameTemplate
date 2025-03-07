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

	ThisT &PauseGraph(				const TCHAR* path)			 { LoadPauseGraph(path); return *this; }
	ThisT &FullScreenFlag(			bool flag)					 { ChangeWindowMode(!flag); return *this; }
	ThisT &Text(					const TCHAR *str)			 { SetMainWindowText(str); return *this; }
	ThisT &Style(					WindowStyles mode)			 { SetWindowStyleMode((int)mode); return *this; }
	ThisT &Icon(					int id)						 { SetWindowIconID(id); return *this; }
	ThisT &SizeChangeFlag(			bool flag)					 { SetWindowSizeChangeEnableFlag(flag); return *this; }
	ThisT &ExtendRate(				const Val2D<double> &size)	 { SetWindowSizeExtendRate(size.x, size.y); return *this; }
	ThisT &Size(					const Val2D<int> &size)		 { SetWindowSize(size.x, size.y); return *this; }
	ThisT &MaxSize(					const Val2D<int> &size)		 { SetWindowMaxSize(size.x, size.y); return *this; }
	ThisT &MinSize(					const Val2D<int> &size)		 { SetWindowMinSize(size.x, size.y); return *this; }
	ThisT &Pos(						const Val2D<int> &pos)		 { SetWindowPosition(pos.x, pos.y); return *this; }
	ThisT &DispFlag(				bool flag)					 { SetWindowVisibleFlag(flag); return *this; }
	ThisT &MinimizeFlag(			bool flag)					 { SetWindowMinimizeFlag(flag); return *this; }
	ThisT &HookWndproc(				WNDPROC wndproc)			 { SetHookWinProc(wndproc); return *this; }
	ThisT &BackgroundColor(			Color3 color, int alpha = 0) { SetBackgroundColor(color.r, color.g, color.b, alpha); return *this; }
	ThisT &BackgroundColor(			Color4 color)				 { SetBackgroundColor(color.r, color.g, color.b, color.a); return *this; }
	ThisT &BackBufferTransFlag(		bool flag)					 { SetUseBackBufferTransColorFlag(flag); return *this; }
	ThisT &UpdateLayerdWindowFlag(	bool flag)					 { SetUseUpdateLayerdWindowFlag(flag); return *this; }
};

class ChildWindow {
public:



};