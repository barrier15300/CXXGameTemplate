#include "SampleScene.h"
#include "Wips/function_ref.h"
#include "Wips/ClientTest.h"
#include "Wips/ServerTest.h"
#include "Wips/RingBufferTest.h"
#include "Wips/HandlerListTest.h"

bool SampleScene::Init() {
	Graph = GraphData::Make("Asset/coursesymbol_easy.png");
	
	Don.Load(Donfilepath);
	Ka.Load(Kafilepath);

	Font = FontData::Make(Fontpath, 24, 10);

	Input.Mouse.Lock();

	Scene->Regist<HandlerListTest>();

	return true;
}

void SampleScene::Proc() {
	Input.Update();

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
