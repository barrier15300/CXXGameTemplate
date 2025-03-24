#pragma once
#include "../Helper/Helper.h"
#include "../Value/Value.h"

struct GraphData : public DXHandle<DXHandleType::Graph, DeleteGraph> {

	using DXHandle::DXHandle;
	
	Val2D<int> Size{};
	bool Alpha = false;

	bool Create(const std::string &path) {

		Init(
			LoadGraph(path.c_str())
		);

		return !IsNull();
	}
	
	bool Create(const std::string &path, bool alpha) {

		Init(
			LoadGraph(path.c_str())
		);
		Alpha = alpha;

		return !IsNull();
	}

	bool Create(Val2D<int> size, bool alpha) {
		Alpha = alpha;
		Size = size;
		Init(
			MakeScreen(Size.x, Size.y, Alpha)
		);
		return !IsNull();
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

	void Draw(const Rect2D<int> &rect) const {
		DrawExtendGraph(
			rect.x,
			rect.y,
			rect.w,
			rect.h,
			*this,
			Alpha
		);
	}

	void Draw(const Rect2D<float> &rect) const {
		DrawExtendGraphF(
			rect.x,
			rect.y,
			rect.w,
			rect.h,
			*this,
			Alpha
		);
	}

	void Draw(const Val2D<int> &pos, double angle, double scale) const {
		DrawRotaGraph(
			pos.x,
			pos.y,
			scale,
			angle,
			*this,
			Alpha
		);
	}

	static const std::vector<GraphData> CreateDivGraph(const std::string &path, const Val2D<int> &size, const Val2D<int> &div) {
		std::vector<int> temp;
		temp.resize(div.x * div.y);
		LoadDivGraph(
			path.c_str(),
			temp.size(),
			div.x,
			div.y,
			size.x,
			size.y,
			temp.data()
		);
		std::vector<GraphData> ret;
		ret.assign(temp.begin(), temp.end());
		return ret;
	}

};
