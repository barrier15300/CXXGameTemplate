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

	bool Create(Val2D<int> size, bool alpha) {
		Init(
			MakeScreen(size.x, size.y, alpha)
		);
		return !IsNull();
	}

	Val2D<int> Size() const {
		Val2D<int> ret;
		GetGraphSize(*this, &ret.x, &ret.y);
		return ret;
	}
	
	/// <summary>
	/// Draw
	/// </summary>
	
	// standard
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

	// rect
	void Draw(const Rect2D<int> &rect, bool alpha) const {
		DrawExtendGraph(
			rect.x,
			rect.y,
			rect.w,
			rect.h,
			*this,
			alpha
		);
	}

	void Draw(const Rect2D<float> &rect, bool alpha) const {
		DrawExtendGraphF(
			rect.x,
			rect.y,
			rect.w,
			rect.h,
			*this,
			alpha
		);
	}

	// rotate
	void Draw(const Val2D<int> &pos, double angle, double scale, bool alpha) const {
		DrawRotaGraph(
			pos.x,
			pos.y,
			scale,
			angle,
			*this,
			alpha
		);
	}

	// static factory
	static std::vector<GraphData> CreateDivGraph(const std::string &path, const Val2D<int> &size, const Val2D<int> &div) {
		std::vector<int> temp;
		temp.resize((size_t)div.x * div.y);
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
		for (auto &&item : temp) {
			ret.emplace_back(item);
		}
		return ret;
	}

	
};
