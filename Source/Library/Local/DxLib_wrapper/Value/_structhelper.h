#pragma once
#include "../Helper/DXHandle.h"

#include "../Helper/JsonHelper.h"

#include <array>
#include <initializer_list>
#include <algorithm>
#include <utility>

#include "Library/fmt_include.h"
#include "Library/Local/template_type.h"
#include "Library/Local/MacroHelper.h"

#define FUNC_GETTER(T, name) const T& name() const { return m_##name; }

#define SCAST(x) static_cast<T>(x)

#define FROM_COONVERTIBLE(toT, ...) template<class fT __VA_OPT__(,) __VA_ARGS__> requires std::is_convertible_v<const fT, toT>

// define assinment operator template

#define TEMPLATE_ASSINMENT_OPERATOR_PROCESS_AUX_1(type, arg) arg ##type##= v.##arg;
#define TEMPLATE_ASSINMENT_OPERATOR_PROCESS_AUX_2(type, arg) arg ##type##= v;

#define TEMPLATE_ASSINMENT_OPERATOR_base(t, type, cv, ref, ...) \
	template<IsArithmetic fromT> constexpr t &operator##type##=(cv t<fromT> ref v) noexcept { MACRO_FOR_EACH_VA_ARGS_ARG1(TEMPLATE_ASSINMENT_OPERATOR_PROCESS_AUX_1, type, __VA_ARGS__) return *this; }\
	template<IsArithmetic fromT> constexpr t &operator##type##=(cv fromT ref v) noexcept { MACRO_FOR_EACH_VA_ARGS_ARG1(TEMPLATE_ASSINMENT_OPERATOR_PROCESS_AUX_2, type, __VA_ARGS__) return *this; }

#define TEMPLATE_ASSINMENT_OPERATOR_s1(t, type, ...) \
	TEMPLATE_ASSINMENT_OPERATOR_base(t, type, const, &, __VA_ARGS__) \
	TEMPLATE_ASSINMENT_OPERATOR_base(t, type, , &&, __VA_ARGS__) \

#define TEMPLATE_ASSINMENT_OPERATOR(t, ...) \
	TEMPLATE_ASSINMENT_OPERATOR_s1(t, +, __VA_ARGS__) \
	TEMPLATE_ASSINMENT_OPERATOR_s1(t, -, __VA_ARGS__) \
	TEMPLATE_ASSINMENT_OPERATOR_s1(t, *, __VA_ARGS__) \
	TEMPLATE_ASSINMENT_OPERATOR_s1(t, /, __VA_ARGS__)

// define binary operator template

#define TEMPLATE_BINARY_OPERATOR_base(t, type, cva, refa, cvb, refb) \
	template<IsArithmetic lfromT, IsArithmetic rfromT, IsArithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return t<returnT>(lhs) type##= rhs; } \
	template<IsArithmetic lfromT, IsArithmetic rfromT, IsArithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(cva t<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return t<returnT>(lhs) type##= rhs;} \
	template<IsArithmetic lfromT, IsArithmetic rfromT, IsArithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(cva lfromT refa lhs, cvb t<rfromT> refb rhs) noexcept { return t<returnT>(rhs) type##= lhs; }

#define TEMPLATE_BINARY_OPERATOR_s1(t, type, cva, refa) \
	TEMPLATE_BINARY_OPERATOR_base(t, type, cva, refa, const, &) \
	TEMPLATE_BINARY_OPERATOR_base(t, type, cva, refa, , &&)

#define TEMPLATE_BINARY_OPERATOR_s2(t, type) \
	TEMPLATE_BINARY_OPERATOR_s1(t, type, const, &) \
	TEMPLATE_BINARY_OPERATOR_s1(t, type, , &&)

#define TEMPLATE_BINARY_OPERATOR(t) \
	TEMPLATE_BINARY_OPERATOR_s2(t, +)\
	TEMPLATE_BINARY_OPERATOR_s2(t, -)\
	TEMPLATE_BINARY_OPERATOR_s2(t, *)\
	TEMPLATE_BINARY_OPERATOR_s2(t, /)


// define compare operator template

template<class Derived>
class ICompare {
public:

	constexpr bool operator< (const Derived& rhs) noexcept {
		static_asset(std::is_invocable_r_v<bool, decltype(rhs.LessThanImpl), Derived>, "Implement the \"LessThanImpl\" function");
		return rhs.LessThanImpl();
	}

	constexpr bool operator> (const Derived& rhs) noexcept { return rhs < *this; }\
	constexpr bool operator<=(const Derived& rhs) noexcept { return !(*this > rhs); }\
	constexpr bool operator>=(const Derived& rhs) noexcept { return !(*this < rhs); }\
	constexpr bool operator==(const Derived& rhs) noexcept { return *this >= rhs && *this <= rhs; }\
	constexpr bool operator!=(const Derived& rhs) noexcept { return !(*this == rhs); }
};

#define TEMPLATE_COMPARE_OPERATOR_base(t, _min, cva, refa, cvb, refb) \
	template<IsArithmetic lfromT, IsArithmetic rfromT> constexpr bool operator< (cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return _min; }\
	template<IsArithmetic lfromT, IsArithmetic rfromT> constexpr bool operator> (cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return rhs < lhs; }\
	template<IsArithmetic lfromT, IsArithmetic rfromT> constexpr bool operator<=(cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return !(lhs > rhs); }\
	template<IsArithmetic lfromT, IsArithmetic rfromT> constexpr bool operator>=(cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return !(lhs < rhs); }\
	template<IsArithmetic lfromT, IsArithmetic rfromT> constexpr bool operator==(cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return lhs >= rhs && lhs <= rhs; }\
	template<IsArithmetic lfromT, IsArithmetic rfromT> constexpr bool operator!=(cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return !(lhs == rhs); }

#define TEMPLATE_COMPARE_OPERATOR_s1(t, _min, cva, refa) \
	TEMPLATE_COMPARE_OPERATOR_base(t, _min, cva, refa, const, &) \
	TEMPLATE_COMPARE_OPERATOR_base(t, _min, cva, refa, , &&)

#define TEMPLATE_COMPARE_OPERATOR(t, _min) \
	TEMPLATE_COMPARE_OPERATOR_s1(t, _min, const, &)\
	TEMPLATE_COMPARE_OPERATOR_s1(t, _min, , &&)

