#pragma once

/// <summary>
/// InputState
/// 
/// </summary>
struct InputState {

	enum class State : byte;

	bool Down() const { return m_bitop & static_cast<byte>(State::Down); }
	bool Press() const { return m_bitop & static_cast<byte>(State::Press) || Down(); }
	bool Up() const { return m_bitop & static_cast<byte>(State::Up); }
	bool Release() const { return m_bitop & static_cast<byte>(State::Release) || Up(); }

	State GetState() const {
		return m_State;
	}

	std::tuple<uint32_t, uint32_t, uint32_t> GetStates() const {
		return {ctrl_press, ctrl_hold, ctrl_release};
	}

	// press = true -> pressing, press = false -> release
	void Update(bool press) {
		m_bitop = 
			3 << (2 * !press) &
			(((((m_bitop - 3) >> 1) & 1) + 1) |
			((((6 >> m_bitop) & 1) << 2) | ((m_bitop + 4) & 8)));

	#pragma region Original
		/*
		if (press) {
			switch (m_State) {
				case State::Press:
					return;
				case State::None:
					m_State = State::Down;
					break;
				case State::Down:
					m_State = State::Press;
					break;
				case State::Up:
					m_State = State::Down;
					break;
				case State::Release:
					m_State = State::Down;
					break;
			}
		}
		else {
			switch (m_State) {
				case State::Release:
					return;
				case State::Press:
					m_State = State::Up;
					break;
				case State::Down:
					m_State = State::Up;
					break;
				case State::Up:
					m_State = State::Release;
					break;
			}
		}
		*/
	#pragma endregion
	}

	void _Update(uint32_t buttons) {
		uint32_t ctrl_cache = ctrl_press | ctrl_hold;

		ctrl_press = buttons & ~ctrl_cache;
		ctrl_release = ~buttons & ctrl_cache;
		ctrl_hold = ctrl_cache ^ ctrl_release;
	}

	enum class State : byte {
		None	= 0,
		Down	= 0b00000001,
		Press	= 0b00000010,
		Up		= 0b00000100,
		Release	= 0b00001000
	};

private:

	uint32_t ctrl_press = 0, ctrl_hold = 0, ctrl_release = 0;

	union {
		State m_State = State::None;
		byte m_bitop;
	};
};