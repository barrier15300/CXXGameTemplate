#include "SampleScene.h"

bool SampleScene::Init() {
	auto temp = GraphData("coursesymbol_oni.png", true);
	Graph.Create(temp.Size, true, [&] { temp.Draw({0, 0}, {0, 0}); });

	return true;
}

void SampleScene::Proc() {
	
	return;
}

void SampleScene::Draw() {
	if (Input.Keyboard()[(int)Keys::C].Press()) {
		DrawBox(size.width * pos.x, size.height * pos.y, size.width * pos.x + size.width, size.height * pos.y + size.height, GetColor(255, 255, 255), TRUE);
	} pos.x += 1;
	if (Input.Keyboard()[(int)Keys::V].Press()) {
		DrawBox(size.width * pos.x, size.height * pos.y, size.width * pos.x + size.width, size.height * pos.y + size.height, GetColor(255, 255, 255), TRUE);
	} pos.x += 1;
	if (Input.Keyboard()[(int)Keys::Oem2].Press()) {
		DrawBox(size.width * pos.x, size.height * pos.y, size.width * pos.x + size.width, size.height * pos.y + size.height, GetColor(255, 255, 255), TRUE);
	} pos.x += 1;
	if (Input.Keyboard()[(int)Keys::Oem102].Press()) {
		DrawBox(size.width * pos.x, size.height * pos.y, size.width * pos.x + size.width, size.height * pos.y + size.height, GetColor(255, 255, 255), TRUE);
	}

	return;
}

void SampleScene::End() {
	return;
}
