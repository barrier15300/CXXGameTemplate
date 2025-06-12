#pragma once
#include "DxLib.h"
#include "InputState.h"
#include <exception>

class __InputDeviceLock {
public:

	void Lock() {
		m_inputlock = true;
	}

	void Unlock() {
		m_inputlock = false;
	}

protected:
	bool m_inputlock = false;
};

template<size_t _inputcount = 1>
class InputDeviceBase : public __InputDeviceLock {
protected:
	static constexpr inline size_t inputcount = _inputcount;
	InputState States[inputcount]{};

public:

	InputDeviceBase() {}

	virtual void Update() = 0;

	InputState operator[](size_t idx) const {
		return m_inputlock ? InputState{} : States[idx];
	}

	InputState at(size_t idx) const {
		if (idx >= inputcount) {
			throw std::exception("Out of Range!!!");
		}
		return (*this)[idx];
	}
};

