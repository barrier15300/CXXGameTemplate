#include "SampleScene.h"

bool SampleScene::Init() {
	Graph = GraphData::Make("Asset/coursesymbol_easy.png");
	
	Don = SoundData::Make(Donfilepath);
	Ka = SoundData::Make(Kafilepath);

	return true;
}

void SampleScene::Proc() {

	if (Input.Keyboard()['D'].Down()) {
		Ka.Play();
	}
	if (Input.Keyboard()['F'].Down()) {
		Don.Play();
	}
	if (Input.Keyboard()['J'].Down()) {
		Don.Play();
	}
	if (Input.Keyboard()['K'].Down()) {
		Ka.Play();
	}

	std::array<int, 100> arr;
	ContainerUtility<decltype(arr)> a(arr);




	return;
}

void SampleScene::Draw() {
	Graph.Draw(Val2D{640, 360}, true);
	printFPS();
	return;
}

void SampleScene::End() {
	return;
}
