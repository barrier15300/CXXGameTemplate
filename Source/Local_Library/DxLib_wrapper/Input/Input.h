#pragma once
#include "Keyboard.h"
#include "Mouse.h"

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