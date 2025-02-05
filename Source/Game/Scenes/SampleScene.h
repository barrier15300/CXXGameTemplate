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
	Val2D<int> size = {80, 80};
	Val2D<double> p1{160, 360}, p2{1120, 360};
	Asset::Value<Val2D<float>, "Sample/DrawPos"> pos{{}};
	Asset::Value<std::string, "Sample/Don"> Donfilepath{"Asset/Don.wav"};
	Asset::Value<std::string, "Sample/Ka"> Kafilepath{"Asset/Ka.wav"};
	Timer timer;
	ScreenData screen;

	ModelData model;
	
};
