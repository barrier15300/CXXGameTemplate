#include "SampleScene.h"

bool SampleScene::Init() {
	//Don.Create(Donfilepath);
	//Ka.Create(Kafilepath);
	return true;
}

void SampleScene::Proc() {
	auto &&pos = this->pos.Get();

	InputState inputs[4] = {
		Input.Keyboard()[Keys::D],
		Input.Keyboard()[Keys::F],
		Input.Keyboard()[Keys::J],
		Input.Keyboard()[Keys::K]
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

	if (timer.Elapsed().Second() > 3) {
		timer.Reset();
	}
	if (Input.Keyboard()[Keys::Left].Down()) {
		timer.Start();
	}
	if (Input.Keyboard()[Keys::Down].Down()) {
		timer.Stop();
	}
	if (Input.Keyboard()[Keys::Right].Down()) {
		timer.Reset();
	}

	return;
}

void SampleScene::Draw() {
	
	Val2D<double> size{80, 80};
	Val2D pos = Val2D<double>::Lerp(p1, p2, timer.Elapsed().Second());
	DrawBoxAA(
		pos.x - size.x / 2,
		pos.y - size.y / 2,
		pos.x + size.x / 2,
		pos.y + size.y / 2,
		Color3{255, 255, 255},
		TRUE
	);

	return;
}

void SampleScene::End() {
	return;
}
