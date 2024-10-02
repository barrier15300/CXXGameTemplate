#pragma once
#include "../../Include.hpp"

class SampleScene : public IObjectBase {
public:
	SampleScene() {
		Name = __func__;
	}

	IObjectBase* ObjectInit() {
		return new SampleScene();
	}
	
	virtual bool Init();
	virtual void Proc();
	virtual void Draw();
	virtual void End();

	GraphData Graph;
	Val2D<int> size = {80, 80};
	decltype(Asset)::Value<"Sample/DrawPos", Val2D<float>> pos{{}};
	Timer timer[4];
};
