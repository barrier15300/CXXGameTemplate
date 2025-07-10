#pragma once
#include "_structhelper.h"

/// <summary>
/// Color3
/// </summary>
struct Color3 {

	Color3() : r(0), g(0), b(0) {}
	Color3(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}
	Color3(uint32_t color) { ParseHex(color); }

	operator uint32_t() const {
		return GetHex();
	}

	operator COLOR_U8() const {
		return GetColorU8(r, g, b, 255);
	}

	union {
		struct {
			byte b, g, r;
		};
		struct {
			std::array<byte, 3> arr;
		};
	};

	uint32_t GetHex() const {
		return union_cast<uint32_t>(arr);
	}

	void ParseHex(uint32_t from) {
		arr = union_cast<std::array<byte, 3>>(from);
	}

	std::string ToString(bool hex = true) const {
		std::string ret;
		if (hex) {
			ret = fmt::format("#{:0>6X}", GetHex());
		}
		else {
			ret = fmt::format("{}{:>3}{}", '{', fmt::join(arr.rbegin(), arr.rend(), ", "), '}');
		}
		return ret;
	}
};

TO_JSON(, Color3, {
	j = nlohmann::json{v.r, v.g, v.b};
		});

FROM_JSON(, Color3, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr[i]);
	}
		});
