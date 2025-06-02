#pragma once
#include "../Helper/Helper.h"
#include "../Value/Value.h"

struct GraphData : public DXHandle<DXHandleType::Graph, DeleteGraph> {

	using DXHandle::DXHandle;
	
	/// <summary>
	/// Utility
	/// </summary>

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
		auto pos = rect.Abs();
		DrawExtendGraph(
			pos.x,
			pos.y,
			pos.w,
			pos.h,
			*this,
			alpha
		);
	}

	void Draw(const Rect2D<float> &rect, bool alpha) const {
		auto pos = rect.Abs();
		DrawExtendGraphF(
			pos.x,
			pos.y,
			pos.w,
			pos.h,
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



	/// 
	/// Factory
	///
		
	static GraphData Make(const std::string &path) {
		GraphData ret;
		ret.Init(LoadGraph(path.c_str()));
		return ret;
	}

	static GraphData Make(Val2D<int> size, bool alpha) {
		GraphData ret;
		ret.Init(MakeScreen(size.x, size.y, alpha));
		return ret;
	}

	static std::vector<GraphData> MakeDivGraph(const std::string &path, const Val2D<int> &size, const Val2D<int> &div) {
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
		ret.reserve(temp.size());
		for (auto &&item : temp) {
			ret.push_back((GraphData)item);
		}
		return ret;
	}

	
};
