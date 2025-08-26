#pragma once
#include "Common.h"

#include "Val2D.h"

/// <summary>
/// Val3D
/// </summary>
/// <typeparam name="T"></typeparam>
template<typeis::Arithmetic T>
struct Val3D {

	DEFINE_TRAITS(Val3D);

	/// <summary>
	/// constructor
	/// </summary>

	constexpr Val3D() : x(0), y(0), z(0) {}
	constexpr explicit Val3D(T _all) : x(_all), y(_all), z(_all) {}
	constexpr Val3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3> constexpr Val3D(fT1 ft1, fT2 ft2, fT3 ft3) : x(SCAST(ft1)), y(SCAST(ft2)), z(SCAST(ft3)) {}
	template<typeis::Arithmetic fromT> constexpr Val3D(LcvrFrom<fromT> v) : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)) {}
	template<typeis::Arithmetic fromT> constexpr Val3D(RvrFrom<fromT> v) : x(SCAST(v.x)), y(SCAST(v.y)), z(SCAST(v.z)) {}
	template<typeis::Arithmetic fromT> constexpr Val3D(const std::initializer_list<fromT>& list) {
		if (list.size() != 3) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), arr.begin());
	}
	template<typeis::Arithmetic fromT> constexpr Val3D(std::initializer_list<fromT>&& list) {
		if (list.size() != 3) {
			throw std::invalid_argument("Initializer list must contain exactly two elements.");
		}
		std::copy(list.begin(), list.end(), arr.begin());
	}

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

	constexpr operator std::tuple<T, T, T>() const {
		return {x, y, z};
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

	constexpr double Dot(Lcvr v) const noexcept {
		return Val3D::Dot(*this, v);
	}

	constexpr Val3D Cross(Lcvr v) const noexcept {
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

	static constexpr double Dot(Lcvr lhs, Lcvr rhs) noexcept {
		return (lhs * rhs).Sum();
	}

	static constexpr Val3D Cross(Lcvr lhs, Lcvr rhs) noexcept {
		return (lhs.yzx() * rhs.zxy()) - (lhs.zxy() * rhs.yzx());
	}

	template<typeis::Arithmetic floatT = double>
	static constexpr Val3D RotateBase(Lcvr v, floatT angle) {
		std::array<Val3D<floatT>, 3> rotatevector = {
			{
				{1, 0, 0},
				{0, cos(angle), -sin(angle)},
				{0, sin(angle), cos(angle)},
			}
		};
		return {
			Val3D::Dot(v, rotatevector[0]),
			Val3D::Dot(v, rotatevector[1]),
			Val3D::Dot(v, rotatevector[2])
		};
	}

	static constexpr double Distance(Lcvr a, Lcvr b) {
		Val3D v = a - b;
		v = v * v;
		return std::sqrt(v.x + v.y);
	}

	template<typeis::Arithmetic floatT = double>
	static constexpr Val3D<double> Lerp(Lcvr a, Lcvr b, floatT t) noexcept {
		return a + (b - a) * t;
	}

	/// <summary>
	/// debug
	/// </summary>

	std::string ToString(int spacewidth = 4, int digit = 6) const {
		return fmt::format("{}{:>{}.{}f}{}", '{', fmt::join(arr, ", "), spacewidth + digit + 1, digit, '}');
	}

	/// <summary>
	/// operator
	/// </summary>

	TEMPLATE_ASSIGNMENT_OPERATOR(Val3D, x, y, z);

};

TEMPLATE_COMPARE_OPERATOR(Val3D, lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);

TEMPLATE_BINARY_OPERATOR(Val3D);

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

/// <summary>
/// template auto compreation helper
/// </summary>

template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3> Val3D(fT1, fT2, fT3) -> Val3D<std::common_type_t<fT1, fT2, fT3>>;
template<typeis::Arithmetic fromT> Val3D(std::initializer_list<fromT>) -> Val3D<fromT>;

