#pragma once
#include "_structhelper.h"

/// <summary>
/// Val3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Val3D {

	/// <summary>
	/// constructor
	/// </summary>

	Val3D() : x(0), y(0), z(0) {}
	Val3D(T _all) : x(_all), y(_all), z(_all) {}
	Val3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	template<IsArithmetic fT_x, IsArithmetic fT_y, IsArithmetic fT_z> Val3D(fT_x &&_x, fT_y &&_y, fT_z &&_z) : x(SCAST(_x)), y(SCAST(_y)), z(SCAST(_z)) {};
	template<IsArithmetic fT> Val3D(const Val3D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), y(SCAST(v.z)) {}
	template<IsArithmetic fT> Val3D(Val3D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.z)) {}

	/// <summary>
	/// union member
	/// </summary>

	union {
		struct {
			T x, y, z;
		};
		std::array<T, 3> arr;
	};

	/// <summary>
	/// unary operator
	/// </summary>

	Val3D operator+() const {
		return *this;
	}
	Val3D operator-() const {
		Val3D ret;
		for (size_t i = 0, size = this->arr.size(); i < size; ++i) { ret.arr[i] = -this->arr[i]; }
		return ret;
	}

	/// <summary>
	/// cast
	/// </summary>

	operator VECTOR() const {
		union {
			Val3D<float> temp = Val3D<float>(*this);
			VECTOR ret;
		};
		return ret;
	}

	operator VECTOR_D() const {
		union {
			Val3D<double> temp = Val3D<double>(*this);
			VECTOR ret;
		};
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
		if(idx >= arr.size()) throw std::out_of_range("Index out of range");
		return arr[idx];
	}

	const T& at(size_t idx) const {
		if(idx >= arr.size()) throw std::out_of_range("Index out of range");
		return arr[idx];
	}

	/// <summary>
	/// vector utility
	/// </summary>

	double Length() const {
		return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	Val3D<double> Norm() const {
		double len = Length();
		return Val3D<double>(x / len, y / len, z / len);
	}

	/// <summary>
	/// static utility
	/// </summary>

	static T Distance(const Val3D &a,const Val3D &b) {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	}

	static Val3D<double> Lerp(const Val3D &a,const Val3D &b,double t) {
		return a + (b - a) * t;
	}

	/// <summary>
	/// debug
	/// </summary>

	std::string ToString(int spacewidth = 4, int digit = 6) {
		return fmt::format("{}{:>{}.{}f}{}", '{', fmt::join(arr, ", "), spacewidth + digit + 1, digit, '}');
	}

#define OPERATOR_BASE(type)\
	template<IsArithmetic fT> Val3D &operator##type##=(const Val3D<fT> &v) { this->x ##type##= v.x; this->y ##type##= v.y; this->z ##type##= v.z; return *this; }\
	template<IsArithmetic fT> Val3D &operator##type##=(Val3D<fT> &&v) { this->x ##type##= v.x; this->y ##type##= v.y; this->z ##type##= v.z;  return *this; }

	OPERATOR_BASE(+);
	OPERATOR_BASE(-);
	OPERATOR_BASE(*);
	OPERATOR_BASE(/ );

};

COMPARE_OPERATOR_BASE(Val3D, lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);

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
