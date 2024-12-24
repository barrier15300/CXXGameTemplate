#pragma once
#include "Val2D.h"

/// <summary>
/// Rect2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect2D {

	Rect2D() : x(0), y(0), w(0), h(0) {}
	Rect2D(T _x, T _y, T _w, T _h) : x(_x), y(_y), w(_w), h(_h) {}
	template<IsArithmetic fT_x, IsArithmetic fT_y, IsArithmetic fT_w, IsArithmetic fT_h> Rect2D(fT_x &&_x, fT_y &&_y, fT_w &&_w, fT_h &&_h) : x(SCAST(_x)), y(SCAST(_y)), w(SCAST(_w)), h(SCAST(_h)) {};
	template<IsArithmetic fT> Rect2D(const Rect2D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), w(SCAST(v.w)), h(SCAST(v.h)) {}
	template<IsArithmetic fT> Rect2D(Rect2D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.y)), w(SCAST(v.w)), h(SCAST(v.h)) {}

	Rect2D(const Val2D<T> &_p1, const Val2D<T> &_p2) : p1(_p1), p2(_p2) {}
	Rect2D(Val2D<T> &&_p1, const Val2D<T> &_p2) : p1(_p1), p2(_p2) {}
	Rect2D(const Val2D<T> &_p1, Val2D<T> &&_p2) : p1(_p1), p2(_p2) {}
	Rect2D(Val2D<T> &&_p1, Val2D<T> &&_p2) : p1(_p1), p2(_p2) {}

	template<IsArithmetic fT1, IsArithmetic fT2> Rect2D(const Val2D<fT1> &_p1, const Val2D<fT2> &_p2) : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2> Rect2D(Val2D<fT1> &&_p1, const Val2D<fT2> &_p2) : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2> Rect2D(const Val2D<fT1> &_p1, Val2D<fT2> &&_p2) : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT1, IsArithmetic fT2> Rect2D(Val2D<fT1> &&_p1, Val2D<fT2> &&_p2) : p1(_p1), p2(_p2) {}

	union {
		struct {
			T x, y, w, h;
		};
		struct {
			Val2D<T> p1, p2;
		};
	};

	explicit operator RECT() const {
		union {
			Rect2D<LONG> temp = Rect2D<LONG>(*this);
			RECT ret;
		};
		return ret;
	}

#define OPERATOR_BASE(type)\
	template<IsArithmetic fT> Rect2D &operator##type##=(const Rect2D<fT> &v) { this->p1 ##type##= v.p1; this->p2 ##type##= v.p2; return *this; }\
	template<IsArithmetic fT> Rect2D &operator##type##=(Rect2D<fT> &&v) { this->p1 ##type##= v.p1; this->p2 ##type##= v.p2; return *this; }\
	\
	template<IsArithmetic fT> Rect2D &operator##type##=(const fT &v) { this->p1 ##type##= v; this->p2 ##type##= v; return *this; }\
	template<IsArithmetic fT> Rect2D &operator##type##=(fT &&v) { this->p1 ##type##= v; this->p2 ##type##= v; return *this; }

	OPERATOR_BASE(+);
	OPERATOR_BASE(-);
	OPERATOR_BASE(*);
	OPERATOR_BASE(/ );

};

TEMPLATE_OPERATOR_BASE(Rect2D, +);
TEMPLATE_OPERATOR_BASE(Rect2D, -);
TEMPLATE_OPERATOR_BASE(Rect2D, *);
TEMPLATE_OPERATOR_BASE(Rect2D, / );

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
