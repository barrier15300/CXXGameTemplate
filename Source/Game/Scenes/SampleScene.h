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

	OptimizationGraph Graph;
	Size2D<int> size{80, 80};
	Pos2D<int> pos{0, 0};

};
