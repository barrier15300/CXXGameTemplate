#pragma once
#include "_structhelper.h"

#include "./Val2D.h"

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

	constexpr Val3D() : x(0), y(0), z(0) {}
	constexpr explicit Val3D(T _all) : x(_all), y(_all), z(_all) {}
	constexpr Val3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3> constexpr Val3D(fT1 ft1, fT2 ft2, fT3 ft3) : x(SCAST(ft1)), y(SCAST(ft2)), z(SCAST(ft3)) {}
	template<IsArithmetic fT> constexpr Val3D(const Val3D<fT> &v) : x(SCAST(v.x)), y(SCAST(v.y)), y(SCAST(v.z)) {}
	template<IsArithmetic fT> constexpr Val3D(Val3D<fT> &&v) : x(SCAST(v.x)), y(SCAST(v.z)) {}

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

	constexpr Val3D operator+() const {
		return *this;
	}
	constexpr Val3D operator-() const {
		Val3D ret;
		for (size_t i = 0, size = arr.size(); i < size; ++i) { ret.arr[i] = -arr[i]; }
		return ret;
	}

	/// <summary>
	/// cast
	/// </summary>

	constexpr operator VECTOR() const {
		union {
			Val3D<float> temp{};
			VECTOR ret;
		};
		temp = *this;
		return ret;
	}

	constexpr operator VECTOR_D() const {
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

	constexpr T &operator[](size_t idx) noexcept {
		return arr[idx];
	}

	constexpr const T &operator[](size_t idx) const noexcept {
		return arr[idx];
	}

	constexpr T &at(size_t idx) {
		return arr.at(idx);
	}

	constexpr const T &at(size_t idx) const {
		return arr.at(idx);
	}

	/// <summary>
	/// vector utility
	/// </summary>

#define MEMBER_SWAP_2D_s1(a, b) constexpr Val2D<T> a##b() const noexcept { return {a, b}; }
#define MEMBER_SWAP_2D_s2(a) MEMBER_SWAP_2D_s1(a, x) MEMBER_SWAP_2D_s1(a, y) MEMBER_SWAP_2D_s1(a, z)
#define MEMBER_SWAP_2D MEMBER_SWAP_2D_s2(x) MEMBER_SWAP_2D_s2(y) MEMBER_SWAP_2D_s2(z)

	MEMBER_SWAP_2D;

#undef MEMBER_SWAP_2D_s1
#undef MEMBER_SWAP_2D_s2
#undef MEMBER_SWAP_2D

#define MEMBER_SWAP_3D_s1(a, b, c) constexpr Val3D a##b##c() const noexcept { return {a, b, c}; }
#define MEMBER_SWAP_3D_s2(a, b) MEMBER_SWAP_3D_s1(a, b, x) MEMBER_SWAP_3D_s1(a, b, y) MEMBER_SWAP_3D_s1(a, b, z)
#define MEMBER_SWAP_3D_s3(a) MEMBER_SWAP_3D_s2(a, x) MEMBER_SWAP_3D_s2(a, y) MEMBER_SWAP_3D_s2(a, z)
#define MEMBER_SWAP_3D MEMBER_SWAP_3D_s3(x) MEMBER_SWAP_3D_s3(y) MEMBER_SWAP_3D_s3(z)

	MEMBER_SWAP_3D;

#undef MEMBER_SWAP_3D_s1
#undef MEMBER_SWAP_3D_s2
#undef MEMBER_SWAP_3D_s3
#undef MEMBER_SWAP_3D

	constexpr T Sum() const noexcept {
		return x + y + z;
	}

	constexpr T Diff() const noexcept {
		return x - y - z;
	}

	constexpr T Mul() const noexcept {
		return x * y * z;
	}

	constexpr T Div() const noexcept {
		return x / y / z;
	}

	FROM_COONVERTIBLE(Val3D)
	constexpr double Dot(fT &&v) const noexcept {
		return Val3D::Dot(*this, std::forward<fT>(v));
	}

	template<class fT>
	constexpr Val3D<std::common_type_t<T, fT>> Cross(const Val3D<fT> &v) const noexcept {
		return Val3D::Cross(*this, v);
	}

	constexpr double Length() const {
		return std::sqrt(this->Dot(*this));
	}

	constexpr Val3D<double> Normalized() const {
		return *this / this->Length();
	}

	// Angle
	constexpr double AngleX() const {
		return this->yz().Angle();
	}
	constexpr double AngleY() const {
		return this->zx().Angle();
	}
	constexpr double AngleZ() const {
		return this->xy().Angle();
	}
	constexpr Val3D<double> Angle() const {
		return {this->AngleX(), this->AngleY(), this->AngleZ()};
	}

	// Rotate
	constexpr Val3D<double> RotateX(double angle) const {
		return Val3D<double>::RotateBase(this->xyz(), angle).xyz();
	}
	constexpr Val3D<double> RotateY(double angle) const {
		return Val3D<double>::RotateBase(this->yxz(), angle).yxz();
	}
	constexpr Val3D<double> RotateZ(double angle) const {
		return Val3D<double>::RotateBase(this->zyx(), angle).zyx();
	}
	constexpr Val3D<double> Rotate(const Val3D<double> &angle) const {
		return this->RotateX(angle.x).RotateY(angle.y).RotateZ(angle.z);
	}


	/// <summary>
	/// static utility
	/// </summary>

	FROM_COONVERTIBLE(Val3D)
	static constexpr double Dot(fT &&lhs, fT &&rhs) noexcept {
		return (lhs * rhs).Sum();
	}

	FROM_COONVERTIBLE(Val3D)
	static constexpr Val3D Cross(fT &&lhs, fT &&rhs) noexcept {
		return (lhs.yzx() * rhs.zxy()) - (lhs.zxy() * rhs.yzx());
	}

	FROM_COONVERTIBLE(Val2D<T>)
	static constexpr double AngleBase(fT &&v) {
		return v.Angle();
	}

	FROM_COONVERTIBLE(Val3D, class floatT = double)
	static constexpr Val3D RotateBase(fT &&v, floatT angle) {
		const std::array<Val3D<floatT>, 3> rotatevector = {
			{
				{1, 0, 0},
				{0, cos(angle), -sin(angle)},
				{0, sin(angle), cos(angle)},
			}
		};
		return {
			(v * rotatevector[0]).Sum(),
			(v * rotatevector[1]).Sum(),
			(v * rotatevector[2]).Sum(),
		};
	}

	FROM_COONVERTIBLE(Val3D)
	static constexpr double Distance(fT &&a, fT &&b) {
		Val3D v = a - b;
		v = v * v;
		return std::sqrt(v.x + v.y);
	}

	FROM_COONVERTIBLE(Val3D, class floatT = double)
	static constexpr Val3D<double> Lerp(fT &&a, fT &&b, floatT t) noexcept {
		return a + (b - a) * t;
	}

	/// <summary>
	/// debug
	/// </summary>

	std::string ToString(int spacewidth = 4, int digit = 6) const {
		return fmt::format("{}{:>{}.{}f}{}", '{', fmt::join(arr, ", "), spacewidth + digit + 1, digit, '}');
	}

	TEMPLATE_ASSINMENT_OPERATOR(Val3D, x, y, z);
};

TEMPLATE_COMPARE_OPERATOR(Val3D, lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);

TEMPLATE_BINARY_OPERATOR(Val3D);

/// <summary>
/// template auto compreation helper
/// </summary>

template<IsArithmetic fT1, IsArithmetic fT2, IsArithmetic fT3> Val3D(fT1, fT2, fT3) -> Val3D<std::common_type_t<fT1, fT2, fT3>>;

/// <summary>
/// json converter
/// </summary>

TO_JSON(template<class T>, Val3D<T>, {
	j = nlohmann::json{v.x, v.y, v.z};
		});

FROM_JSON(template<class T>, Val3D<T>, {
	for (size_t i = 0, size = v.arr.size(); i < size; ++i) {
		j.at(i).get_to(v.arr.at(i));
	}
		  });
