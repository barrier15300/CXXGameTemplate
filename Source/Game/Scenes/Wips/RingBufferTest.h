#pragma once
#include "Include.hpp"

class RingBufferTest : public IObjectBase {
public:
	virtual bool Init() override;
	virtual void Proc() override;
	virtual void Draw() override;
	virtual void End() override;

	
	ring::array<int, 8> buffer;
	ring::array<int, 8> buffer2;
	int c = 0;

};

bool RingBufferTest::Init() {

	auto it = buffer.begin() - buffer2.end();

	return true;
}

void RingBufferTest::Proc() {

	if (Input.Keyboard[Keys::A].Down()) {
		buffer.write_back(++c);
	}
	if (Input.Keyboard[Keys::Z].Down()) {
		buffer.write_back(--c);
	}

	if (Input.Keyboard[Keys::C].Down()) {
		buffer.clear_front();
	}

	return;
}

void RingBufferTest::Draw() {

	for (size_t i{}; auto& elem : buffer) {
		DrawFormatString(
			0,
			16 + i * 16,
			Color3{ 255,255,255 },
			"%d, %p: %d",
			i,
			&elem,
			elem
		);
		i++;
	}

	return;
}

void RingBufferTest::End() {
	return;
}
