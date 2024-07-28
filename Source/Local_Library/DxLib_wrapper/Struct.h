#pragma once
#include "DxLib.h"
#include "nlohmann/json.hpp"
#include <cmath>
#include <compare>
#include "../template_type.h"
#include "../special.h"

#define TO_JSON(name) {#name, v.name}
#define FROM_JSON(name) j.at(#name).get_to(v.name)

#define COMPOPERATOR_DEF(lvaltype, rvaltype, ...)\
template<__VA_ARGS__> constexpr inline bool operator<(lvaltype lhs, rvaltype rhs) { return MIN; }\
template<__VA_ARGS__> constexpr inline bool operator>(lvaltype lhs, rvaltype rhs) { return rhs < lhs; }\
template<__VA_ARGS__> constexpr inline bool operator<=(lvaltype lhs, rvaltype rhs) { return !(lhs > rhs); }\
template<__VA_ARGS__> constexpr inline bool operator>=(lvaltype lhs, rvaltype rhs) { return !(lhs < rhs); }\
template<__VA_ARGS__> constexpr inline bool operator==(lvaltype lhs, rvaltype rhs) { return !(lhs < rhs) && !(lhs > rhs); }\
template<__VA_ARGS__> constexpr inline bool operator!=(lvaltype lhs, rvaltype rhs) { return !(lhs == rhs); }

#define CONSTRUCTURE_DEF(base, to)\
constexpr to(const to &v) : to::base(v) {}\
constexpr to(to &&v) : to::base(v) {}\
constexpr to(const base<T> &v) : to::base(v) {}\
constexpr to(base<T> &&v) noexcept : to::base(v) {}

/// <summary>
/// Value2D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Value2D

template<IsArithmetic T>
struct Value2D {

	constexpr Value2D() : x(0), y(0) {}
	//constexpr Value2D(const Value2D &v) : x(v.x), y(v.y) {}
	//constexpr Value2D(Value2D &&v) noexcept : x(v.x), y(v.y) {}
	constexpr Value2D(T _x, T _y) : x(_x), y(_y) {}
	template<IsArithmetic fT1, IsArithmetic fT2> constexpr Value2D(fT1 _x, fT2 _y) : x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}
	template<IsArithmetic fpT> constexpr Value2D(const Value2D<fpT> &v) : Value2D(v.x, v.y) {};
	template<IsArithmetic fpT> constexpr Value2D(Value2D<fpT> &&v) : Value2D(v.x, v.y) {};

	T x, y;

	Value2D &&plus() { return Value2D(std::abs(x), std::abs(y)); };
	Value2D &&minus() { return Value2D(-std::abs(x), -std::abs(y)); };

	template<template<IsArithmetic mT> class tT> constexpr inline operator const tT<T> &() {
		return tT<T>(this->x, this->y);
	}

#define OPERATOR_DEF(type, rvaltype) template<IsArithmetic fT> constexpr inline Value2D &operator##type##=(rvaltype rhs) { this->x type##= rhs.x; this->y type##= rhs.y; return *this; };

	OPERATOR_DEF(+, const Value2D<fT> &);
	OPERATOR_DEF(-, const Value2D<fT> &);
	OPERATOR_DEF(*, const Value2D<fT> &);
	OPERATOR_DEF(/, const Value2D<fT> &);
	
	OPERATOR_DEF(+, Value2D<fT> &&);
	OPERATOR_DEF(-, Value2D<fT> &&);
	OPERATOR_DEF(*, Value2D<fT> &&);
	OPERATOR_DEF(/, Value2D<fT> &&);
	
#define OPERATOR_DEF(type, rvaltype) template<IsArithmetic vT> constexpr inline Value2D &operator##type##=(rvaltype rhs) { this->x type##= rhs; this->y type##= rhs; return *this; }

	OPERATOR_DEF(*, const vT &);
	OPERATOR_DEF(/, const vT &);
	OPERATOR_DEF(*,       vT &&);
	OPERATOR_DEF(/,       vT &&);

};

