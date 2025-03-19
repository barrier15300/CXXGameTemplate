#pragma once
#include "DxLib.h"
#include "InputState.h"
#include <exception>

template<size_t _inputcount = 1>
class __baseInputDevice {
	static inline bool m_inputlock = false;
protected:
	static constexpr inline size_t inputcount = _inputcount;
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

