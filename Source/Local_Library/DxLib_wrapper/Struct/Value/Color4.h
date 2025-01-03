#pragma once
#include "_structhelper.h"

/// <summary>
/// Color4
/// </summary>
struct Color4 {

	Color4() : a(0), r(0), g(0), b(0) {}
	Color4(int _r, int _g, int _b, int _a) : a(_a), r(_r), g(_g), b(_b) {}
	Color4(unsigned int color) : hexcolor(color) {}

	operator unsigned int() const {
		return hexcolor;
	}

	operator COLOR_U8() const {
		return GetColorU8(r, g, b, a);
	}

	union {
		struct {
			byte b, g, r, a;
		};
		std::array<byte, 4> arr;
		unsigned int hexcolor;
	};

	std::string ToString(bool hex = true) {
		std::string ret;
		if (hex) {
			ret = fmt::format("#{:0>8X}", hexcolor);
		}
		else {
			ret = fmt::format("{}{:>{}}{}", '{', fmt::join(arr.rbegin(), arr.rend(), ", "), 3, '}');
		}
		return ret;
	}
};

TO_JSON(, Color4, {
	j = nlohmann::json{v.r, v.g, v.b};
		});

FROM_JSON(, Color4, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr[i]);
	}
		});
