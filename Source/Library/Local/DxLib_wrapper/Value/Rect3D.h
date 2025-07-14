#pragma once
#include "Val3D.h"

/// <summary>
/// Rect3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<typeis::Arithmetic T>
struct Rect3D {

	DEFINE_TRAITS(Rect3D);

	constexpr Rect3D() noexcept : off(0), size(0) {}
	constexpr explicit Rect3D(T _all) noexcept : off(_all), size(_all) {}
	constexpr Rect3D(T _x, T _y, T _z, T _w, T _h, T _d) noexcept : off(_x, _y, _z), size(_w, _h, _d) {}
	constexpr Rect3D(Val3D<T> _off, Val3D<T> _size) noexcept : off(_off), size(_size) {}
	template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3, typeis::Arithmetic fT4, typeis::Arithmetic fT5, typeis::Arithmetic fT6>
	constexpr Rect3D(fT1 ft1, fT2 ft2, fT3 ft3, fT4 ft4, fT5 ft5, fT6 ft6) noexcept
		: off(SCAST(ft1), SCAST(ft2), SCAST(ft3)), size(SCAST(ft4), SCAST(ft5), SCAST(ft6)) { }
	template<typeis::Arithmetic fromT> constexpr Rect3D(LcvrFrom<fromT> v) noexcept
		: off(SCAST(v.off)), size(SCAST(v.size)) { }
	template<typeis::Arithmetic fromT> constexpr Rect3D(RvrFrom<fromT> v) noexcept
		: off(SCAST(v.off)), size(SCAST(v.size)) { }
	template<typeis::Arithmetic fromT> constexpr Rect3D(const std::initializer_list<fromT>& list) {
		if (list.size() != 6) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), list.begin());
	}
	template<typeis::Arithmetic fromT> constexpr Rect3D(std::initializer_list<fromT>&& list) {
		if (list.size() != 6) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), list.begin());
	}

	/// <summary>
	/// Data Members
	/// </summary>
	union {
		struct {
			Val3D<T> off, size;
		};
		struct {
			T x, y, z, w, h, d;
		};
	};

	/// <summary>
	/// Utilities
	/// </summary>
	template<class fromT>
	constexpr bool InRect(LcvrFrom<fromT> pos) const noexcept {
		return off <= pos && pos <= off + size;
	}

	constexpr Rect3D Abs() const noexcept {
		return { off, off + size };
	}

	constexpr Val3D<T> Size() const noexcept {
		return size;
	}

	constexpr Val3D<T> LeftBottomBack() const noexcept {
		return off;
	}

	constexpr Val3D<T> RightTopFront() const noexcept {
		return off + size;
	}

	constexpr Val3D<T> Center() const noexcept {
		return off + size / 2;
	}

	constexpr Rect3D OffsetCenter() const noexcept {
		return { off - size / 2, size };
	}

	std::string ToString(int digit = 6) const {
		return fmt::format("{}{}, {}{}", '{', off.ToString(), (off + size).ToString(), '}');
	}

	/// <summary>
	/// operator
	/// </summary>

	TEMPLATE_ASSIGNMENT_OPERATOR(Rect3D, x, y, z, w, h, d);
	
};

TEMPLATE_BINARY_OPERATOR(Rect3D);
	
/// <summary>
/// json converter
/// </summary>

TO_JSON(template<class T>, Rect3D<T>, {
	j = nlohmann::json{
		{v.off.x, v.off.y, v.off.z}, {v.size.x, v.size.y, v.size.z}
	};
	});

FROM_JSON(template<class T>, Rect3D<T>, {
	for (size_t i = 0, size = v.off.arr.size(); i < size; ++i) {
		j.at(0).get_to(v.off.arr[i]);
	}
	for (size_t i = 0, size = v.size.arr.size(); i < size; ++i) {
		j.at(1).get_to(v.size.arr[i]);
	}
	});

/// <summary>
/// template auto comprehension helper
/// </summary>

template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3, typeis::Arithmetic fT4, typeis::Arithmetic fT5, typeis::Arithmetic fT6>
Rect3D(fT1, fT2, fT3, fT4, fT5, fT6) -> Rect3D<std::common_type_t<fT1, fT2, fT3, fT4, fT5, fT6>>;
template<class fT1, class fT2>
Rect3D(fT1, fT2) -> Rect3D<std::common_type_t<typename fT1::value_type, typename fT2::value_type>>;
