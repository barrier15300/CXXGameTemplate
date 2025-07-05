#include "SampleScene.h"
#include "Wips/function_ref.h"

bool SampleScene::Init() {
	Graph = GraphData::Make("Asset/coursesymbol_easy.png");
	
	Don = SoundData::Make(Donfilepath);
	Ka = SoundData::Make(Kafilepath);

	Font = FontData::Make(Fontpath, 24, 10);

	Input.Mouse.Lock();

	Scene->Regist<FunctionRefTest>();

	DTMFSounds['0'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_0.wav");
	DTMFSounds['1'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_1.wav");
	DTMFSounds['2'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_2.wav");
	DTMFSounds['3'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_3.wav");
	DTMFSounds['4'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_4.wav");
	DTMFSounds['5'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_5.wav");
	DTMFSounds['6'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_6.wav");
	DTMFSounds['7'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_7.wav");
	DTMFSounds['8'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_8.wav");
	DTMFSounds['9'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_9.wav");
	DTMFSounds['#'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_hash.wav");
	DTMFSounds['A'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_A.wav");
	DTMFSounds['B'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_B.wav");
	DTMFSounds['C'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_C.wav");
	DTMFSounds['D'] = SoundData::Make(DTMFSoundsFolder.Get() + "/dtmf_D.wav");

	return true;
}

void SampleScene::Proc() {

	

	return;
}

void SampleScene::Draw() {

	
	return;
}

void SampleScene::End() {
	return;
}
