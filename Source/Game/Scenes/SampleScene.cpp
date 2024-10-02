#include "SampleScene.h"

bool SampleScene::Init() {
	Graph.Load("coursesymbol_oni.png", true);
	return true;
}

void SampleScene::Proc() {
	auto &&pos = this->pos.Get();

	InputState inputs[4] = {
		Input.Keyboard()[(int)Keys::Left],
		Input.Keyboard()[(int)Keys::Up],
		Input.Keyboard()[(int)Keys::Right],
		Input.Keyboard()[(int)Keys::Down]
	};

	for (size_t i = 0; i < 4; ++i) {
		if (inputs[i].Down()) {
			timer[i].Start();
		}
		if (inputs[i].Up()) {
			timer[i].Reset();
		}
	}

	float base = 10, add = 1, mul = 4;
	auto valf = [&](size_t idx) { return (1 / (std::pow(timer[idx].Elapsed<Timer::second>() + add, mul))) * base; };
	if (inputs[0].Press()) {
		pos.x -= valf(0);
	}
	if (inputs[1].Press()) {
		pos.y -= valf(1);
	}
	if (inputs[2].Press()) {
		pos.x += valf(2);
	}
	if (inputs[3].Press()) {
		pos.y += valf(3);
	}

	if (pos.x < 0) {
		pos.x = 0;
	}
	if (pos.x > 1280) {
		pos.x = 1280;
	}
	if (pos.y < 0) {
		pos.y = 0;
	}
	if (pos.y > 720) {
		pos.y = 720;
	}
	
	return;
}

void SampleScene::Draw() {
	auto &pos = this->pos.Get();
	Graph.Draw(pos, 0);
	DrawFormatStringF(pos.x, pos.y, Color3{255, 255, 255}, "[%-.8f, %-.8f]", pos.x, pos.y);
	for (size_t i = 0; i < 4; ++i) {
		DrawFormatString(0, 16 + (16 * i), Color3{255, 255, 255}, "timer[%d]:%lf", i, timer[i].Elapsed());
	}
	return;
}

void SampleScene::End() {
	return;
}
