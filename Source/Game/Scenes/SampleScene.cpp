#include "SampleScene.h"

bool SampleScene::Init() {
	
	//screen.Create({1280,720}, TRUE);
	screen.Create({1280,720}, TRUE, 4, 4);
	
	screen.ScreenDraw(
		[&]() {
		IndexedVertex2D iv = Vertex::Factory2D::RectAngle({400,400},{200,200},{255,255,255,255});
		iv.Draw();
	}
	);

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

	screen.Draw(Val2D<int>{0,0});
	
	return;
}

void SampleScene::End() {
	return;
}
