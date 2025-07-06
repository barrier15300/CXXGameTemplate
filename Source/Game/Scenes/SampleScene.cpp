#include "SampleScene.h"
#include "Wips/function_ref.h"

bool SampleScene::Init() {
	Graph = GraphData::Make("Asset/coursesymbol_easy.png");
	
	Don = SoundData::Make(Donfilepath);
	Ka = SoundData::Make(Kafilepath);

	Font = FontData::Make(Fontpath, 24, 10);

	Input.Mouse.Lock();

	Scene->Regist<FunctionRefTest>();

	Text = Font.ToDrawable("press Ctrl+F1 to spawn console. press D key to test output.");

	return true;
}

void SampleScene::Proc() {

	if (Input.Keyboard[Keys::ControlKey].Press() && Input.Keyboard[Keys::F1].Down()) {
		AttachConsole::GetInstance();
	}

	if (Input.Keyboard[Keys::D].Down()) {
		std::cout << "D key pressed" << "\n";
	}

	return;
}

void SampleScene::Draw() {

	Text.Draw(Val2D{0, 0});
	
	return;
}

void SampleScene::End() {
	return;
}
