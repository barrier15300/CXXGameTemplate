#pragma once

/// <summary>
/// InputState
/// 
/// </summary>
struct InputState {

	enum class State : byte;

	constexpr bool Down() const { return m_State == State::Down; }
	constexpr bool Press() const { return m_State == State::Press || Down(); }
	constexpr bool Up() const { return m_State == State::Up; }
	constexpr bool Release() const { return m_State == State::Release || Up(); }

	State GetState() const {
		return m_State;
	}

	// press = true -> pressing, press = false -> release
	void Update(bool press) {
		m_bitop = 
			3 << (2 * !press) &
			(((((m_bitop - 3) >> 1) & 1) + 1) |
			((((6 >> m_bitop) & 1) << 2) | ((m_bitop + 4) & 8)));

	#pragma region ____Original
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
	
	enum class State : byte {
		None	= 0,
		Down	= 0b00000001,
		Press	= 0b00000010,
		Up		= 0b00000100,
		Release	= 0b00001000
	};

private:
	union {
		State m_State = State::None;
		byte m_bitop;
	};
};