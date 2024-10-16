#pragma once
#include "DxLib.h"
#include "nlohmann/json.hpp"
#include <cmath>
#include <compare>
#include "../template_type.h"
#include "../special.h"

enum class DXHandleType : int {
	None = DX_HANDLETYPE_NONE,
	Graph = DX_HANDLETYPE_GRAPH,
	SoftImage = DX_HANDLETYPE_SOFTIMAGE,
	Sound = DX_HANDLETYPE_SOUND,
	SoftSound = DX_HANDLETYPE_SOFTSOUND,
	Music = DX_HANDLETYPE_MUSIC,
	Movie = DX_HANDLETYPE_MOVIE,
	Mask = DX_HANDLETYPE_GMASK,
	Font = DX_HANDLETYPE_FONT,
	KeyInput = DX_HANDLETYPE_KEYINPUT,
	NetWork = DX_HANDLETYPE_NETWORK,
	Light = DX_HANDLETYPE_LIGHT,
	Shader = DX_HANDLETYPE_SHADER,
	ModelBase = DX_HANDLETYPE_MODEL_BASE,
	Model = DX_HANDLETYPE_MODEL,
	VertexBuffer = DX_HANDLETYPE_VERTEX_BUFFER,
	IndexBuffer = DX_HANDLETYPE_INDEX_BUFFER,
	File = DX_HANDLETYPE_FILE,
	ShadowMap = DX_HANDLETYPE_SHADOWMAP,
	ShaderConstantBuffer = DX_HANDLETYPE_SHADER_CONSTANT_BUFFER,
	Live2DCubism4Model = DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL,
	HandleTypeCount
};

template<DXHandleType handletype>
struct DXHandle {

	DXHandle() : m_handle(-1) {}
	DXHandle(int from) : m_handle(from) {}

	operator const int() {
		return m_handle;
	}
	operator const int() const {
		return m_handle;
	}
	
	int GetLimitHandleCount() const {
		return GetMaxHandleNum(static_cast<int>(m_type));
	}
	int GetUsingHandleCount() const {
		return GetHandleNum(static_cast<int>(m_type));
	}
	int GetAvaliableCount() const {
		return GetUsingHandleCount() - GetLimitHandleCount();
	}

private:
	int m_handle;
	inline static DXHandleType m_type = handletype;
};

template<DXHandleType handletype>
class std::hash<DXHandle<handletype>> {
public:
	size_t operator()(const DXHandle<handletype>& key) const {
		return (size_t)(key);
	}
};

#define TO_JSON(temp, type, ...) \
temp void to_json(nlohmann::json &j, const type &v) __VA_ARGS__ \
temp void to_json(nlohmann::ordered_json &j, const type &v) __VA_ARGS__

#define FROM_JSON(temp, type, ...) \
temp void from_json(const nlohmann::json &j, type &v) __VA_ARGS__ \
temp void from_json(const nlohmann::ordered_json &j, type &v) __VA_ARGS__

#define SCAST(x) static_cast<T>(x)

#define OPERATOR2_BASE(t, type)\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(const t<lfT> &lhs, const t<rfT> &rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(t<lfT> &&lhs, const t<rfT> &rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(const t<lfT> &lhs, t<rfT> &&rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(t<lfT> &&lhs, t<rfT> &&rhs) { return t<rT>(lhs) ##type##= rhs; }\
\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(const t<lfT> &lhs, const rfT &rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(t<lfT> &&lhs, const rfT &rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(const t<lfT> &lhs, rfT &&rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(t<lfT> &&lhs, rfT &&rhs) { return t<rT>(lhs) ##type##= rhs; }

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
	OPERATOR_BASE(/);

};

OPERATOR2_BASE(Val2D, +);
OPERATOR2_BASE(Val2D, -);
OPERATOR2_BASE(Val2D, *);
OPERATOR2_BASE(Val2D, /);

TO_JSON(template<class T>, Val2D<T>, {
	j = nlohmann::json{v.x, v.y};
});

FROM_JSON(template<class T>, Val2D<T>, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr.at(i));
	}
});

