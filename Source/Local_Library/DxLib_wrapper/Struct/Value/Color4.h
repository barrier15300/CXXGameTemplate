#pragma once
#include "DxLib.h"
#include "../Helper/JsonHelper.h"
#include <array>

/// <summary>
/// Color4
/// </summary>
struct Color4 {

	Color4() : r(0), g(0), b(0), a(0) {}
	Color4(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {}
	Color4(unsigned int color) : _dxcolor(color) {}

	operator unsigned int() const {
		return _dxcolor;
	}

	operator COLOR_U8() const {
		return GetColorU8(r, g, b, a);
	}

	union {
		struct {
			byte a, r, g, b;
		};
		std::array<byte, 4> arr;
		unsigned int _dxcolor;
	};
};

TO_JSON(, Color4, {
	j = nlohmann::json{v.r, v.g, v.b};
		});

FROM_JSON(, Color4, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr[i]);
	}
		});
