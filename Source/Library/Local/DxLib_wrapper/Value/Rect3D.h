#pragma once
#include "Val3D.h"

/// <summary>
/// Rect3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect3D {

	using value_type = T;

	constexpr Rect3D() noexcept : x(0), y(0), z(0), w(0), h(0), d(0) {}
	constexpr explicit Rect3D(T _all) noexcept : p1(_all), p2(_all) {}
	constexpr Rect3D(T _x, T _y, T _z, T _w, T _h, T _d) noexcept : x(_x), y(_y), z(_z), w(_w), h(_h), d(_d) {}
	constexpr Rect3D(Val3D<T> _p1, Val3D<T> _p2) noexcept : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3, IsArithmetic fT4, IsArithmetic fT5, IsArithmetic fT6> constexpr Rect3D(fT1 ft1, fT2 ft2, fT3 ft3, fT4 ft4, fT5 ft5, fT6 ft6) noexcept : x(SCAST(ft1)), y(SCAST(ft2)), z(SCAST(ft3)), w(SCAST(ft4)), h(SCAST(ft5)), d(SCAST(ft6)) {}
	template<IsArithmetic fT> constexpr Rect3D(const Rect3D<fT> &v) noexcept : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)), w(SCAST(v.w)), h(SCAST(v.h)), d(SCAST(v.d)) {}
	template<IsArithmetic fT> constexpr Rect3D(Rect3D<fT> &&v) noexcept : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)), w(SCAST(v.w)), h(SCAST(v.h)), d(SCAST(v.d)) {}

	union {
		struct {
			T x, y, z, w, h, d;
		};
		struct {
			Val3D<T> p1, p2;
		};
	};

	template<IsArithmetic fT>
	constexpr bool InRect(const Val3D<fT> &pos) const noexcept {
		return p1 <= pos && p2 >= pos;
	}

	constexpr Val3D<T> Size() const noexcept {
		return p2 - p1;
	}

	constexpr Rect3D Fixed() const noexcept {
		std::pair<T, T> mmx = std::minmax(p1.x, p2.x);
		std::pair<T, T> mmy = std::minmax(p1.y, p2.y);
		std::pair<T, T> mmz = std::minmax(p1.z, p2.z);
		return {
			mmx.first, mmy.first, mmz.first,
			mmx.second, mmy.second, mmz.second
		};
	}

	constexpr Rect3D &FixedThis() noexcept {
		return *this = Fixed();
	}

	std::string ToString(int digit = 6) const {
		return fmt::format("{}{}, {}{}", '{', p1.ToString(), p2.ToString(), '}');
	}
	
	TEMPLATE_ASSINMENT_OPERATOR(Rect3D, x, y, z, w, h, d);
};

TEMPLATE_BINARY_OPERATOR(Rect3D);

// <summary>
/// template auto compreation helper
/// </summary>

template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3, IsArithmetic fT4, IsArithmetic fT5, IsArithmetic fT6> Rect3D(fT1, fT2, fT3, fT4, fT5, fT6) -> Rect3D<std::common_type_t<fT1, fT2, fT3, fT4, fT5, fT6>>;
template<class fT1, class fT2> Rect3D(fT1, fT2) -> Rect3D<std::common_type_t<typename fT1::value_type, typename fT2::value_type>>;

/// <summary>
/// json converter
/// </summary>

TO_JSON(template<class T>, Rect3D<T>, {
	j = nlohmann::json{
		{v.x, v.y, v.z}, {v.w, v.h, v.d}
	};
		});

FROM_JSON(template<class T>, Rect3D<T>, {
	for (size_t i = 0, size = v.p1.arr.size(); i < size; ++i) {
		j.at(0).get_to(v.p1.arr.at(i));
	}
	for (size_t i = 0, size = v.p2.arr.size(); i < size; ++i) {
		j.at(1).get_to(v.p2.arr.at(i));
	}
		  });

