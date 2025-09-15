#pragma once
#include "Include.hpp"

class FunctionRefTest : public IObjectBase {
public:
	virtual bool Init();
	virtual void Proc();
	virtual void Draw();
	virtual void End();

	double time[5]{};
	size_t ret[5]{};

	void print() {
		auto fmtstr = fmt::format("non_ref: {}, {}\nref:     {}, {}\nmove:    {}, {}\nnormal:  {}, {}\nraw:     {}, {}", time[0], ret[0], time[1], ret[1], time[2], ret[2], time[3], ret[3], time[4], ret[4]);
		DrawBox(0, 16, GetDrawStringWidth(fmtstr.c_str(), fmtstr.size()) + 16, 96, Color3(16, 16, 16), TRUE);
		DrawString(0, 16, fmtstr.c_str(), Color3{ 255,255,255 });
	}
};