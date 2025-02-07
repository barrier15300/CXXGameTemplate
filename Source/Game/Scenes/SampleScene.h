#pragma once
#include "../../Include.hpp"

class SampleScene : public IObjectBase {
public:
	
	IObjectBase* ObjectInit() {
		return new SampleScene();
	}
	
	virtual bool Init();
	virtual void Proc();
	virtual void Draw();
	virtual void End();

	//GraphData Graph;
	//SoundData Don;
	//SoundData Ka;
	Asset::Value<Val2D<float>, "Sample/DrawPos"> pos{{}};
	Asset::Value<std::string, "Sample/Don"> Donfilepath{"Asset/Don.wav"};
	Asset::Value<std::string, "Sample/Ka"> Kafilepath{"Asset/Ka.wav"};
	ScreenData screen;

	void printFPS() {
		auto fmtstr = fmt::format("FPS: {}",(int)GetFPS());
		DrawBox(0,0,GetDrawStringWidth(fmtstr.c_str(),fmtstr.size()) + 16,32,Color3(16,16,16),TRUE);
		DrawString(0,0,fmtstr.c_str(),Color3{255,255,255});
	}

};
