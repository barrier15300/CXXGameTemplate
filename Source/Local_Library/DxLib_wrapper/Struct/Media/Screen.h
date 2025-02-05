#pragma once
#include "../Helper/Helper.h"
#include "../Value/Value.h"

struct ScreenData : public DXHandle<DXHandleType::Graph, DeleteGraph> {
	
	using DXHandle::DXHandle;

	bool Create(Val2D<int> size, bool alpha) {
		Size = size;
		Alpha = alpha;
		Init(
			MakeScreen(Size.x, Size.y, Alpha)
		);
		return !IsNull();
	}

	bool Create(Val2D<int> size, bool alpha, int antiailiasSample, int antiailiasQuality) {
		antiailiasQuality = std::clamp(antiailiasQuality, 0, GetMultiSampleQuality(antiailiasSample));
		SetDrawValidMultiSample(antiailiasSample, antiailiasQuality);
		bool res = Create(size, alpha);
		SetDrawValidMultiSample(0, 0);
		return res;
	}

	template<class _func>
	void ScreenDraw(_func drawfunc) const {
		DXHandle<> _buf = GetDrawScreen();
		SetDrawScreen(*this);
		drawfunc();
		SetDrawScreen(_buf);
	}

	explicit operator GraphData() const {
		GraphData ret;
		ret.Size = Size;
		ret.Alpha = Alpha;
		ret.Init(*this);
		return ret;
	}

	void Draw(const Val2D<int> &pos) const {
		DrawGraph(
			pos.x,
			pos.y,
			*this,
			Alpha
		);
	}

	void Draw(const Val2D<float> &pos) const {
		DrawGraphF(
			pos.x,
			pos.y,
			*this,
			Alpha
		);
	}

	Val2D<int> Size;
	bool Alpha = false;
};