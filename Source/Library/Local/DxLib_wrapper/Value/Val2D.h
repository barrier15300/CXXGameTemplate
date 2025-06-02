#pragma once
#include "_structhelper.h"

/// <summary>
/// Val2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Val2D {

	using value_type = T;
	using Lcvr = const Val2D<T>&;
	using Rvr = Val2D<T>&&;
	template<class fromT> using LcvrFrom = const Val2D<fromT>&;
	template<class fromT> using RvrFrom = Val2D<fromT>&&;


	/// <summary>
	/// constructor
	/// </summary>

	constexpr Val2D() noexcept : x(0), y(0) {}
	constexpr explicit Val2D(T _all) noexcept : x(_all), y(_all) {}
	constexpr Val2D(T _x, T _y) noexcept : x(_x), y(_y) {}
	constexpr explicit Val2D(const std::complex<T> &_complex) : x(SCAST(_complex.real())), y(SCAST(_complex.imag())) {}
	constexpr explicit Val2D(std::complex<T> &&_complex) : x(SCAST(_complex.real())), y(SCAST(_complex.imag())) {}
	template<IsArithmetic fT1, IsArithmetic fT2> constexpr Val2D(fT1 ft1, fT2 ft2) noexcept : x(SCAST(ft1)), y(SCAST(ft2)) {}
	template<IsArithmetic fromT> constexpr Val2D(LcvrFrom<fromT> v) noexcept : x(SCAST(v.x)), y(SCAST(v.y)) {}
	template<IsArithmetic fromT> constexpr Val2D(RvrFrom<fromT> v) noexcept : x(SCAST(v.x)), y(SCAST(v.y)) {}
	template<IsArithmetic fromT> constexpr Val2D(const std::initializer_list<fromT>& list) {
		if (list.size() != 2) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), arr.begin());
	}
	template<IsArithmetic fromT> constexpr Val2D(std::initializer_list<fromT>&& list) {
		if (list.size() != 2) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), arr.begin());
	}

	/// <summary>
	/// union member
	/// </summary>

	union {
		struct {
			T x, y;
		};
		struct {
			std::array<T, 2> arr;
		};
	};

	/// <summary>
	/// unary operator
	/// </summary>

	constexpr Val2D operator+() const noexcept {
		return *this;
	}
	constexpr Val2D operator-() const noexcept {
		Val2D ret;
		for (size_t i = 0, size = arr.size(); i < size; ++i) { ret.arr[i] = -arr[i]; }
		return ret;
	}

	/// <summary>
	/// arr accessor
	/// </summary>

	constexpr T &operator[](size_t idx) {
		return arr[idx];
	}

	constexpr const T &operator[](size_t idx) const {
		return arr[idx];
	}

	constexpr T &at(size_t idx) {
		return arr.at(idx);
	}

	constexpr const T &at(size_t idx) const {
		return arr.at(idx);
	}

	/// <summary>
	/// vector utility
	/// </summary>

#define MEMBER_SWAP_2D_s1(a, b) constexpr Val2D a##b() const noexcept { return {a, b}; }
#define MEMBER_SWAP_2D_s2(a) MEMBER_SWAP_2D_s1(a, x) MEMBER_SWAP_2D_s1(a, y)
#define MEMBER_SWAP_2D MEMBER_SWAP_2D_s2(x) MEMBER_SWAP_2D_s2(y)

	MEMBER_SWAP_2D;

#undef MEMBER_SWAP_2D_s1
#undef MEMBER_SWAP_2D_s2
#undef MEMBER_SWAP_2D

	constexpr T Sum() const noexcept {
		return x + y;
	}

	constexpr T Diff() const noexcept {
		return x - y;
	}

	constexpr T Mul() const noexcept {
		return x * y;
	}

	constexpr T Div() const noexcept {
		return x / y;
	}

	constexpr double Dot(Lcvr v) const noexcept {
		return Val2D::Dot(*this, v);
	}

	constexpr double Cross(Lcvr v) const noexcept {
		return Val2D::Cross(*this, v);
	}

	constexpr double Length() const {
		return std::sqrt(this->Dot(*this));
	}

	constexpr Val2D Normalized() const {
		return *this / this->Length();
	}

	constexpr double Angle() const {
		return std::atan2(y, x);
	}

	template<class fromT>
	constexpr double Angle(const Val2D<fromT> &v) const {
		return std::atan2(this->Cross(v), this->Dot(v));
	}

	template<IsArithmetic floatT>
	constexpr Val2D Rotate(floatT angle) const {
		auto rotatevector = Val2D<floatT>{sin(angle), cos(angle)};
		return {this->Cross(rotatevector), this->Dot(rotatevector)};
	}

	/// <summary>
	/// static utility
	/// </summary>

	static constexpr double Dot(Lcvr lhs, Lcvr rhs) noexcept {
		return (lhs * rhs).Sum();
	}

	static constexpr double Cross(Lcvr lhs, Lcvr rhs) noexcept {
		return (lhs * rhs.yx()).Diff();
	}

	static constexpr double Angle(Lcvr lhs, Lcvr rhs) {
		return std::atan2(Cross(lhs, rhs), Dot(lhs, rhs));
	}

	static constexpr Val2D<double> Intersection(const std::pair<Val2D, Val2D> &l1, const std::pair<Val2D, Val2D> &l2) noexcept {
		double s, t, deno = Cross(l1.second - l1.first, l2.second - l2.first);
		Val2D<double> error{INFINITY, INFINITY};

		if (deno == 0) {
			return error;
		}

		s = Val2D::Cross(l2.first - l1.first, l2.second - l2.first) / deno;
		t = Val2D::Cross(l1.second - l1.first, l1.first - l2.first) / deno;

		if (s < 0 || 1 < s || t < 0 || 1 < t) {
			return error;
		}

		return l1.first + s * (l1.second - l1.first);
	}

	static constexpr double Distance(Lcvr a, Lcvr b) {
		Val2D v = a - b;
		v *= v;
		return std::sqrt(v.x + v.y);
	}

	template<IsArithmetic floatT = double>
	static constexpr Val2D<double> Lerp(Lcvr a, Lcvr b, floatT t) noexcept {
		return a + (b - a) * t;
	}

	/// <summary>
	/// debug
	/// </summary>

	std::string ToString(int spacewidth = 4, int digit = 6) const {
		return fmt::format("{}{:>{}.{}f}{}", '{', fmt::join(arr, ", "), spacewidth + digit + 1, digit, '}');
	}

	TEMPLATE_ASSINMENT_OPERATOR(Val2D, x, y);
};

TEMPLATE_COMPARE_OPERATOR(Val2D, lhs.x < rhs.x && lhs.y < rhs.y);

TEMPLATE_BINARY_OPERATOR(Val2D);

/// <summary>
/// template auto compreation helpers
/// </summary>

template<IsArithmetic fT1, IsArithmetic fT2> Val2D(fT1, fT2) -> Val2D<std::common_type_t<fT1, fT2>>;
template<IsArithmetic fromT> Val2D(std::initializer_list<fromT>) -> Val2D<fromT>;

/// <summary>
/// json converter
/// </summary>

TO_JSON(template<class T>, Val2D<T>, {
	j = nlohmann::json{v.x, v.y};
		});

FROM_JSON(template<class T>, Val2D<T>, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr.at(i));
	}
		});

