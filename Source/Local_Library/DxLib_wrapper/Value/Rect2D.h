﻿#pragma once
#include "Val2D.h"

/// <summary>
/// Rect2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect2D {

	using value_type = T;

	Rect2D() : x(0), y(0), w(0), h(0) {}
	Rect2D(T _x, T _y, T _w, T _h) : x(_x), y(_y), w(_w), h(_h) {}
	Rect2D(Val2D<T> _p1, Val2D<T> _p2) : p1(_p1), p2(_p2) {}
	template<IsArithmetic fT> Rect2D(const Rect2D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), w(SCAST(v.w)), h(SCAST(v.h)) {}
	template<IsArithmetic fT> Rect2D(Rect2D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.y)), w(SCAST(v.w)), h(SCAST(v.h)) {}
	
	union {
		struct {
			T x, y, w, h;
		};
		struct {
			Val2D<T> p1, p2;
		};
	};

	operator RECT() const {
		union {
			Rect2D<LONG> temp{};
			RECT ret;
		};
		temp = *this;
		return ret;
	}

	template<IsArithmetic fT>
	bool InRect(const Val2D<fT>& pos) {
		Rect2D<fT> rect = {
			min(this->p1.x, this->p2.x), max(this->p1.x, this->p1.x),
			min(this->p1.y, this->p2.y), max(this->p1.y, this->p1.y)
		};
		return rect.p1 <= pos && rect.p2 >= pos;
	}

	std::string ToString(int digit = 6) const {
		return fmt::format("{}{}, {}{}", '{', p1.ToString(), p2.ToString(), '}');
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

/// <summary>
/// template auto compreation helper
/// </summary>

template<IsArithmetic fT1,IsArithmetic fT2,IsArithmetic fT3,IsArithmetic fT4> Rect2D(fT1,fT2,fT3,fT4) -> Rect2D<std::common_type_t<fT1,fT2,fT3,fT4>>;
template<class fT1, class fT2> Rect2D(fT1,fT2) -> Rect2D<std::common_type_t<typename fT1::value_type, typename fT2::value_type>>;


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
