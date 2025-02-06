#pragma once
#include "_structhelper.h"

/// <summary>
/// Val2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Val2D {

	/// <summary>
	/// constructor
	/// </summary>

	Val2D() : x(0), y(0) {}
	Val2D(T _all) : x(_all), y(_all) {}
	Val2D(T _x, T _y) : x(_x), y(_y) {}
	Val2D(const std::complex<T> &_complex) : x(SCAST(_complex.real())), y(SCAST(_complex.imag())) {}
	Val2D(std::complex<T> &&_complex) : x(SCAST(_complex.real())), y(SCAST(_complex.imag())) {}
	template<IsArithmetic fT_x, IsArithmetic fT_y> Val2D(fT_x &&_x, fT_x &&_y) : x(SCAST(_x)), y(SCAST(_y)) {};
	template<IsArithmetic fT> Val2D(const Val2D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)) {}
	template<IsArithmetic fT> Val2D(Val2D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.y)) {}

	/// <summary>
	/// union member
	/// </summary>

	union {
		struct {
			T x, y;
		};
		std::array<T, 2> arr;
	};

	/// <summary>
	/// unary operator
	/// </summary>
	
	Val2D operator+() const {
		return *this;
	}
	Val2D operator-() const {
		Val2D ret;
		for (size_t i = 0, size = this->arr.size(); i < size; ++i) { ret.arr[i] = -this->arr[i]; }
		return ret;
	}

	/// <summary>
	/// arr accessor
	/// </summary>
	
	T& operator[](size_t idx) {
		return arr[idx];
	}

	const T& operator[](size_t idx) const {
		return arr[idx];
	}

	T& at(size_t idx) {
		if (idx >= arr.size()) throw std::out_of_range("Index out of range");
		return arr[idx];
	}

	const T& at(size_t idx) const {
		if (idx >= arr.size()) throw std::out_of_range("Index out of range");
		return arr[idx];
	}

	/// <summary>
	/// vector utility
	/// </summary>

	double Dot(const Val2D &v) const {
		return x * v.x + y * v.y;
	}

	double Cross(const Val2D &v) const {
		return x * v.y - y * v.x;
	}

	double Length() const {
		return std::sqrt(Dot(*this));
	}

	Val2D<double> Normalized() const {
		return *this / Length();
	}

	double Angle() const {
		return std::atan2(y, x);
	}

	double Angle(const Val2D& v) const {
		return std::atan2(Cross(v), Dot(v));
	}

	Val2D<double> Rotate(double angle) const {
		Val2D<double> rotatevector{sin(angle), cos(angle)};
		return {this->Cross(rotatevector), this->Dot(rotatevector)};
	}

	/// <summary>
	/// static utility
	/// </summary>

	static double Dot(const Val2D &lhs, const Val2D &rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	static double Cross(const Val2D &lhs,const Val2D &rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}

	static double Angle(const Val2D &lhs, const Val2D &rhs) {
		return std::atan2(Cross(lhs, rhs), Dot(lhs, rhs));
	}

	static Val2D<double> Intersection(const std::pair<Val2D, Val2D> &l1, const std::pair<Val2D, Val2D> &l2) {
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

	static double Distance(const Val2D &a, const Val2D &b) {
		Val2D v = a - b;
		v = v * v;
		return std::sqrt(v.x + v.y);
	}

	static Val2D<double> Lerp(const Val2D &a, const Val2D &b, double t) {
		return a + (b - a) * t;
	}

	/// <summary>
	/// debug
	/// </summary>

	std::string ToString(int spacewidth = 4, int digit = 6) const {
		return fmt::format("{}{:>{}.{}f}{}", '{', fmt::join(arr, ", "), spacewidth + digit + 1, digit, '}');
	}

#define OPERATOR_BASE(type)\
	template<IsArithmetic fT> Val2D &operator##type##=(const Val2D<fT> &v) { this->x ##type##= v.x; this->y ##type##= v.y; return *this; }\
	template<IsArithmetic fT> Val2D &operator##type##=(Val2D<fT> &&v) { this->x ##type##= v.x; this->y ##type##= v.y; return *this; }

	OPERATOR_BASE(+);
	OPERATOR_BASE(-);
	OPERATOR_BASE(*);
	OPERATOR_BASE(/ );

};

COMPARE_OPERATOR_BASE(Val2D, lhs.x < rhs.x && lhs.y < rhs.y);

TEMPLATE_OPERATOR_BASE(Val2D, +);
TEMPLATE_OPERATOR_BASE(Val2D, -);
TEMPLATE_OPERATOR_BASE(Val2D, *);
TEMPLATE_OPERATOR_BASE(Val2D, / );

TO_JSON(template<class T>, Val2D<T>, {
	j = nlohmann::json{v.x, v.y};
		});

FROM_JSON(template<class T>, Val2D<T>, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr.at(i));
	}
		  });

