#pragma once
#include "../Helper/JsonHelper.h"
#include "../Helper/StructHelper.h"
#include <array>

/// <summary>
/// Val2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Val2D {

	Val2D() : x(0), y(0) {}
	Val2D(T &&_x, T &&_y) : x(_x), y(_y) {}
	template<IsArithmetic fT_x, IsArithmetic fT_y> Val2D(fT_x &&_x, fT_y &&_y) : x(SCAST(_x)), y(SCAST(_y)) {};
	template<IsArithmetic fT> Val2D(const Val2D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)) {}
	template<IsArithmetic fT> Val2D(Val2D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.y)) {}

	union {
		struct {
			T x, y;
		};
		std::array<T, 2> arr;
	};

	Val2D operator+() const & {
		return *this;
	}
	Val2D operator-() const & {
		Val2D ret;
		for (size_t i = 0, size = this->arr.size(); i < size; ++i) { ret.arr[i] = -this->arr[i]; }
		return ret;
	}

#define OPERATOR_BASE(type)\
	template<IsArithmetic fT> Val2D &operator##type##=(const Val2D<fT> &v) { this->x ##type##= v.x; this->y ##type##= v.y; return *this; }\
	template<IsArithmetic fT> Val2D &operator##type##=(Val2D<fT> &&v) { this->x ##type##= v.x; this->y ##type##= v.y; return *this; }\
	\
	template<IsArithmetic fT> Val2D &operator##type##=(const fT &v) { this->x ##type##= v; this->y ##type##= v; return *this; }\
	template<IsArithmetic fT> Val2D &operator##type##=(fT &&v) { this->x ##type##= v; this->y ##type##= v; return *this; }

	OPERATOR_BASE(+);
	OPERATOR_BASE(-);
	OPERATOR_BASE(*);
	OPERATOR_BASE(/ );

};

OPERATOR2_BASE(Val2D, +);
OPERATOR2_BASE(Val2D, -);
OPERATOR2_BASE(Val2D, *);
OPERATOR2_BASE(Val2D, / );

TO_JSON(template<class T>, Val2D<T>, {
	j = nlohmann::json{v.x, v.y};
		});

FROM_JSON(template<class T>, Val2D<T>, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr.at(i));
	}
		  });

