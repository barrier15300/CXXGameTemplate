#include "SampleScene.h"

bool SampleScene::Init() {
	
	//screen.Create({1280,720}, TRUE);
	screen.Create({1280,720}, TRUE, 4, 4);
	Line.Create({1280,720}, TRUE, 4, 4);
	Mid.Create({1280,720}, TRUE, 4, 4);
	
	screen.ScreenDraw([&]() {
		IndexedVertex2D iv =
			Vertex::Factory2D::Framed(
			Vertex::Factory2D::RectAngle(
			{100,100},
			{500,300},
			{255,255,255,255}
			),
			50
			);
		iv = Vertex::Factory2D::Framed(iv, 6);
		// TODO: Iseue's Inversed VertexData.
		iv.Draw();
	}
	);

	Mid.ScreenDraw([&]{
		IndexedVertex2D iv;
		iv = Vertex::Factory2D::Circle(
			{20,20},
			{640,360},
			{255,0,0,0},
			32
		);
		iv.vertex[iv.vertex.size() - 1].color = {255,0,0,255};
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

	//Line.ScreenDraw([&]{
	//	ClearDrawScreen();
	//	IndexedVertex2D iv;
	//	iv = Vertex::Factory2D::Framed(
	//		Vertex::Factory2D::Line(
	//		{640,360},
	//		Input.Mouse().GetMousePos(),
	//		{0,255,0,255},
	//		100
	//	),
	//		20
	//		);
	//	iv.Draw();
	//}
	//);

	Line.Draw(Val2D<int>{0,0});
	Mid.Draw(Val2D<int>{0,0});
	screen.Draw(Val2D<int>{0,0});
	
	return;
}

void SampleScene::End() {
	return;
}
