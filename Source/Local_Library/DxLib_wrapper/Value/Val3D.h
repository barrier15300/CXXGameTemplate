#pragma once
#include "_structhelper.h"

/// <summary>
/// Val3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<IsArithmetic T>
struct Val3D {

	using value_type = T;

	/// <summary>
	/// constructor
	/// </summary>

	Val3D() : x(0), y(0), z(0) {}
	Val3D(T _all) : x(_all), y(_all), z(_all) {}
	Val3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3> Val3D(fT1 ft1, fT2 ft2, fT3 ft3) : x(SCAST(ft1)), y(SCAST(ft2)), z(SCAST(ft3)) {}
	template<IsArithmetic fT> Val3D(const Val3D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), y(SCAST(v.z)) {}
	template<IsArithmetic fT> Val3D(Val3D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.z)) {}

	/// <summary>
	/// union member
	/// </summary>

	union {
		struct {
			T x, y, z;
		};
		struct {
			std::array<T, 3> arr;
		};
	};

	/// <summary>
	/// unary operator
	/// </summary>

	Val3D operator+() const {
		return *this;
	}
	Val3D operator-() const {
		Val3D ret;
		for (size_t i = 0, size = arr.size(); i < size; ++i) { ret.arr[i] = -arr[i]; }
		return ret;
	}

	/// <summary>
	/// cast
	/// </summary>

	operator VECTOR() const {
		union {
			Val3D<float> temp{};
			VECTOR ret;
		};
		temp = *this;
		return ret;
	}

	operator VECTOR_D() const {
		union {
			Val3D<double> temp{};
			VECTOR_D ret;
		};
		temp = *this;
		return ret;
	}

	/// <summary>
	/// arr accessor
	/// </summary>

	T &operator[](size_t idx) {
		return arr[idx];
	}

	const T &operator[](size_t idx) const {
		return arr[idx];
	}

	T &at(size_t idx) {
		if (idx >= arr.size()) throw std::out_of_range("Index out of range");
		return arr[idx];
	}

	const T &at(size_t idx) const {
		if (idx >= arr.size()) throw std::out_of_range("Index out of range");
		return arr[idx];
	}

	/// <summary>
	/// vector utility
	/// </summary>

#define MEMBER_SWAP_2D_s1(a, b) Val2D<T> a##b() const { return {a, b}; }
#define MEMBER_SWAP_2D_s2(a) MEMBER_SWAP_2D_s1(a, x) MEMBER_SWAP_2D_s1(a, y) MEMBER_SWAP_2D_s1(a, z)
#define MEMBER_SWAP_2D MEMBER_SWAP_2D_s2(x) MEMBER_SWAP_2D_s2(y) MEMBER_SWAP_2D_s2(z)

	MEMBER_SWAP_2D;

#undef MEMBER_SWAP_2D_s1
#undef MEMBER_SWAP_2D_s2
#undef MEMBER_SWAP_2D

#define MEMBER_SWAP_3D_s1(a, b, c) Val3D a##b##c() const { return {a, b, c}; }
#define MEMBER_SWAP_3D_s2(a, b) MEMBER_SWAP_3D_s1(a, b, x) MEMBER_SWAP_3D_s1(a, b, y) MEMBER_SWAP_3D_s1(a, b, z)
#define MEMBER_SWAP_3D_s3(a) MEMBER_SWAP_3D_s2(a, x) MEMBER_SWAP_3D_s2(a, y) MEMBER_SWAP_3D_s2(a, z)
#define MEMBER_SWAP_3D MEMBER_SWAP_3D_s3(x) MEMBER_SWAP_3D_s3(y) MEMBER_SWAP_3D_s3(z)

	MEMBER_SWAP_3D;

#undef MEMBER_SWAP_3D_s1
#undef MEMBER_SWAP_3D_s2
#undef MEMBER_SWAP_3D_s3
#undef MEMBER_SWAP_3D

	T Sum() const {
		return x + y + z;
	}

	T Diff() const {
		return x - y - z;
	}

	template<class fT>
	double Dot(const Val3D<fT> &v) const {
		return Val3D::Dot(*this, v);
	}

	template<class fT>
	Val3D<std::common_type_t<T, fT>> Cross(const Val3D<fT> &v) const {
		return Val3D::Cross(*this, v);
	}

	double Length() const {
		return std::sqrt(this->Dot(*this));
	}

	Val3D<double> Normalized() const {
		return *this / this->Length();
	}

	double Angle() const {
		return std::atan2(y, x);
	}

	double Angle(const Val3D &v) const {
		return Val3D::Angle(*this, v);
	}

	Val3D<double> Rotate(double angle) const {
		auto rotatevector = Val3D<double>{sin(angle),cos(angle)};
		return {this->Cross(rotatevector),this->Dot(rotatevector)};
	}

	/// <summary>
	/// static utility
	/// </summary>

	static double Dot(const Val3D &lhs, const Val3D &rhs) {
		return (lhs * rhs).Sum();
	}

	static Val3D Cross(const Val3D &lhs, const Val3D &rhs) {
		return (lhs.yzx() * rhs.zxy()) - (lhs.zxy() * rhs.yzx());
	}

	static double Angle(const Val3D &lhs, const Val3D &rhs) {
		return std::atan2(Cross(lhs, rhs), Dot(lhs, rhs));
	}

	static Val2D<double> Intersection(const std::pair<Val3D, Val3D> &l1, const std::pair<Val3D, Val3D> &l2) {
		double s, t, deno = Cross(l1.second - l1.first, l2.second - l2.first);
		Val3D<double> error{INFINITY,INFINITY};

		if (deno == 0) {
			return error;
		}

		s = Val3D::Cross(l2.first - l1.first, l2.second - l2.first) / deno;
		t = Val3D::Cross(l1.second - l1.first, l1.first - l2.first) / deno;

		if (s < 0 || 1 < s || t < 0 || 1 < t) {
			return error;
		}

		return l1.first + s * (l1.second - l1.first);
	}

	static double Distance(const Val3D &a, const Val3D &b) {
		Val3D v = a - b;
		v = v * v;
		return std::sqrt(v.x + v.y);
	}

	static Val3D<double> Lerp(const Val3D &a, const Val3D &b, double t) {
		return a + (b - a) * t;
	}

	/// <summary>
	/// debug
	/// </summary>

	std::string ToString(int spacewidth = 4, int digit = 6) const {
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

/// <summary>
/// template auto compreation helper
/// </summary>

template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3> Val3D(fT1, fT2, fT3) -> Val3D<std::common_type_t<fT1, fT2, fT3>>;


COMPARE_OPERATOR_BASE(Val3D, lhs.x < rhs.x &&lhs.y < rhs.y &&lhs.z < rhs.z);

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
