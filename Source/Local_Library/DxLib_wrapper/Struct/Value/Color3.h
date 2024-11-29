#pragma once
#include "DxLib.h"
#include "../Helper/JsonHelper.h"
#include <array>

/// <summary>
/// Color3
/// </summary>
struct Color3 {

	Color3() : r(0), g(0), b(0) {}
	Color3(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}

	operator unsigned int() {
		return GetColor(r, g, b);
	}

	union {
		struct {
			int r, g, b;
		};
		std::array<int, 3> arr;
	};
};

TO_JSON(, Color3, {
	j = nlohmann::json{v.r, v.g, v.b};
		});

FROM_JSON(, Color3, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr[i]);
	}
		  });