/// <summary>
/// Val3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Val3D {

	Val3D() : x(0), y(0), z(0) {}
	Val3D(T &&_x, T &&_y, T &&_z) : x(_x), y(_y), z(_z) {}
	template<IsArithmetic fT_x, IsArithmetic fT_y, IsArithmetic fT_z> Val3D(fT_x &&_x, fT_y &&_y, fT_z &&_z) : x(SCAST(_x)), y(SCAST(_y)), z(SCAST(_z)) {};
	template<IsArithmetic fT> Val3D(const Val3D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), y(SCAST(v.z)) {}
	template<IsArithmetic fT> Val3D(Val3D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.z)) {}

	union {
		struct {
			T x, y, z;
		};
		std::array<T, 3> arr;
	};

	Val3D operator+() const & {
		return *this;
	}
	Val3D operator-() const & {
		Val3D ret;
		for (size_t i = 0, size = this->arr.size(); i < size; ++i) { ret.arr[i] = -this->arr[i]; }
		return ret;
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
	OPERATOR_BASE(/);

};

OPERATOR2_BASE(Val3D, +);
OPERATOR2_BASE(Val3D, -);
OPERATOR2_BASE(Val3D, *);
OPERATOR2_BASE(Val3D, /);

TO_JSON(template<class T>, Val3D<T>, {
	j = nlohmann::json{v.x, v.y, v.z};
});

FROM_JSON(template<class T>, Val3D<T>, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr.at(i));
	}
});

/// <summary>
/// Rect2D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect2D {

	Rect2D() : x(0), y(0), w(0), h(0) {}
	Rect2D(T &&_x, T &&_y, T &&_w, T &&_h) : x(_x), y(_y), w(_w), h(_h) {}
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
	
	explicit operator RECT() {
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

OPERATOR2_BASE(Rect2D, +);
OPERATOR2_BASE(Rect2D, -);
OPERATOR2_BASE(Rect2D, *);
OPERATOR2_BASE(Rect2D, /);

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

/// <summary>
/// Rect3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Rect3D {

	Rect3D() : x(0), y(0), z(0), w(0), h(0), d(0) {}
	Rect3D(T &&_x, T &&_y, T &&_z, T &&_w, T &&_h, T &&_d) : x(_x), y(_y), z(_z), w(_w), h(_h), d(_d) {}
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
	
#define OPERATOR_BASE(type)\
	template<IsArithmetic fT> Rect3D &operator##type##=(const Rect3D<fT> &v) { this->p1 ##type##= v.p1; this->p2 ##type##= v.p2; return *this; }\
	template<IsArithmetic fT> Rect3D &operator##type##=(Rect3D<fT> &&v) { this->p1 ##type##= v.p1; this->p2 ##type##= v.p2; return *this; }\
	\
	template<IsArithmetic fT> Rect3D &operator##type##=(const fT &v) { this->p1 ##type##= v; this->p2 ##type##= v; return *this; }\
	template<IsArithmetic fT> Rect3D &operator##type##=(fT &&v) { this->p1 ##type##= v; this->p2 ##type##= v; return *this; }

	OPERATOR_BASE(+);
	OPERATOR_BASE(-);
	OPERATOR_BASE(*);
	OPERATOR_BASE(/);

};

OPERATOR2_BASE(Rect3D, +);
OPERATOR2_BASE(Rect3D, -);
OPERATOR2_BASE(Rect3D, *);
OPERATOR2_BASE(Rect3D, /);

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

/// <summary>
/// Color3
/// </summary>
struct Color3 {

	Color3() : r(0), g(0), b(0) {}
	Color3(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}

	operator unsigned int() {
		return GetColor(r, g, b);
	}

	union {
		struct {
			int r, g, b;
		};
		std::array<int, 3> arr;
	};
};

TO_JSON(, Color3, {
	j = nlohmann::json{v.r, v.g, v.b};
		});

FROM_JSON(, Color3, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr[i]);
	}
});

#undef SCAST
#undef OPERATOR_BASE
#undef OPERATOR2_BASE
#undef TO_JSON
#undef FROM_JSON