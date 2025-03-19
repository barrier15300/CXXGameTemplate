#pragma once
#include "_structhelper.h"

/// <summary>
/// Color4F
/// </summary>
struct Color4F {

	Color4F(): a(0), r(0), g(0), b(0) {}
	Color4F(float _r, float _g, float _b, float _a) : a(_a), r(_r), g(_g), b(_b) {}
	Color4F(int _r, int _g, int _b, int _a) : Color4F(Color4{_r,_g,_b,_a}) {}
	Color4F(unsigned int hexcolor) : Color4F(Color4{hexcolor}) {}
	Color4F(Color4 color) {
		*this = Color4F(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
	}

	operator COLOR_F() const {
		return GetColorF(r,g,b,a);
	}

	union {
		struct {
			float b, g, r, a;
		};
		std::array<float, 4> arr;
	};

	std::string ToString(int digit = 6) const {
		std::string ret;
		ret = fmt::format("{}{:>1.{}f}{}",'{',fmt::join(arr.rbegin(),arr.rend(),", "), digit + 1,'}');
		return ret;
	}
};

TO_JSON( , Color4F, {
	j = nlohmann::json{v.r,v.g,v.b};
		});

FROM_JSON( , Color4F, {
	for(size_t i = 0,size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr[i]);
	}
		});
