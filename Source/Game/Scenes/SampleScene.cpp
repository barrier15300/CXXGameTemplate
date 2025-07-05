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

	if (Input.Keyboard[Keys::NumPad0].Down()) {
		DTMFSounds['0'].Play();
	}
	if (Input.Keyboard[Keys::NumPad1].Down()) {
		DTMFSounds['1'].Play();
	}
	if (Input.Keyboard[Keys::NumPad2].Down()) {
		DTMFSounds['2'].Play();
	}
	if (Input.Keyboard[Keys::NumPad3].Down()) {
		DTMFSounds['3'].Play();
	}
	if (Input.Keyboard[Keys::NumPad4].Down()) {
		DTMFSounds['4'].Play();
	}
	if (Input.Keyboard[Keys::NumPad5].Down()) {
		DTMFSounds['5'].Play();
	}
	if (Input.Keyboard[Keys::NumPad6].Down()) {
		DTMFSounds['6'].Play();
	}
	if (Input.Keyboard[Keys::NumPad7].Down()) {
		DTMFSounds['7'].Play();
	}
	if (Input.Keyboard[Keys::NumPad8].Down()) {
		DTMFSounds['8'].Play();
	}
	if (Input.Keyboard[Keys::NumPad9].Down()) {
		DTMFSounds['9'].Play();
	}
	
	if (Input.Keyboard[Keys::NumPad0].Up()) {
		DTMFSounds['0'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad1].Up()) {
		DTMFSounds['1'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad2].Up()) {
		DTMFSounds['2'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad3].Up()) {
		DTMFSounds['3'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad4].Up()) {
		DTMFSounds['4'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad5].Up()) {
		DTMFSounds['5'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad6].Up()) {
		DTMFSounds['6'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad7].Up()) {
		DTMFSounds['7'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad8].Up()) {
		DTMFSounds['8'].Stop();
	}
	if (Input.Keyboard[Keys::NumPad9].Up()) {
		DTMFSounds['9'].Stop();
	}

	return;
}

void SampleScene::Draw() {

	
	return;
}

void SampleScene::End() {
	return;
}