#define OPERATOR_DEF(type, lvalt, rvalt) template<IsArithmetic fT1, IsArithmetic fT2> constexpr inline Value2D<std::common_type_t<fT1, fT2>> operator##type##(lvalt lhs, rvalt rhs) { return Value2D<std::common_type_t<fT1, fT2>>(lhs) type##= rhs; }

OPERATOR_DEF(+, const Value2D<fT1> &,  const Value2D<fT2> &);
OPERATOR_DEF(+,       Value2D<fT1> &&, const Value2D<fT2> &);
OPERATOR_DEF(+, const Value2D<fT1> &,        Value2D<fT2> &&);
OPERATOR_DEF(+,       Value2D<fT1> &&,       Value2D<fT2> &&);

OPERATOR_DEF(-, const Value2D<fT1> &,  const Value2D<fT2> &);
OPERATOR_DEF(-,       Value2D<fT1> &&, const Value2D<fT2> &);
OPERATOR_DEF(-, const Value2D<fT1> &,        Value2D<fT2> &&);
OPERATOR_DEF(-,       Value2D<fT1> &&,       Value2D<fT2> &&);

OPERATOR_DEF(*, const Value2D<fT1> &,  const Value2D<fT2> &);
OPERATOR_DEF(*,       Value2D<fT1> &&, const Value2D<fT2> &);
OPERATOR_DEF(*, const Value2D<fT1> &,        Value2D<fT2> &&);
OPERATOR_DEF(*,       Value2D<fT1> &&,       Value2D<fT2> &&);

OPERATOR_DEF(/, const Value2D<fT1> &,  const Value2D<fT2> &);
OPERATOR_DEF(/,       Value2D<fT1> &&, const Value2D<fT2> &);
OPERATOR_DEF(/, const Value2D<fT1> &,        Value2D<fT2> &&);
OPERATOR_DEF(/,       Value2D<fT1> &&,       Value2D<fT2> &&);

#define OPERATOR_DEF(type, lvalt, rvalt) template<IsArithmetic fT1, IsArithmetic vT> constexpr inline Value2D<std::common_type_t<fT1, vT>> operator##type##(lvalt lhs, rvalt rhs) { return Value2D<std::common_type_t<fT1, vT>>(lhs) type##= rhs; }

OPERATOR_DEF(*, const Value2D<fT1> &,  const vT &);
OPERATOR_DEF(*,       Value2D<fT1> &&, const vT &);
OPERATOR_DEF(*, const Value2D<fT1> &,        vT &&);
OPERATOR_DEF(*,       Value2D<fT1> &&,       vT &&);

OPERATOR_DEF(/, const Value2D<fT1> &,  const vT &);
OPERATOR_DEF(/,       Value2D<fT1> &&, const vT &);
OPERATOR_DEF(/, const Value2D<fT1> &,        vT &&);
OPERATOR_DEF(/,       Value2D<fT1> &&,       vT &&);

#define MIN lhs.x < rhs.x && lhs.y < rhs.y

COMPOPERATOR_DEF(const Value2D<T> &,  const Value2D<T> &,  IsArithmetic T);
COMPOPERATOR_DEF(const Value2D<T> &,        Value2D<T> &&, IsArithmetic T);
COMPOPERATOR_DEF(      Value2D<T> &&, const Value2D<T> &,  IsArithmetic T);

COMPOPERATOR_DEF(const Value2D<fT1> &,  const Value2D<fT2> &,  IsArithmetic fT1, IsArithmetic fT2);
COMPOPERATOR_DEF(const Value2D<fT1> &,        Value2D<fT2> &&, IsArithmetic fT1, IsArithmetic fT2);
COMPOPERATOR_DEF(      Value2D<fT1> &&, const Value2D<fT2> &,  IsArithmetic fT1, IsArithmetic fT2);

#undef MIN

#undef OPERATOR_DEF

#pragma endregion

/// <summary>
/// Pos2D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Pos2D

template<IsArithmetic T>
struct Pos2D : public Value2D<T> {
	using Value2D<T>::Value2D;

