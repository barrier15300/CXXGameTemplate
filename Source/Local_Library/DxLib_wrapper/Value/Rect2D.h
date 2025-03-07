#pragma once
#include "Val2D.h"

/// <summary>
/// Rect2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect2D {

	using value_type = T;

	constexpr Rect2D() noexcept : x(0), y(0), w(0), h(0) {}
	constexpr explicit Rect2D(T _all) noexcept : p1(_all), p2(_all) {}
	constexpr Rect2D(T _x, T _y, T _w, T _h) noexcept : x(_x), y(_y), w(_w), h(_h) {}
	constexpr Rect2D(Val2D<T> _p1, Val2D<T> _p2) noexcept : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3, IsArithmetic fT4> constexpr Rect2D(fT1 ft1, fT2 ft2, fT3 ft3, fT4 ft4) noexcept : x(SCAST(ft1)), y(SCAST(ft2)), w(SCAST(ft3)), h(SCAST(ft4)) {}
	template<IsArithmetic fT> constexpr Rect2D(const Rect2D<fT> &v) noexcept : x(SCAST(v.x)), y(SCAST(v.y)), w(SCAST(v.w)), h(SCAST(v.h)) {}
	template<IsArithmetic fT> constexpr Rect2D(Rect2D<fT> &&v) noexcept : x(SCAST(v.x)), y(SCAST(v.y)), w(SCAST(v.w)), h(SCAST(v.h)) {}

	union {
		struct {
			T x, y, w, h;
		};
		struct {
			Val2D<T> p1, p2;
		};
	};

	constexpr operator RECT() const {
		union {
			Rect2D<LONG> temp{};
			RECT ret;
		};
		temp = *this;
		return ret;
	}

	template<IsArithmetic fT>
	constexpr bool InRect(const Val2D<fT> &pos) const noexcept {
		return p1 <= pos && p2 >= pos;
	}

	constexpr Val2D<T> Size() const noexcept {
		return p2 - p1;
	}

	constexpr Rect2D Fixed() const noexcept {
		std::pair<T, T> mmx = std::minmax(p1.x, p2.x);
		std::pair<T, T> mmy = std::minmax(p1.y, p2.y);
		return {
			mmx.first, mmy.first,
			mmx.second, mmy.second
		};
	}

	constexpr Rect2D &FixedThis() noexcept {
		return *this = Fixed();
	}

	std::string ToString(int digit = 6) const {
		return fmt::format("{}{}, {}{}", '{', p1.ToString(), p2.ToString(), '}');
	}

	TEMPLATE_ASSINMENT_OPERATOR(Rect2D);
};

TEMPLATE_BINARY_OPERATOR(Rect2D);

/// <summary>
/// template auto compreation helper
/// </summary>

template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3, IsArithmetic fT4> Rect2D(fT1, fT2, fT3, fT4) -> Rect2D<std::common_type_t<fT1, fT2, fT3, fT4>>;
template<class fT1, class fT2> Rect2D(fT1, fT2) -> Rect2D<std::common_type_t<typename fT1::value_type, typename fT2::value_type>>;

/// <summary>
/// json converter
/// </summary>

TO_JSON(template<class T>, Rect2D<T>, {
	j = nlohmann::json{
		{v.x, v.y}, {v.w, v.h}
	};
		});

FROM_JSON(template<class T>, Rect2D<T>, {
	for (size_t i = 0, size = v.p1.arr.size(); i < size; ++i) {
		j.at(0).get_to(v.p1.arr[i]);
	}
	for (size_t i = 0, size = v.p2.arr.size(); i < size; ++i) {
		j.at(1).get_to(v.p2.arr[i]);
	}
		  });
