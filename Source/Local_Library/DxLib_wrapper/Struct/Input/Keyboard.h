#pragma once
#include "DeviceBase.h"
#include "Keys.h"

inline byte __gotkeyinput[256]{};
inline LRESULT CALLBACK KeyInputMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_KEYDOWN:
			__gotkeyinput[wParam] = 1;
			break;
		case WM_KEYUP:
			__gotkeyinput[wParam] = 0;
			break;
	}
	return 0;
}

class __keyboardInput_sc : public __baseInputDevice<256> {

	byte *rawInput = __gotkeyinput;

public:

	__keyboardInput_sc() : __baseInputDevice() {
		SetHookWinProc(KeyInputMessage);
	}

	InputState operator[](size_t idx) const {
		return __baseInputDevice::operator[](idx);
	}

	InputState operator[](Keys key) const {
		return __baseInputDevice::operator[](static_cast<unsigned int>(key));
	}

	void Update() {
		for (auto &&item : States) {
			item.Update(rawInput[(size_t)(&item - States)]);
		}
	}
};
