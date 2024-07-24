#pragma once
#include "DxLib.h"

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
	bool* m_inputlock = nullptr;
protected:
	InputState States[inputcount];

public:

	__baseInputDevice() {}
	__baseInputDevice(bool* inputlock) { m_inputlock = inputlock; }

	virtual void Update() = 0;

	InputState operator[](size_t idx) const {
		return *m_inputlock ? InputState{} : States[idx];
	}

	InputState at(size_t idx) const {
		if (!(idx >= 0 && idx < inputcount)) {
			throw std::exception("Out of Range!!!");
		}
		return (*this)[idx];
	}
};

class __keyboardInput_sc : public __baseInputDevice<256> {
	char rawInput[256];

public:

	using __baseInputDevice::__baseInputDevice;

	void Update() {
		GetHitKeyStateAll(rawInput);
		for (auto&& item : States) {
			item.Update(rawInput[(size_t)(&item - States)]);
		}
	}
};

class __mouseInput_sc : public __baseInputDevice<8> {
	int rawInput = 0;
public:

	using __baseInputDevice::__baseInputDevice;

	void Update() {
		rawInput = GetMouseInput();
		for (size_t i = 0; i < 8; ++i) {
			int shift = (1 << i);
			States[i].Update(rawInput & shift);
		}
	}
};

class InputDevices {
public:

	void Update() {
		KeyBoard.Update();
		Mouse.Update();
	}

	void Lock() {
		InputLock = true;
	}

	void UnLock() {
		InputLock = false;
	}

private:
	inline static bool InputLock = false;
	inline static __keyboardInput_sc KeyBoard = __keyboardInput_sc(&InputLock);
	inline static __mouseInput_sc Mouse = __mouseInput_sc(&InputLock);
};