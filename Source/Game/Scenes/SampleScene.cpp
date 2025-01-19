#include "SampleScene.h"

bool SampleScene::Init() {
	//Don.Create(Donfilepath);
	//Ka.Create(Kafilepath);
	model.Create("");
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

	if (timer.Elapsed().Second() > 1) {
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
	if (Input.Keyboard()[Keys::Up].Down()) {
		model.Settings().Position({1,1,1});
	}

	return;
}

void SampleScene::Draw() {
	
	Val2D<double> size{80, 80};
	Val2D pos = Val2D<double>::Lerp(p1, p2, timer.Elapsed().FrameTime());
	
	DrawBoxAA(
		p1.x - size.x / 2,
		p1.y - size.y / 2,
		p1.x + size.x / 2,
		p1.y + size.y / 2,
		Color3{255, 255, 255},
		TRUE
	);
	DrawBoxAA(
		p2.x - size.x / 2,
		p2.y - size.y / 2,
		p2.x + size.x / 2,
		p2.y + size.y / 2,
		Color3{255, 255, 255},
		TRUE
	);
	DrawBoxAA(
		pos.x - size.x / 2,
		pos.y - size.y / 2,
		pos.x + size.x / 2,
		pos.y + size.y / 2,
		Color3{255, 255, 255},
		TRUE
	);

	DrawFormatString(0,0,Color3{255,255,255},"%s", model.Pos->ToString().c_str());

	return;
}

void SampleScene::End() {
	return;
}
