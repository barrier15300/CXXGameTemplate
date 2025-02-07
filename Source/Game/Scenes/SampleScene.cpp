#include "SampleScene.h"

bool SampleScene::Init() {
	
	//screen.Create({1280,720}, TRUE);
	screen.Create({1280,720}, TRUE, 4, 4);
	
	screen.ScreenDraw([&]() {
		IndexedVertex2D iv =
			Vertex::Factory2D::RectAngle(
			{100,100},
			{640,360},
			{255,255,255,255}
			);

		//iv = iv.PolygonFramed(30);
		
		// TODO: Isuee's PolygonFramed.
		//       - Vertex angle Isuee.

		iv.Draw();
		
		size_t start = 0, end = start + 2;

		for (size_t i = start, size = iv.index.size(); i < size; ++i) {
			IndexedVertex2D line =
				Vertex::Factory2D::Line(
				iv.vertex[iv.index[i]].pos,
				iv.vertex[iv.index[(i + 1) % size]].pos,
				{224,128,32,255},
				2
				);

			line.Draw();
		}
		
		for (size_t i = start, size = iv.vertex.size(); i < size; ++i) {
			IndexedVertex2D circle =
				Vertex::Factory2D::Circle(
				{4,4},
				iv.vertex[i].pos,
				{128,192,128,255}
				);
		
			circle.Draw();
		}

	}
	);

	return true;
}

void SampleScene::Proc() {
	
	if (Input.Keyboard()[Keys::Left].Down()) {

	}
	if (Input.Keyboard()[Keys::Down].Down()) {

	}
	if (Input.Keyboard()[Keys::Right].Down()) {

	}
	if (Input.Keyboard()[Keys::Up].Down()) {

	}

	return;
}

void SampleScene::Draw() {

	screen.Draw(Val2D<int>{0,0});

	printFPS();
	return;
}

void SampleScene::End() {
	return;
}
