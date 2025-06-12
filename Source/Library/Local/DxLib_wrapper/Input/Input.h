#pragma once
#include "Keyboard.h"
#include "Mouse.h"

class InputDevices {

public:

	void Update() {
		Keyboard.Update();
		Mouse.Update();
	}

	KeyboardInput Keyboard{};
	MouseInput Mouse{};
};