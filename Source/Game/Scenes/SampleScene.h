#pragma once
#include "Include.hpp"

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
	
	Timer timer;
	size_t num = 4;
	ValClamp<size_t> idx{};
	double t = 0.1;

	void printFPS() {
		auto fmtstr = fmt::format("FPS: {}",(int)GetFPS());
		DrawBox(0, 0, GetDrawStringWidth(fmtstr.c_str(), fmtstr.size()) + 16, 16, Color3(16, 16, 16), TRUE);
		DrawString(0, 0, fmtstr.c_str(), Color3{ 255,255,255 });
	}

};
