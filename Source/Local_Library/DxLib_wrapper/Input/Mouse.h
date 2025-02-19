#pragma once
#include "DeviceBase.h"

class __mouseInput_sc : public __baseInputDevice<> {
	Val2D<int> _MousePos{};
public:

	using __baseInputDevice::__baseInputDevice;

	void Update() {
		GetMousePoint(&_MousePos.x, &_MousePos.y);
	}

	const Val2D<int> &GetMousePos() const {
		return _MousePos;
	}

	int GetDoubleClickTime() {
		return ::GetDoubleClickTime();
	}
};
