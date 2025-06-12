#pragma once
#include "../../Include.hpp"

class SampleScene : public IObjectBase {
public:
	
	virtual bool Init() override;
	virtual void Proc() override;
	virtual void Draw() override;
	virtual void End() override;

	Asset::Value<Val2D<float>, "Sample/DrawPos"> pos{{}};
	Asset::Value<std::string, "Sample/Don"> Donfilepath{"Asset/Don.wav"};
	Asset::Value<std::string, "Sample/Ka"> Kafilepath{"Asset/Ka.wav"};
	GraphData Graph;
	SoundData Don;
	SoundData Ka;
	ScreenData screen;
	
	double time[2]{};

	void printFPS() {
		auto fmtstr = fmt::format("FPS: {}\nnon_ref: {}\nref: {}",(int)GetFPS(),time[0],time[1]);
		DrawBox(0, 0, GetDrawStringWidth(fmtstr.c_str(), fmtstr.size()) + 16, 64, Color3(16, 16, 16), TRUE);
		DrawString(0, 0, fmtstr.c_str(), Color3{ 255,255,255 });
	}

};
