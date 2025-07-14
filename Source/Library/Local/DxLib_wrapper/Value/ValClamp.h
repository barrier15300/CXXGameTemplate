#pragma once

#include "Common.h"

/// <summary>
/// ValClamp
/// </summary>
template<typeis::Arithmetic T>
struct ValClamp {
	
	constexpr ValClamp() noexcept = default;
	constexpr ValClamp(T _val, T _min, T _max) : val(_val), min(_min), max(_max) { check_error(); clamp(); }
	template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3> constexpr ValClamp(fT1 _val, fT2 _min, fT3 _max) : val(SCAST(_val)), min(SCAST(_min)), max(SCAST(_max)) { check_error(); clamp(); }
	template<typeis::Arithmetic fT> constexpr ValClamp(T _val, std::pair<fT, fT> _minmax) : val(_val), min(SCAST(_minmax.first)), max(SCAST(_minmax.second)) { check_error(); clamp(); }
	template<typeis::Arithmetic fT> constexpr ValClamp(std::pair<T, T> _minmax) : min(SCAST(_minmax.first)), max(SCAST(_minmax.second)) { check_error(); clamp(); }
	template<typeis::Arithmetic fT> constexpr ValClamp(const ValClamp<fT> &from) : val(SCAST(from.val)), min(SCAST(from.min)), max(SCAST(from.max)) { check_error(); clamp(); }

private:
	
	T val = 0;
	T min = 0;
	T max = 0;

public:

	operator T() const noexcept {
		return val;
	}

	template<typeis::Arithmetic fT>
	constexpr void SetMin(fT _min) {
		min = SCAST(_min);
		check_error();
		clamp();
	}

	template<typeis::Arithmetic fT>
	constexpr void SetMax(fT _max) {
		max = SCAST(_max);
		check_error();
		clamp();
	}

	template<typeis::Arithmetic fT>
	constexpr void SetRange(fT _min, fT _max) {
		min = SCAST(_min);
		max = SCAST(_max);
		check_error();
		clamp();
	}

	template<typeis::Arithmetic fT>
	constexpr void SetRange(const std::pair<fT, fT> &_minmax) {
		min = SCAST(_minmax.first);
		max = SCAST(_minmax.second);
		check_error();
		clamp();
	}

	template<typeis::Arithmetic floatT = double>
	constexpr floatT Rate() const noexcept {
		if (min == max) { return 0.0; }
		return static_cast<floatT>(val - min) / static_cast<floatT>(max - min);
	}

	std::string ToString() const {
		return fmt::format("{}{} <= {} <= {}{}", '(', min, val, max, ')');
	}

	// define operator

#define VALCLAMP_ASSINMENT_OPERATOR_base(type, cv, ref) \
	template<typeis::Arithmetic fromT> constexpr ValClamp &operator##type##=(cv fromT ref##v) noexcept { val type##= v; clamp(); return *this; } \
	template<typeis::Arithmetic fromT> constexpr ValClamp &operator##type##=(cv ValClamp<fromT> ref##v) noexcept { val type##= v.val; clamp(); return *this; }
	
#define VALCLAMP_ASSINMENT_OPERATOR_s1(type) \
	VALCLAMP_ASSINMENT_OPERATOR_base(type, const, &) \
	VALCLAMP_ASSINMENT_OPERATOR_base(type, , &&)

#define VALCLAMP_ASSINMENT_OPERATOR \
	VALCLAMP_ASSINMENT_OPERATOR_s1() \
	VALCLAMP_ASSINMENT_OPERATOR_s1(+) \
	VALCLAMP_ASSINMENT_OPERATOR_s1(-) \
	VALCLAMP_ASSINMENT_OPERATOR_s1(*) \
	VALCLAMP_ASSINMENT_OPERATOR_s1(/)

	VALCLAMP_ASSINMENT_OPERATOR;

#undef VALCLAMP_ASSINMENT_OPERATOR_base
#undef VALCLAMP_ASSINMENT_OPERATOR_s1
#undef VALCLAMP_ASSINMENT_OPERATOR

private:

	void clamp() {
		val = std::clamp(val, min, max);
	}

	void check_error() {
		if (min > max) {
			throw std::invalid_argument("min is bigger than max");
		}
	}

};

template<typeis::Arithmetic fT1, typeis::Arithmetic fT2, typeis::Arithmetic fT3> ValClamp(fT1, fT2, fT3) -> ValClamp<std::common_type_t<fT1, fT2, fT3>>;
template<typeis::Arithmetic fT> ValClamp(std::pair<fT, fT>) -> ValClamp<fT>;

// define binary operator

