#include "SampleScene.h"

bool SampleScene::Init() {
	//Don.Create(Donfilepath);
	//Ka.Create(Kafilepath);
	return true;
}

void SampleScene::Proc() {
	auto &&pos = this->pos.Get();

	InputState inputs[4] = {
		Input.Keyboard()[(int)Keys::D],
		Input.Keyboard()[(int)Keys::F],
		Input.Keyboard()[(int)Keys::J],
		Input.Keyboard()[(int)Keys::K]
	};

	//if (inputs[0].Down()) {
	//	Ka.Play();
	//}
	//if (inputs[1].Down()) {
	//	Don.Play();
	//}
	//if (inputs[2].Down()) {
	//	Don.Play();
	//}
	//if (inputs[3].Down()) {
	//	Ka.Play();
	//}
	
	if (Input.Keyboard()[(int)Keys::Left].Down()) {
		timer.Start();
	}
	if (Input.Keyboard()[(int)Keys::Down].Down()) {
		timer.Stop();
	}
	if (Input.Keyboard()[(int)Keys::Right].Down()) {
		timer.Reset();
	}

	return;
}

void SampleScene::Draw() {

	DrawBoxAA(0, 360, timer.Elapsed().Second() * 50, 376, Color3{0,255,0}, TRUE);

	
	return;
}

void SampleScene::End() {
	return;
}
