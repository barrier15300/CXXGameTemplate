#pragma once
#include "Val2D.h"

/// <summary>
/// Rect2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<typeis::Arithmetic T>
struct Rect2D {

	using value_type = T;
	using Lcvr = const Rect2D<T>&;
	using Rvr = Rect2D<T>&&;
	template<class fromT> using LcvrFrom = const Rect2D<fromT>&;
	template<class fromT> using RvrFrom = Rect2D<fromT>&&;

	constexpr Rect2D() noexcept : x(0), y(0), w(0), h(0) {}
	constexpr explicit Rect2D(T _all) noexcept : off(_all), size(_all) {}
	constexpr Rect2D(T _x, T _y, T _w, T _h) noexcept : x(_x), y(_y), w(_w), h(_h) {}
	constexpr Rect2D(Val2D<T> _p1, Val2D<T> _p2) noexcept : off(_p1), size(_p2) {}
	template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3, typeis::Arithmetic fT4> constexpr Rect2D(fT1 ft1, fT2 ft2, fT3 ft3, fT4 ft4) noexcept
		: x(SCAST(ft1)), y(SCAST(ft2)), w(SCAST(ft3)), h(SCAST(ft4)) {}
	template<typeis::Arithmetic fromT> constexpr Rect2D(LcvrFrom<fromT> v) noexcept
		: off(SCAST(v.off)), size(SCAST(v.size)) {}
	template<typeis::Arithmetic fromT> constexpr Rect2D(RvrFrom<fromT> v) noexcept
		: off(SCAST(v.off)), size(SCAST(v.size)) {}
	template<typeis::Arithmetic fromT> constexpr Rect2D(const std::initializer_list<fromT>& list) {
		if (list.size() != 4) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), list.begin());
	}
	template<typeis::Arithmetic fromT> constexpr Rect2D(std::initializer_list<fromT>&& list) {
		if (list.size() != 4) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), list.begin());
	}

	/// <summary>
	/// Data Members
	/// </summary>
	
	union {
		struct {
			T x, y, w, h;
		};
		struct {
			Val2D<T> off, size;
		};
	};

	constexpr operator RECT() const noexcept {
		union {
			Rect2D<LONG> temp{};
			RECT ret;
		};
		temp = Rect2D<LONG>(off, off + size);
		return ret;
	}

	/// <summary>
	///  Utilities
	/// </summary>
	
	template<class fromT>
	constexpr bool InRect(Val2D<fromT> pos) const noexcept {
		auto target = this->Abs();
		return (target.x <= pos.x && target.y <= pos.y) && (pos.x <= target.w && pos.y <= target.h);
	}

	constexpr Rect2D Abs() const noexcept {
		return { off, off + size };
	}

	constexpr Val2D<T> Size() const noexcept {
		return size;
	}

	constexpr Val2D<T> LeftTop() const noexcept {
		return off;
	}

	constexpr Val2D<T> CenterTop() const noexcept {
		return { off.x + size.x / 2, off.y };
	}

	constexpr Val2D<T> RightTop() const noexcept {
		return { off.x + size.x, off.y };
	}

	constexpr Val2D<T> MidLeft() const noexcept {
		return { off.x, off.y + size.y / 2 };
	}

	constexpr Val2D<T> MidCenter() const noexcept {
		return off + size / 2;
	}

	constexpr Val2D<T> MidRight() const noexcept {
		return { off.x + size.x, off.y + size.y / 2 };
	}

	constexpr Val2D<T> LeftBottom() const noexcept {
		return { off.x, off.y + size.y };
	}

	constexpr Val2D<T> CenterBottom() const noexcept {
		return { off.x + size.x / 2, off.y + size.y };
	}

	constexpr Val2D<T> RightBottom() const noexcept {
		return off + size;
	}

	constexpr Rect2D OffsetCenter() const noexcept {
		return { off - size / 2, size };
	}

	std::string ToString(int digit = 6) const {
		return fmt::format("{}{}, {}{}", '{', off.ToString(), (off + size).ToString(), '}');
	}

	/// <summary>
	/// operator
	/// </summary>

	TEMPLATE_ASSIGNMENT_OPERATOR(Rect2D, x, y, w, h);

};

TEMPLATE_BINARY_OPERATOR(Rect2D);

/// <summary>
/// json converter
/// </summary>

TO_JSON(template<class T>, Rect2D<T>, {
	j = nlohmann::json{
		{v.x, v.y}, {v.w, v.h}
	};
		});

FROM_JSON(template<class T>, Rect2D<T>, {
	for (size_t i = 0, size = v.off.arr.size(); i < size; ++i) {
		j.at(0).get_to(v.off.arr[i]);
	}
	for (size_t i = 0, size = v.size.arr.size(); i < size; ++i) {
		j.at(1).get_to(v.size.arr[i]);
	}
			});

/// <summary>
/// template auto completion helper
/// </summary>

template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3, typeis::Arithmetic fT4> Rect2D(fT1, fT2, fT3, fT4) -> Rect2D<std::common_type_t<fT1, fT2, fT3, fT4>>;
template<class fT1, class fT2> Rect2D(fT1, fT2) -> Rect2D<std::common_type_t<typename fT1::value_type, typename fT2::value_type>>;

