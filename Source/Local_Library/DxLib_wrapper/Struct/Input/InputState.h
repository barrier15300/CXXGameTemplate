#pragma once

/// <summary>
/// InputState
/// 
/// </summary>
struct InputState {

	bool Down() const { return static_cast<byte>(State) & static_cast<byte>(_State::Down); }
	bool Press() const { return static_cast<byte>(State) & static_cast<byte>(_State::Press) || Down(); }
	bool Up() const { return static_cast<byte>(State) & static_cast<byte>(_State::Up); }
	bool Release() const { return static_cast<byte>(State) & static_cast<byte>(_State::Release) || Up(); }

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
		None = 0,
		Down = 0b00000001,
		Press = 0b00000010,
		Up = 0b00000100,
		Release = 0b00001000
	} State = _State::None;
};