	//CONSTRUCTURE_DEF(Value2D, Pos2D);
};
template<IsArithmetic T>
void to_json(nlohmann::json &j, const Pos2D<T> &v) {
	j = nlohmann::json{
		TO_JSON(x),
		TO_JSON(y)
	};
}
template<IsArithmetic T>
void from_json(const nlohmann::json &j, Pos2D<T> &v) {
	FROM_JSON(x);
	FROM_JSON(y);
}

#pragma endregion

/// <summary>
/// Size2D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Size2D

template<IsArithmetic T>
struct Size2D : public Value2D<T> {

	using Value2D<T>::Value2D;

	//CONSTRUCTURE_DEF(Value2D, Size2D);

	rename_member<T> width = rename_member(this->x), height = rename_member(this->y);
};
template<IsArithmetic T>
void to_json(nlohmann::json &j, const Size2D<T> &v) {
	j = nlohmann::json{
		TO_JSON(width),
		TO_JSON(height)
	};
}
template<IsArithmetic T>
void from_json(const nlohmann::json &j, Size2D<T> &v) {
	FROM_JSON(width);
	FROM_JSON(height);
}

#pragma endregion

/// <summary>
/// Rect2D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Rect2D

template<IsArithmetic T>
struct Rect2D {

	Rect2D() : m_P1({}), m_P2({}) {}
	Rect2D(T _left, T _top, T _right, T _bottom) : left(_left), top(_top), right(_right), bottom(_bottom) {};
	template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3, IsArithmetic fT4> Rect2D(fT1 _left, fT2 _top, fT3 _right, fT4 _bottom) : left(static_cast<T>(_left)), top(static_cast<T>(_top)), right(static_cast<T>(_right)), bottom(static_cast<T>(_bottom)) {}
	template<IsArithmetic fpT> Rect2D(const Rect2D<fpT> &v) : Rect2D(v.left, v.top, v.right, v.bottom) {}
	template<IsArithmetic fpT> Rect2D(Rect2D<fpT> &&v) : Rect2D(v.left, v.top, v.right, v.bottom) {}
	template<IsArithmetic fpT> Rect2D(const Value2D<fpT> &p1, const Value2D<fpT> &p2) : m_P1(p1), m_P2(p2) {}
	template<IsArithmetic fpT> Rect2D(Value2D<fpT> &&p1, Value2D<fpT> &&p2) : m_P1(std::move(p1)), m_P2(std::move(p2)) {}

	rename_member<T> left = rename_member(this->m_P1.x), top = rename_member(this->m_P1.y), right = rename_member(m_P2.x), bottom = rename_member(this->m_P2.y);

	template<IsArithmetic fT>
	bool InRect(const Value2D<fT>& pos) {
		Value2D<fT> distance = (this->m_P2 - this->m_P1).plus();
		return pos > Value2D<fT>{0,0} && pos < distance;
	}

#define OPERATOR_DEF(type, rvaltype) inline Rect2D &operator##type##=(rvaltype rhs) { this->left type##= rhs.left; this->top type##= rhs.top; this->right type##= rhs.right; this->bottom type##= rhs.bottom; return *this; };

	constexpr OPERATOR_DEF(+, const Rect2D &);
	constexpr OPERATOR_DEF(-, const Rect2D &);
	constexpr OPERATOR_DEF(*, const Rect2D &);
	constexpr OPERATOR_DEF(/, const Rect2D &);
	constexpr OPERATOR_DEF(,  const Rect2D &);

	constexpr OPERATOR_DEF(+, Rect2D &&);
	constexpr OPERATOR_DEF(-, Rect2D &&);
	constexpr OPERATOR_DEF(*, Rect2D &&);
	constexpr OPERATOR_DEF(/, Rect2D &&);
	constexpr OPERATOR_DEF(,  Rect2D &&);

