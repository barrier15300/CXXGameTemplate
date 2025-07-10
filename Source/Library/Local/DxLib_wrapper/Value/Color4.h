﻿#pragma once
#include "_structhelper.h"

/// <summary>
/// Color4
/// </summary>
struct Color4 {

	Color4() : a(0), r(0), g(0), b(0) {}
	Color4(int _r, int _g, int _b, int _a) : a(_a), r(_r), g(_g), b(_b) {}
	Color4(unsigned int color) { ParseHex(color); }
	Color4(const COLOR_U8& from) {
		r = from.r;
		g = from.g;
		b = from.b;
		a = from.a;
	}

	operator unsigned int() const {
		return GetHex();
	}

	operator COLOR_U8() const {
		return GetColorU8(r, g, b, a);
	}

	union {
		struct {
			byte b, g, r, a;
		};
		struct {
			std::array<byte, 4> arr;
		};
	};

	uint32_t GetHex() const {
		return union_cast<uint32_t>(arr);
	}

	void ParseHex(uint32_t from) {
		arr = union_cast<std::array<byte, 4>>(from);
	}

	std::string ToString(bool hex = true) const {
		std::string ret;
		if (hex) {
			ret = fmt::format("#{:0>8X}", GetHex());
		}
		else {
			ret = fmt::format("{}{:>3}{}", '{', fmt::join(arr.rbegin(), arr.rend(), ", "), '}');
		}
		return ret;
	}
};

TO_JSON(, Color4, {
	j = nlohmann::json{v.r, v.g, v.b, v.a};
		});

FROM_JSON(, Color4, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr[i]);
	}
		});
