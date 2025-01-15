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
	
	double Length() const {
		return std::sqrt(this->x * this->x + this->y * this->y);
	}

	Val2D<double> Norm() const {
		double len = Length();
		return Val2D<double>(x / len, y / len);
	}

	/// <summary>
	/// static utility
	/// </summary>

	static T Distance(const Val2D &a, const Val2D &b) {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	static Val2D<double> Lerp(const Val2D &a, const Val2D &b, double t) {
		return a + (b - a) * t;
	}

	/// <summary>
	/// debug
	/// </summary>

	std::string ToString(int spacewidth = 4, int digit = 6) {
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

