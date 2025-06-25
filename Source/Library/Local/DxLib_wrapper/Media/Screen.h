#pragma once
#include "../Helper/Helper.h"
#include "../Value/Value.h"

struct ScreenData : public DXHandle<DXHandleType::Graph, DeleteGraph> {
	
	using DXHandle::DXHandle;

	bool Create(Val2D<int> size, bool alpha) {
		Init(
			MakeScreen(size.x, size.y, alpha)
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

	explicit operator const GraphData() const {
		GraphData ret;
		ret.Init(*this);
		return ret;
	}

	void Draw(const Val2D<int> &pos, bool alpha) const {
		DrawGraph(
			pos.x,
			pos.y,
			*this,
			alpha
		);
	}

	void Draw(const Val2D<float> &pos, bool alpha) const {
		DrawGraphF(
			pos.x,
			pos.y,
			*this,
			alpha
		);
	}

	bool Save(const std::string& savepath, const Rect2D<int> &rect, int compressionlevel = 2) {
		return SUCCEEDED(SaveDrawValidGraphToPNGWithStrLen(*this, rect.x, rect.y, rect.w, rect.h, (savepath + ".png").c_str(), savepath.size(), compressionlevel));
	}

	bool Save(const std::string& savename, const Val2D<int>& size, int compressionlevel = 2) {
		return Save(savename, {{},size}, compressionlevel);
	}

	bool Save(const std::string& savename, int compressionlevel = 2) {
		Val2D<int> size;
		GetGraphSize(*this, &size.x, &size.y);
		return Save(savename, size, compressionlevel);
	}
};