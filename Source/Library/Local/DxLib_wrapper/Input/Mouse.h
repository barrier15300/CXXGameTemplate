#pragma once
#include "DeviceBase.h"

class MouseInput : public InputDeviceBase<11> {
	Val2D<int> _MousePos{};
public:

	using InputDeviceBase::InputDeviceBase;

	void Update() {
		::GetMousePoint(&_MousePos.x, &_MousePos.y);
		std::bitset<inputcount> input = ::GetMouseInput();
		for (size_t i = 0; i < inputcount; ++i) {
			States[i].Update(input[i]);
		}
	}

	const Val2D<int> &GetMousePos() const {
		return _MousePos;
	}

	int GetDoubleClickTime() {
		return ::GetDoubleClickTime();
	}

	int GetWheelVol() {
		return ::GetMouseWheelRotVol();
	}
};