	template<IsArithmetic fT1> constexpr OPERATOR_DEF(+, const Rect2D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(-, const Rect2D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(*, const Rect2D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(/, const Rect2D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(,  const Rect2D<fT1> &);

	template<IsArithmetic fT1> constexpr OPERATOR_DEF(+, Rect2D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(-, Rect2D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(*, Rect2D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(/, Rect2D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(,  Rect2D<fT1> &&);

#define OPERATOR_DEF(type, rvaltype) inline Rect2D& operator##type##=(rvaltype rhs) { this->left type##= rhs; this->top type##= rhs; this->right type##= rhs; this->bottom type##= rhs; return *this;  }

	template<IsArithmetic vT> constexpr OPERATOR_DEF(*, const vT &);
	template<IsArithmetic vT> constexpr OPERATOR_DEF(/, const vT &);

	template<IsArithmetic vT> constexpr OPERATOR_DEF(*, vT &&);
	template<IsArithmetic vT> constexpr OPERATOR_DEF(/, vT &&);

private:
	Value2D<T> m_P1, m_P2;
};
template<IsArithmetic T>
void to_json(nlohmann::json &j, const Rect2D<T> &v) {
	j = nlohmann::json{
		TO_JSON(left),
		TO_JSON(top),
		TO_JSON(right),
		TO_JSON(bottom)
	};
}
template<IsArithmetic T>
void from_json(const nlohmann::json &j, Rect2D<T> &v) {
	FROM_JSON(left);
	FROM_JSON(top);
	FROM_JSON(right);
	FROM_JSON(bottom);
}

#define OPERATOR_DEF(type) template<IsArithmetic T> constexpr Rect2D<T> &&operator##type##(const Rect2D<T>& lhs, const Rect2D<T>& rhs) { return std::move(Rect2D<T>(lhs) type##= rhs); }

OPERATOR_DEF(+);
OPERATOR_DEF(-);
OPERATOR_DEF(*);
OPERATOR_DEF(/);

#define OPERATOR_DEF(type) template<IsArithmetic fT1, IsArithmetic fT2> constexpr inline Rect2D<std::common_type_t<fT1, fT2>> &&operator##type##(const Rect2D<fT1>& lhs, const Rect2D<fT2>& rhs) { return std::move(Rect2D<std::common_type_t<fT1, fT2>>(lhs) type##= rhs); }

OPERATOR_DEF(+);
OPERATOR_DEF(-);
OPERATOR_DEF(*);
OPERATOR_DEF(/);

#define OPERATOR_DEF(type) template<IsArithmetic T, IsArithmetic vT> constexpr inline Rect2D<std::common_type_t<T, vT>> &&operator##type##(const Rect2D<T>& lhs, vT rhs) { return std::move(Rect2D<std::common_type_t<T, vT>>(lhs) type##= rhs); }

OPERATOR_DEF(*);
OPERATOR_DEF(/);

#undef OPERATOR_DEF

#pragma endregion

/// <summary>
/// Value3D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Value3D

template<IsArithmetic T>
struct Value3D {

	Value3D() : x(0), y(0), z(0) {}
	Value3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3> Value3D(fT1 _x, fT2 _y, fT3 _z) : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)) {}
	template<IsArithmetic fpT> Value3D(const Value3D<fpT> &v) : Value3D(v.x, v.y, v.z) {};
	template<IsArithmetic fpT> Value3D(Value3D<fpT> &&v) : Value3D(v.x, v.y, v.z) {};

	T x, y, z;

	Value3D &&plus() { return Value3D(std::abs(x), std::abs(y), std::abs(z)); };
	Value3D &&minus() { return Value3D(-std::abs(x), -std::abs(y), -std::abs(z)); };

#define OPERATOR_DEF(type, rvaltype) inline Value3D &operator##type##=(rvaltype rhs) { this->x type##= rhs.x; this->y type##= rhs.y; this->z type##= rhs.z; return *this; };

	constexpr OPERATOR_DEF(+, const Value3D &);
	constexpr OPERATOR_DEF(-, const Value3D &);
	constexpr OPERATOR_DEF(*, const Value3D &);
	constexpr OPERATOR_DEF(/, const Value3D &);
	constexpr OPERATOR_DEF(,  const Value3D &);

	constexpr OPERATOR_DEF(+, Value3D &&);
	constexpr OPERATOR_DEF(-, Value3D &&);
	constexpr OPERATOR_DEF(*, Value3D &&);
	constexpr OPERATOR_DEF(/, Value3D &&);
	constexpr OPERATOR_DEF(,  Value3D &&);

	template<IsArithmetic fT> constexpr OPERATOR_DEF(+, const Value3D<fT> &);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(-, const Value3D<fT> &);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(*, const Value3D<fT> &);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(/, const Value3D<fT> &);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(,  const Value3D<fT> &);

	template<IsArithmetic fT> constexpr OPERATOR_DEF(+, Value3D<fT> &&);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(-, Value3D<fT> &&);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(*, Value3D<fT> &&);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(/, Value3D<fT> &&);
	template<IsArithmetic fT> constexpr OPERATOR_DEF(,  Value3D<fT> &&);

#define OPERATOR_DEF(type, rvaltype) inline Value3D& operator##type##=(rvaltype rhs) { this->x type##= rhs; this->y type##= rhs; this->z type##= rhs; return *this; }

	template<IsArithmetic vT> constexpr OPERATOR_DEF(*, const vT &);
	template<IsArithmetic vT> constexpr OPERATOR_DEF(/, const vT &);

	template<IsArithmetic vT> constexpr OPERATOR_DEF(*, vT &&);
	template<IsArithmetic vT> constexpr OPERATOR_DEF(/, vT &&);
};


#define OPERATOR_DEF(type) template<IsArithmetic T> constexpr inline Value3D<T> &&operator##type##(const Value3D<T>& lhs, const Value3D<T>& rhs) { return std::move(Value3D<T>(lhs) type##= rhs); }

OPERATOR_DEF(+);
OPERATOR_DEF(-);
OPERATOR_DEF(*);
OPERATOR_DEF(/);

#define OPERATOR_DEF(type) template<IsArithmetic fT1, IsArithmetic fT2> constexpr inline Value3D<std::common_type_t<fT1, fT2>> &&operator##type##(const Value3D<fT1> &lhs, const Value3D<fT2> &rhs) { return std::move(Value3D<std::common_type_t<fT1, fT2>>(lhs) type##= rhs); }

OPERATOR_DEF(+);
OPERATOR_DEF(-);
OPERATOR_DEF(*);
OPERATOR_DEF(/);

#define OPERATOR_DEF(type) template<IsArithmetic T, IsArithmetic vT> constexpr inline Value3D<std::common_type_t<T, vT>> &&operator##type##(const Value3D<T>& lhs, vT rhs) { return std::move(Value3D<std::common_type_t<T, vT>>(lhs) type##= rhs); }

OPERATOR_DEF(*);
OPERATOR_DEF(/);

#define MIN lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z

COMPOPERATOR_DEF(const Value3D<T> &,  const Value3D<T> &,  IsArithmetic T);
COMPOPERATOR_DEF(const Value3D<T> &,        Value3D<T> &&, IsArithmetic T);
COMPOPERATOR_DEF(      Value3D<T> &&, const Value3D<T> &,  IsArithmetic T);

COMPOPERATOR_DEF(const Value3D<fT1> &,  const Value3D<fT2> &,  IsArithmetic fT1, IsArithmetic fT2);
COMPOPERATOR_DEF(const Value3D<fT1> &,        Value3D<fT2> &&, IsArithmetic fT1, IsArithmetic fT2);
COMPOPERATOR_DEF(      Value3D<fT1> &&, const Value3D<fT2> &,  IsArithmetic fT1, IsArithmetic fT2);

#undef MIN

#undef OPERATOR_DEF

#pragma endregion

/// <summary>
/// Pos3D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Pos3D

template<IsArithmetic T>
struct Pos3D : public Value3D<T> {
	using Value3D<T>::Value3D;

	CONSTRUCTURE_DEF(Value3D, Pos3D);
};
template<IsArithmetic T>
void to_json(nlohmann::json &j, const Pos3D<T> &v) {
	j = nlohmann::json{
		TO_JSON(x),
		TO_JSON(y),
		TO_JSON(z)
	};
}
template<IsArithmetic T>
void from_json(const nlohmann::json &j, Pos3D<T> &v) {
	FROM_JSON(x);
	FROM_JSON(y);
	FROM_JSON(z);
}

#pragma endregion

/// <summary>
/// Size3D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Size3D

template<IsArithmetic T>
struct Size3D : private Value3D<T> {

	using Value3D<T>::Value3D;

	CONSTRUCTURE_DEF(Value3D, Size3D);

	rename_member<T> width = rename_member(this->x), height = rename_member(this->y), depth = rename_member(this->z);
};
template<IsArithmetic T>
void to_json(nlohmann::json &j, const Size3D<T> &v) {
	j = nlohmann::json{
		TO_JSON(width),
		TO_JSON(height),
		TO_JSON(depth)
	};
}
template<IsArithmetic T>
void from_json(const nlohmann::json &j, Size3D<T> &v) {
	FROM_JSON(width);
	FROM_JSON(height);
	FROM_JSON(depth);
}

#pragma endregion

/// <summary>
/// Rect3D
/// </summary>
/// <typeparam name="T"></typeparam>
#pragma region Rect3D

template<IsArithmetic T>
struct Rect3D {

	Rect3D() : m_P1({}), m_P2({}) {}
	Rect3D(T _left, T _top, T _front, T _right, T _bottom, T _back) : left(_left), top(_top), front(_front), right(_right), bottom(_bottom) , back(_back) {};
	template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3, IsArithmetic fT4, IsArithmetic fT5, IsArithmetic fT6> Rect3D(fT1 _left, fT2 _top, fT3 _front, fT4 _right, fT5 _bottom, fT6 &&_back) : left(static_cast<T>(_left)), top(static_cast<T>(_top)), front(static_cast<T>(_front)), right(static_cast<T>(_right)), bottom(static_cast<T>(_bottom)), back(static_cast<T>(_back)) {}
	template<IsArithmetic fpT> Rect3D(const Rect3D<fpT> &v) : Rect3D(v.left, v.top, v.front, v.right, v.bottom, v.back) {}
	template<IsArithmetic fpT> Rect3D(Rect3D<fpT> &&v) : Rect3D(v.left, v.top, v.front, v.right, v.bottom, v.back) {}
	template<IsArithmetic fpT> Rect3D(const Value3D<fpT> &p1, const Value3D<fpT> &p2) : m_P1(p1), m_P2(p2) {}
	template<IsArithmetic fpT> Rect3D(Value3D<fpT> &&p1, Value3D<fpT> &&p2) : m_P1(std::move(p1)), m_P2(std::move(p2)) {}

	rename_member<T> left = rename_member(m_P1.x), top = rename_member(m_P1.y), front = rename_member(m_P1.z), right = rename_member(m_P1.x), bottom = rename_member(m_P2.y), back = rename_member(m_P2.z);

	template<IsArithmetic fT>
	bool InRect(const Value3D<fT> &pos) {
		Value3D<fT> distance = (this->m_P2 - this->m_P1).plus();
		return pos > Value3D<fT>{0, 0, 0} && pos < distance;
	}

#define OPERATOR_DEF(type, rvaltype) inline Rect3D &operator##type##=(rvaltype rhs) { this->left type##= rhs.left; this->top type##= rhs.top; this->front type##= rhs.front; this->right type##= rhs.right; this->bottom type##= rhs.bottom; this->back type##= rhs.back; return *this; };

	constexpr OPERATOR_DEF(+, const Rect3D &);
	constexpr OPERATOR_DEF(-, const Rect3D &);
	constexpr OPERATOR_DEF(*, const Rect3D &);
	constexpr OPERATOR_DEF(/, const Rect3D &);
	constexpr OPERATOR_DEF(, const Rect3D &);

	constexpr OPERATOR_DEF(+, Rect3D &&);
	constexpr OPERATOR_DEF(-, Rect3D &&);
	constexpr OPERATOR_DEF(*, Rect3D &&);
	constexpr OPERATOR_DEF(/, Rect3D &&);
	constexpr OPERATOR_DEF(, Rect3D &&);

	template<IsArithmetic fT1> constexpr OPERATOR_DEF(+, const Rect3D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(-, const Rect3D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(*, const Rect3D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(/, const Rect3D<fT1> &);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(, const Rect3D<fT1> &);

	template<IsArithmetic fT1> constexpr OPERATOR_DEF(+, Rect3D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(-, Rect3D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(*, Rect3D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(/, Rect3D<fT1> &&);
	template<IsArithmetic fT1> constexpr OPERATOR_DEF(, Rect3D<fT1> &&);

#define OPERATOR_DEF(type, rvaltype) inline Rect3D& operator##type##=(rvaltype rhs) { this->left type##= rhs; this->top type##= rhs; this->front type##= rhs; this->right type##= rhs; this->bottom type##= rhs; this->back type##= rhs; return *this; }

	template<IsArithmetic vT> constexpr OPERATOR_DEF(*, const vT &);
	template<IsArithmetic vT> constexpr OPERATOR_DEF(/, const vT &);

	template<IsArithmetic vT> constexpr OPERATOR_DEF(*, vT &&);
	template<IsArithmetic vT> constexpr OPERATOR_DEF(/, vT &&);

private:
	Value3D<T> m_P1, m_P2;
};
template<IsArithmetic T>
void to_json(nlohmann::json &j, const Rect3D<T> &v) {
	j = nlohmann::json{
		TO_JSON(left),
		TO_JSON(top),
		TO_JSON(front),
		TO_JSON(right),
		TO_JSON(bottom),
		TO_JSON(back)
	};
}
template<IsArithmetic T>
void from_json(const nlohmann::json &j, Rect3D<T> &v) {
	FROM_JSON(left);
	FROM_JSON(top);
	FROM_JSON(front);
	FROM_JSON(right);
	FROM_JSON(bottom);
	FROM_JSON(back);
}

#define OPERATOR_DEF(type) template<IsArithmetic T> constexpr inline Rect3D<T> &&operator##type##(const Rect3D<T>& lhs, const Rect3D<T>& rhs) { return Rect3D<T>(lhs) type##= rhs; }

OPERATOR_DEF(+);
OPERATOR_DEF(-);
OPERATOR_DEF(*);
OPERATOR_DEF(/);

#define OPERATOR_DEF(type) template<IsArithmetic fT1, IsArithmetic fT2> constexpr inline Rect3D<std::common_type_t<fT1, fT2>> &&operator##type##(const Rect3D<fT1>& lhs, const Rect3D<fT2>& rhs) { return Rect3D<std::common_type_t<fT1, fT2>>(lhs) type##= rhs; }

OPERATOR_DEF(+);
OPERATOR_DEF(-);
OPERATOR_DEF(*);
OPERATOR_DEF(/);

#define OPERATOR_DEF(type) template<IsArithmetic T, IsArithmetic vT> constexpr inline Rect3D<T> &&operator##type##(const Rect3D<T>& lhs, vT rhs) { return Rect3D<T>(lhs) type##= rhs; }

OPERATOR_DEF(*);
OPERATOR_DEF(/);

#undef OPERATOR_DEF

#pragma endregion

/// <summary>
/// Color3
/// </summary>
#pragma region Color3

struct Color3 {
	Color3() : r(0), g(0), b(0) {}
	Color3(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}
	Color3(unsigned int _color) { GetColor2(_color, &r, &g, &b); }

	operator unsigned int() {
		return GetColor(r, g, b);
	}

	int r, g, b;
};

#pragma endregion

/// <summary>
/// Color4
/// </summary>
#pragma region Color4

struct Color4 {
	Color4() : r(0), g(0), b(0) {}
	Color4(byte _r, byte _g, byte _b, byte _a) : r(_r), g(_g), b(_b), a(_a) {}

	operator COLOR_U8() {
		return GetColorU8(r, g, b, a);
	}

	byte r, g, b, a;
};

#pragma endregion

#undef OPERATOR_DEF
#undef COMPOPERATOR_DEF
#undef CONSTRUCTURE_DEF

#undef TO_JSON
#undef FROM_JSON