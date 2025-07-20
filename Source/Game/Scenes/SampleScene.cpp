#include "SampleScene.h"
#include "Wips/function_ref.h"
#include "Wips/ClientTest.h"
#include "Wips/ServerTest.h"

bool SampleScene::Init() {
	Graph = GraphData::Make("Asset/coursesymbol_easy.png");
	
	Don = SoundData::Make(Donfilepath);
	Ka = SoundData::Make(Kafilepath);

	Font = FontData::Make(Fontpath, 24, 10);

	Input.Mouse.Lock();

	Scene->Regist<FunctionRefTest>();
	Scene->Regist<ClientTest>();
	Scene->Regist<ServerTest>();

	return true;
}

void SampleScene::Proc() {
	Input.Update();

	if (Input.Keyboard[Keys::D1].Down()) {
		Scene->Change(typeid(ServerTest));
	}

	if (Input.Keyboard[Keys::D2].Down()) {
		Scene->Change(typeid(ClientTest));
	}
	
	Scene->Proc();

	return;
}

void SampleScene::Draw() {
	Scene->Draw();
	return;
}

void SampleScene::End() {
	return;
}
