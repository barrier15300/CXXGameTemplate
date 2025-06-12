#include "SampleScene.h"

bool SampleScene::Init() {
	Graph = GraphData::Make("Asset/coursesymbol_easy.png");
	
	Don = SoundData::Make(Donfilepath);
	Ka = SoundData::Make(Kafilepath);

	Input.Mouse.Lock();

	std::function<int(int, int)> add = [](int l, int r) { return l * r; };
	function_ref<int(int, int)> add_ref = [](int l, int r) { return l * r; };

	constexpr size_t count = 1000;

	Timer t;
	
	t.Restart();
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < count; ++j) {
			int ret = add(i, j);
		}
	}
	time[0] = t.Elapsed().Second();

	t.Restart();
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < count; ++j) {
			int ret = add_ref(i, j);
		}
	}
	time[1] = t.Elapsed().Second();

	return true;
}

void SampleScene::Proc() {

	if (Input.Keyboard['D'].Down()) {
		Ka.Play();
	}
	if (Input.Keyboard['F'].Down()) {
		Don.Play();
	}
	if (Input.Keyboard['J'].Down()) {
		Don.Play();
	}
	if (Input.Keyboard['K'].Down()) {
		Ka.Play();
	}

	
	


	return;
}

void SampleScene::Draw() {
	//Graph.Draw(Val2D{640, 360}, true);

	double speed = 100;

	Val2D<double> offset = Val2D<double>{ 640, 360 };
	Val2D<double> direction = Val2D<double>{ 0, 0 };

	DrawCircle(
		offset.x,
		offset.y,
		4,
		Color3{255, 255, 255},
		true
	);

	direction = Input.Mouse.GetMousePos() - offset;

	DrawLineAA(
		offset.x, 
		offset.y, 
		offset.x + direction.x,
		offset.y + direction.y,
		Color3{ 255, 0, 0 }, 
		4
	);

	direction = direction.Normalized() * speed;

	DrawLineAA(
		offset.x,
		offset.y,
		offset.x + direction.x,
		offset.y + direction.y,
		Color3{ 0, 255, 0 },
		4
	);

	printFPS();
	return;
}

void SampleScene::End() {
	return;
}
