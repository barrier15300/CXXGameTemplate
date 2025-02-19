#pragma once
#include "Val3D.h"

/// <summary>
/// Rect3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect3D {

	using value_type = T;

	Rect3D() : x(0), y(0), z(0), w(0), h(0), d(0) {}
	Rect3D(T _x, T _y, T _z, T _w, T _h, T _d) : x(_x), y(_y), z(_z), w(_w), h(_h), d(_d) {}
	Rect3D(Val3D<T> _p1, Val3D<T> _p2): p1(_p1),p2(_p2) {}
	template<IsArithmetic fT> Rect3D(const Rect3D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)), w(SCAST(v.w)), h(SCAST(v.h)), d(SCAST(v.d)) {}
	template<IsArithmetic fT> Rect3D(Rect3D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)), w(SCAST(v.w)), h(SCAST(v.h)), d(SCAST(v.d)) {}

	union {
		struct {
			T x, y, z, w, h, d;
		};
		struct {
			Val3D<T> p1, p2;
		};
	};

	template<IsArithmetic fT>
	bool InRect(const Val3D<fT>& pos) {
		Rect3D<fT> rect = {
			min(this->p1.x, this->p2.x), max(this->p1.x, this->p1.x),
			min(this->p1.y, this->p2.y), max(this->p1.y, this->p1.y),
			min(this->p1.z, this->p2.z), max(this->p1.z, this->p1.z)
		};
		return rect.p1 <= pos && rect.p2 >= pos;
	}

	std::string ToString(int digit = 6) const {
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

// <summary>
/// template auto compreation helper
/// </summary>

template<IsArithmetic fT1,IsArithmetic fT2,IsArithmetic fT3,IsArithmetic fT4,IsArithmetic fT5,IsArithmetic fT6> Rect3D(fT1,fT2,fT3,fT4,fT5,fT6) -> Rect3D<std::common_type_t<fT1,fT2,fT3,fT4,fT5,fT6>>;
template<class fT1,class fT2> Rect3D(fT1,fT2) -> Rect3D<std::common_type_t<typename fT1::value_type,typename fT2::value_type>>;


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

