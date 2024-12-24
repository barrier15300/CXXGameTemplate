#pragma once
#include "../Value/Value.h"

template<class T>
struct Square {

	Square() {}
	Square(const Val2D<T> &pos, const Val2D<T> &size, bool fill = true) :
		Pos(pos), Size(size), m_Fill(fill) {}

	const Rect2D<T> &GetRect() {
		return Rect2D<T>(
			Pos - Size * Origin,
			Pos + Size * Origin
		);
	}

	void Draw(const Val2D<T> &offset = {}) {
		auto &&rect = this->GetRect() + Rect2D<T>(offset, offset);
		if (m_Fill) {
			this->DrawBase(
				rect,
				Color,
				true
			);
		}
		if (Edge != 0) {
			this->DrawBase(
				rect,
				EdgeColor,
				false
			);
		}
	}

	Val2D<T> Pos{};
	Val2D<T> Size{};
	Val2D<double> Origin{};
	double Edge = 0;
	Color3 Color{};
	Color3 EdgeColor{};

private:

	bool m_Fill = true;
	
	void DrawBase(const Rect2D<T> &rect, const Color3 &color, bool fill) {
		DrawBoxAA(
			rect.x,
			rect.y,
			rect.w,
			rect.h,
			color,
			fill,
			Edge
		);
	}
};