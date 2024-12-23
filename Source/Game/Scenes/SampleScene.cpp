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

	for (int c = 0; c < 4; ++c) {
		if (inputs[c].Down()) {
			inputtimer[c].Reset();
			inputtimer[c].Start();
		}
		if (inputtimer[c].Elapsed().Second() > 0.25) {
			inputtimer[c].Reset();
		}
		Val2D<double> pos{640, 360};
		Val2D<double> size{80, 80};
		Val2D<double> offset[4]{size * -1.5, size * -0.5, size * 0.5, size * 1.5};
		if (inputtimer[c].Running()) {
			size *= 1 + (1 - Easing::GetRate(inputtimer[c].Elapsed().Second() / 0.25, Easing::Out, Easing::Cubic)) * 0.5;
		}
		DrawBoxAA(
			pos.x + offset[c].x - (size.x / 2),
			pos.y + offset[c].y - (size.y / 2),
			pos.x + offset[c].x + (size.x / 2),
			pos.y + offset[c].y + (size.y / 2),
			Color3{255,255,255},
			TRUE
			);
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

	input.Update((Input.Keyboard()[Keys::Up].Press()));
	auto [press, hold, release] = input.GetStates();


	DrawFormatString(0, 0, Color3{255, 255, 255}, "abs(x): %f", m_abs(-1.f));

	//DrawFormatString(0, 0, Color3{255, 255, 255}, "\npress: %x\nhold: %x\nrelease: %x\nfps: %d", press, hold, release, (int)GetFPS());
	DrawFormatString(0, 0, Color3{255, 255, 255}, "\npress: %x", (byte)input.GetState());
	
	

	return;
}

void SampleScene::End() {
	return;
}
