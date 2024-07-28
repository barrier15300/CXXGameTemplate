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
	Graph.Draw({200,200});
	return;
}

void SampleScene::End() {
	return;
}
