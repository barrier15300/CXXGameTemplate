#pragma once
#include "../Include.hpp"

class Game : public IObjectBase {
public:
	Game() { Name = __func__; }
	IObjectBase* ObjectInit() { return new Game(); }
	
	virtual bool Init();
	virtual void Proc();
	virtual void Draw();
	virtual void End();

};