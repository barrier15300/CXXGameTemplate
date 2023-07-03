#pragma once
#include "include.h"
#include "Object/O_Sample.h"

class S_Sample : public SceneBase {
public:

	S_Sample() { Init(); };
	~S_Sample() { End(); };

	void Init() override;
	void End() override;

private:

};