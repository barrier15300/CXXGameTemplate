#pragma once
#include "../Helper/JsonHelper.h"
#include "../Helper/StructHelper.h"
#include <array>

/// <summary>
/// Val3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Val3D {

	Val3D() : x(0), y(0), z(0) {}
	Val3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	template<IsArithmetic fT_x, IsArithmetic fT_y, IsArithmetic fT_z> Val3D(fT_x &&_x, fT_y &&_y, fT_z &&_z) : x(SCAST(_x)), y(SCAST(_y)), z(SCAST(_z)) {};
	template<IsArithmetic fT> Val3D(const Val3D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), y(SCAST(v.z)) {}
	template<IsArithmetic fT> Val3D(Val3D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.z)) {}

	union {
		struct {
			T x, y, z;
		};
		std::array<T, 3> arr;
	};

	Val3D operator+() const {
		return *this;
	}
	Val3D operator-() const {
		Val3D ret;
		for (size_t i = 0, size = this->arr.size(); i < size; ++i) { ret.arr[i] = -this->arr[i]; }
		return ret;
	}

	std::string ToString(int digit = 6) {
		std::stringstream buf;
		buf.precision(digit);
		buf << "{" << x << ", " << y << ", " << z << "}";
		return buf.str();
	}

#define OPERATOR_BASE(type)\
	template<IsArithmetic fT> Val3D &operator##type##=(const Val3D<fT> &v) { this->x ##type##= v.x; this->y ##type##= v.y; this->z ##type##= v.z; return *this; }\
	template<IsArithmetic fT> Val3D &operator##type##=(Val3D<fT> &&v) { this->x ##type##= v.x; this->y ##type##= v.y; this->z ##type##= v.z;  return *this; }\
	\
	template<IsArithmetic fT> Val3D &operator##type##=(const fT &v) { this->x ##type##= v; this->y ##type##= v; this->z ##type##= v; return *this; }\
	template<IsArithmetic fT> Val3D &operator##type##=(fT &&v) { this->x ##type##= v; this->y ##type##= v; this->z ##type##= v; return *this; }

	OPERATOR_BASE(+);
	OPERATOR_BASE(-);
	OPERATOR_BASE(*);
	OPERATOR_BASE(/ );

};

TEMPLATE_OPERATOR_BASE(Val3D, +);
TEMPLATE_OPERATOR_BASE(Val3D, -);
TEMPLATE_OPERATOR_BASE(Val3D, *);
TEMPLATE_OPERATOR_BASE(Val3D, / );

TO_JSON(template<class T>, Val3D<T>, {
	j = nlohmann::json{v.x, v.y, v.z};
		});

FROM_JSON(template<class T>, Val3D<T>, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr.at(i));
	}
		  });
