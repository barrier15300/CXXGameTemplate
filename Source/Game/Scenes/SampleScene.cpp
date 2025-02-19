#include "SampleScene.h"

bool SampleScene::Init() {
	
	//screen.Create({1280,720}, TRUE);
	screen.Create({1280,720}, TRUE, 4, 4);
	
	screen.ScreenDraw([&]() {
		IndexedVertex2D iv =
			Vertex::Factory2D::RectAngle(
			{240,240},
			{640,360},
			{255,255,255,255}
			);

		auto framed = iv.Framed(10, 1);
		
		// TODO: cos theorem will Isuee killer
		//       - why? -> will make tow trapezoid.

		// TODO: Isuee will PolygonFramed.
		//       - Vertex angle Isuee.

		iv.Draw();
		
		for(auto& v : framed.vertex){
			v.color = {255,0,255,255};
		}

		framed.Draw();
		
		size_t start = 0, end = start + 4;

		//for (size_t i = start, size = iv.index.size(); i < size; ++i) {
		//	IndexedVertex2D line =
		//		Vertex::Factory2D::Line(
		//		iv.vertex[iv.index[i]].pos,
		//		iv.vertex[iv.index[(i + 1) % size]].pos,
		//		{224,128,32,255},
		//		4
		//		);
		//
		//	line.Draw();
		//}
		//
		//for (size_t i = start, size = iv.vertex.size(); i < size; ++i) {
		//	IndexedVertex2D circle =
		//		Vertex::Factory2D::Circle(
		//		{8,8},
		//		iv.vertex[i].pos,
		//		{128,192,128,255}
		//		);
		//
		//	circle.Draw();
		//}
		
		//for (size_t i = start, size = framed.index.size(); i < end; ++i) {
		//	IndexedVertex2D line =
		//		Vertex::Factory2D::Line(
		//		framed.vertex[framed.index[i]].pos,
		//		framed.vertex[framed.index[(i + 1) % size]].pos,
		//		{32,128,224,255},
		//		4
		//		);
		//
		//	line.Draw();
		//}
		//
		//for (size_t i = start, size = framed.vertex.size(); i < end; ++i) {
		//	IndexedVertex2D circle =
		//		Vertex::Factory2D::Circle(
		//		{8,8},
		//		framed.vertex[i].pos,
		//		{192,128,128,255}
		//		);
		//
		//	circle.Draw();
		//}
		
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

	screen.Draw(Val2D{0,0});

	printFPS();
	return;
}

void SampleScene::End() {
	return;
}
