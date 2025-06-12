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

class KeyboardInput : public InputDeviceBase<256> {

	byte *rawInput = __gotkeyinput;

public:

	KeyboardInput() : InputDeviceBase() {
		SetHookWinProc(KeyInputMessage);
	}

	InputState operator[](size_t idx) const {
		return InputDeviceBase::operator[](idx);
	}

	InputState operator[](Keys key) const {
		return InputDeviceBase::operator[](static_cast<unsigned int>(key));
	}

	void Update() {
		for (size_t i = 0; auto&& item : States) {
			item.Update(rawInput[i]);
			++i;
		}
	}
};
