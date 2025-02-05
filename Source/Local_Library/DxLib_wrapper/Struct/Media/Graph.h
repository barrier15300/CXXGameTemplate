#pragma once
#include "../Helper/Helper.h"
#include "../Value/Value.h"

struct GraphData : public DXHandle<DXHandleType::Graph, DeleteGraph> {

	using DXHandle::DXHandle;

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

	Val2D<int> Size{};
	bool Alpha = false;
};