#define VALCLAMP_BINARY_OPERATOR_base(type, cva, refa, cvb, refb) \
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT, typeis::Arithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr returnT operator##type##(cva ValClamp<lfromT> refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return lhs.val type##= rhs.val; } \
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT, typeis::Arithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr returnT operator##type##(cva ValClamp<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return lhs.val type##= rhs; } \
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT, typeis::Arithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr returnT operator##type##(cva lfromT refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return lhs type##= rhs.val; }

#define VALCLAMP_BINARY_OPERATOR_s1(type, cva, refa) \
	VALCLAMP_BINARY_OPERATOR_base(type, cva, refa, const, &) \
	VALCLAMP_BINARY_OPERATOR_base(type, cva, refa, , &&)

#define VALCLAMP_BINARY_OPERATOR_s2(type) \
	VALCLAMP_BINARY_OPERATOR_s1(type, const, &) \
	VALCLAMP_BINARY_OPERATOR_s1(type, , &&)

#define VALCLAMP_BINARY_OPERATOR \
	VALCLAMP_BINARY_OPERATOR_s2(+) \
	VALCLAMP_BINARY_OPERATOR_s2(-) \
	VALCLAMP_BINARY_OPERATOR_s2(*) \
	VALCLAMP_BINARY_OPERATOR_s2(/)

VALCLAMP_BINARY_OPERATOR;

#undef VALCLAMP_BINARY_OPERATOR_base
#undef VALCLAMP_BINARY_OPERATOR_s1
#undef VALCLAMP_BINARY_OPERATOR_s2
#undef VALCLAMP_BINARY_OPERATOR

// define compare operator

#define VALCLAMP_SMALLDEFINE template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator
#define VALCLAMP_COMPARE_OPERATOR_base(cva, refa, cvb, refb) \
	VALCLAMP_SMALLDEFINE<(cva ValClamp<lfromT> refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return lhs.val < rhs.val; } \
	VALCLAMP_SMALLDEFINE<(cva ValClamp<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return lhs.val < rhs; } \
	VALCLAMP_SMALLDEFINE<(cva lfromT refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return lhs < rhs.val; } \
	VALCLAMP_SMALLDEFINE>(cva ValClamp<lfromT> refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return rhs < lhs; } \
	VALCLAMP_SMALLDEFINE>(cva ValClamp<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return rhs < lhs; } \
	VALCLAMP_SMALLDEFINE>(cva lfromT refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return rhs < lhs; } \
	VALCLAMP_SMALLDEFINE<=(cva ValClamp<lfromT> refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return !(lhs > rhs); } \
	VALCLAMP_SMALLDEFINE<=(cva ValClamp<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return !(lhs > rhs); } \
	VALCLAMP_SMALLDEFINE<=(cva lfromT refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return !(lhs > rhs); } \
	VALCLAMP_SMALLDEFINE>=(cva ValClamp<lfromT> refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return !(lhs < rhs); } \
	VALCLAMP_SMALLDEFINE>=(cva ValClamp<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return !(lhs < rhs); } \
	VALCLAMP_SMALLDEFINE>=(cva lfromT refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return !(lhs < rhs); } \
	VALCLAMP_SMALLDEFINE==(cva ValClamp<lfromT> refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return lhs <= rhs && lhs >= rhs; } \
	VALCLAMP_SMALLDEFINE==(cva ValClamp<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return lhs <= rhs && lhs >= rhs; } \
	VALCLAMP_SMALLDEFINE==(cva lfromT refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return lhs <= rhs && lhs >= rhs; } \
	VALCLAMP_SMALLDEFINE!=(cva ValClamp<lfromT> refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return !(lhs == rhs); } \
	VALCLAMP_SMALLDEFINE!=(cva ValClamp<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return !(lhs == rhs); } \
	VALCLAMP_SMALLDEFINE!=(cva lfromT refa lhs, cvb ValClamp<rfromT> refb rhs) noexcept { return !(lhs == rhs); }

#define VALCLAMP_COMPARE_OPERATOR_s1(cva, refa) \
	VALCLAMP_COMPARE_OPERATOR_base(cva, refa, const, &) \
	VALCLAMP_COMPARE_OPERATOR_base(cva, refa, , &&)

#define VALCLAMP_COMPARE_OPERATOR \
	VALCLAMP_COMPARE_OPERATOR_s1(const, &) \
	VALCLAMP_COMPARE_OPERATOR_s1(, &&)

VALCLAMP_COMPARE_OPERATOR;

#undef VALCLAMP_SMALLDEFINE
#undef VALCLAMP_COMPARE_OPERATOR_base
#undef VALCLAMP_COMPARE_OPERATOR_s1
#undef VALCLAMP_COMPARE_OPERATOR