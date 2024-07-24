#include "SampleScene.h"

bool SampleScene::Init() {
	auto temp = GraphData("coursesymbol_oni.png", true);
	Graph.Create(temp.Size, true, [&] { temp.Draw({0, 0}, {0, 0}); });

	Pos2D p = (Pos2D<int>(100, 100) - Pos2D<float>(50, 50) * Pos2D<float>(0, 0));

	return true;
}

void SampleScene::Proc() {

	return;
}

void SampleScene::Draw() {
	Graph.Draw();
	return;
}

void SampleScene::End() {
	return;
}
