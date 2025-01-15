#pragma once
#include "../Helper/DXHandle.h"

struct GraphData : public DXHandle<DXHandleType::Graph> {

	using DXHandle::DXHandle;

	bool Create(const std::string &path) {

		*this = LoadGraph(path.c_str());

		return !IsNull();
	}
	
	bool Create(const std::string &path, bool alpha) {

		*this = LoadGraph(path.c_str());
		Alpha = alpha;

		return !IsNull();
	}
	
	template<class T>
	void Draw(const Val2D<T> &pos) {
		DrawGraphF(
			static_cast<float>(pos.x),
			static_cast<float>(pos.y),
			*this,
			Alpha
		);
	}

	template<class T>
	void Draw(const Rect2D<T> &rect) {
		DrawExtendGraphF(
			static_cast<float>(rect.x),
			static_cast<float>(rect.y),
			static_cast<float>(rect.w),
			static_cast<float>(rect.h),
			*this,
			Alpha
		);
	}

	Val2D<int> Size{};
	bool Alpha = true;

private:
	int InitImpl() {
		DeleteGraph(*this);
	}
};
