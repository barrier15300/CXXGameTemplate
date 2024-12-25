#pragma once
#include "Val3D.h"

/// <summary>
/// Rect3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect3D {

	Rect3D() : x(0), y(0), z(0), w(0), h(0), d(0) {}
	Rect3D(T _x, T _y, T _z, T _w, T _h, T _d) : x(_x), y(_y), z(_z), w(_w), h(_h), d(_d) {}
	template<IsArithmetic fT_x, IsArithmetic fT_y, IsArithmetic fT_z, IsArithmetic fT_w, IsArithmetic fT_h, IsArithmetic fT_d> Rect3D(fT_x &&_x, fT_y &&_y, fT_z &&_z, fT_w &&_w, fT_h &&_h, fT_d &&_d) : x(SCAST(_x)), y(SCAST(_y)), z(SCAST(_z)), w(SCAST(_w)), h(SCAST(_h)), d(SCAST(_d)) {};
	template<IsArithmetic fT> Rect3D(const Rect3D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)), w(SCAST(v.w)), h(SCAST(v.h)), d(SCAST(v.d)) {}
	template<IsArithmetic fT> Rect3D(Rect3D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)), w(SCAST(v.w)), h(SCAST(v.h)), d(SCAST(v.d)) {}

	Rect3D(const Val3D<T> &_p1, const Val3D<T> &_p2) : p1(_p1), p2(_p2) {}
	Rect3D(Val3D<T> &&_p1, const Val3D<T> &_p2) : p1(_p1), p2(_p2) {}
	Rect3D(const Val3D<T> &_p1, Val3D<T> &&_p2) : p1(_p1), p2(_p2) {}
	Rect3D(Val3D<T> &&_p1, Val3D<T> &&_p2) : p1(_p1), p2(_p2) {}

	template<IsArithmetic fT1, IsArithmetic fT2> Rect3D(const Val3D<fT1> &_p1, const Val3D<fT2> &_p2) : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2> Rect3D(Val3D<fT1> &&_p1, const Val3D<fT2> &_p2) : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2> Rect3D(const Val3D<fT1> &_p1, Val3D<fT2> &&_p2) : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2> Rect3D(Val3D<fT1> &&_p1, Val3D<fT2> &&_p2) : p1(_p1), p2(_p2) {}

	union {
		struct {
			T x, y, z, w, h, d;
		};
		struct {
			Val3D<T> p1, p2;
		};
	};

	std::string ToString(int digit = 6) {
		return fmt::format("{}{}, {}{}", '{', p1.ToString(), p2.ToString(), '}');
	}

#define OPERATOR_BASE(type)\
	template<IsArithmetic fT> Rect3D &operator##type##=(const Rect3D<fT> &v) { this->p1 ##type##= v.p1; this->p2 ##type##= v.p2; return *this; }\
	template<IsArithmetic fT> Rect3D &operator##type##=(Rect3D<fT> &&v) { this->p1 ##type##= v.p1; this->p2 ##type##= v.p2; return *this; }\
	\
	template<IsArithmetic fT> Rect3D &operator##type##=(const fT &v) { this->p1 ##type##= v; this->p2 ##type##= v; return *this; }\
	template<IsArithmetic fT> Rect3D &operator##type##=(fT &&v) { this->p1 ##type##= v; this->p2 ##type##= v; return *this; }

	OPERATOR_BASE(+);
	OPERATOR_BASE(-);
	OPERATOR_BASE(*);
	OPERATOR_BASE(/ );

};

TEMPLATE_OPERATOR_BASE(Rect3D, +);
TEMPLATE_OPERATOR_BASE(Rect3D, -);
TEMPLATE_OPERATOR_BASE(Rect3D, *);
TEMPLATE_OPERATOR_BASE(Rect3D, / );

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

