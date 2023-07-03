#pragma once
#include "include.h"

class O_Sample : public ObjectBase {
public:

	O_Sample() { Init(); };
	~O_Sample() { End(); };

	void Init() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:

};