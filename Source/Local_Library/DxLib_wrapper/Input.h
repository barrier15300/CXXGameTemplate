#pragma once
#include "DxLib.h"
#include "Keys.h"
#include "Struct.h"
#include "../special.h"

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

struct InputState {

	bool Down() const { return static_cast<byte>(State) & static_cast<byte>(_State::Down); }
	bool Press() const { return static_cast<byte>(State) & static_cast<byte>(_State::Press); }
	bool Up() const { return static_cast<byte>(State) & static_cast<byte>(_State::Up); }
	bool Release() const { return static_cast<byte>(State) & static_cast<byte>(_State::Release); }

	void Update(bool press) {
		if (press) {
			switch (State) {
				case _State::Press:
					return;
				case _State::None:
					State = _State::Down;
					break;
				case _State::Down:
					State = _State::Press;
					break;
				case _State::Up:
					State = _State::Down;
					break;
				case _State::Release:
					State = _State::Down;
					break;
			}
		}
		else {
			switch (State) {
				case _State::Release:
					return;
				case _State::Press:
					State = _State::Up;
					break;
				case _State::Down:
					State = _State::Up;
					break;
				case _State::Up:
					State = _State::Release;
					break;
			}
		}
	}

private:

	enum class _State : byte {
		None    = 0,
		Down    = 0b00000001,
		Press   = 0b00000010,
		Up      = 0b00000100,
		Release = 0b00001000
	} State = _State::None;
};

template<size_t inputcount = 1>
class __baseInputDevice {
	static inline bool m_inputlock = false;
protected:
	InputState States[inputcount]{};

public:

	__baseInputDevice() {}

	virtual void Update() = 0;

	InputState operator[](size_t idx) const {
		return m_inputlock ? InputState{} : States[idx];
	}

	InputState at(size_t idx) const {
		if (!(idx >= 0 && idx < inputcount)) {
			throw std::exception("Out of Range!!!");
		}
		return (*this)[idx];
	}

	static void SetInputLock(bool flag) {
		m_inputlock = flag;
	}
};

class __keyboardInput_sc : public __baseInputDevice<256> {
	
	byte *rawInput = __gotkeyinput;

public:

	__keyboardInput_sc() : __baseInputDevice() {
		SetHookWinProc(KeyInputMessage);
	}

	void Update() {
		for (auto&& item : States) {
			item.Update(rawInput[(size_t)(&item - States)]);
		}
	}

	
};

class __mouseInput_sc : public __baseInputDevice<> {
	Pos2D<int> _MousePos{};
public:

	using __baseInputDevice::__baseInputDevice;

	void Update() {
		GetMousePoint(&_MousePos.x, &_MousePos.y);
	}

	const Pos2D<int> &GetMousePos() {
		return _MousePos;
	}
};

class InputDevices {

public:

	void Update() {
		_Keyboard.Update();
		_Mouse.Update();
	}

	void Lock() {
		__baseInputDevice<>::SetInputLock(true);
	}

	void UnLock() {
		__baseInputDevice<>::SetInputLock(false);
	}

	const __keyboardInput_sc &Keyboard() {
		return _Keyboard;
	}
	const __mouseInput_sc &Mouse() {
		return _Mouse;
	}

private:

	inline static __keyboardInput_sc _Keyboard{};
	inline static __mouseInput_sc _Mouse{};
};