#pragma once
#include "../Helper/DXHandle.h"
#include "SoundDevice.h"
#include "Window.h"

class DxLibSystem final {
public:

	using ThisT = DxLibSystem;

	bool Init() { Setting(); return DxLib_Init() != -1; };
	void End() { if (DxLib_IsInit() == TRUE) { DxLib_End(); } }

	void Setting() {
		SetUseDXNetWorkProtocol(false);
	}

	enum class CharSet : int { 
		Default = DX_CHARSET_DEFAULT,
		ShiftJIS = DX_CHARSET_SHFTJIS,
		Hangeul = DX_CHARSET_HANGEUL,
		Big5 = DX_CHARSET_BIG5,
		GB2312 = DX_CHARSET_GB2312,
		Windows1252 = DX_CHARSET_WINDOWS_1252,
		ISO_IEC_8859_15 = DX_CHARSET_ISO_IEC_8859_15,
		UTF8 = DX_CHARSET_UTF8
	};

	enum class CharCodeFormat: int {
		ShiftJIS = DX_CHARCODEFORMAT_SHIFTJIS,
		GB2312 = DX_CHARCODEFORMAT_GB2312,
		UHC = DX_CHARCODEFORMAT_UHC,
		Big5 = DX_CHARCODEFORMAT_BIG5,
		UTF16LE = DX_CHARCODEFORMAT_UTF16LE,
		UTF16BE = DX_CHARCODEFORMAT_UTF16BE,
		Windows1252 = DX_CHARCODEFORMAT_WINDOWS_1252,
		ISO_IEC_8859_15 = DX_CHARCODEFORMAT_ISO_IEC_8859_15,
		UTF8 = DX_CHARCODEFORMAT_UTF8,
		ASCII = DX_CHARCODEFORMAT_ASCII,
		UTF32LE = DX_CHARCODEFORMAT_UTF32LE,
		UTF32BE = DX_CHARCODEFORMAT_UTF32BE,
	};

	ThisT &AlwaysRunFlag(		bool flag)				{ SetAlwaysRunFlag(flag); return *this; }
	ThisT &CharSet(				CharSet mode)			{ SetUseCharSet((int)mode); return *this; }
	ThisT &CharCodeFormat(		CharCodeFormat format)	{ SetUseCharCodeFormat((int)format); return *this; }
	ThisT &SysCommandOffFlag(	bool flag)				{ SetSysCommandOffFlag(flag); return *this; }
	ThisT &DoubleStartFlag(		bool flag)				{ SetDoubleStartValidFlag(flag); return *this; }
	ThisT &WaitVSyncFlag(		bool flag)				{ SetWaitVSyncFlag(flag); return *this; }
	ThisT &UseSoundDevice(SoundDevice::SoundDeviceType type, bool exclusive, int bufsize, int samplerate) {
		SoundDevice.SetDevice(type, exclusive, bufsize, samplerate); return *this;
	}

	SoundDevice SoundDevice;
	MainWindowSetting MainWindow;
};

class WinMainArgs {
public:
	WinMainArgs(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
		m_Instance = hInstance;
		m_CommandLineArgs = split(lpCmdLine, ' ');
	};

	static const HINSTANCE Instance() {
		return m_Instance;
	}

	static const std::vector<std::string_view> &CommandLineArgs() {
		return m_CommandLineArgs;
	}

private:

	static inline HINSTANCE m_Instance = nullptr;
	static inline std::vector<std::string_view> m_CommandLineArgs{};

};