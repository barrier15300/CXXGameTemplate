#pragma once
#include "../Helper/DXHandle.h"

#include "../Helper/JsonHelper.h"

#include <array>
#include <initializer_list>
#include <algorithm>
#include <utility>

#include "Library/Common/CommonInclude.h"

#define SCAST(x) static_cast<T>(x)

#define FROM_COONVERTIBLE(toT, ...) template<class fT __VA_OPT__(,) __VA_ARGS__> requires std::is_convertible_v<const fT, toT>

#define DEFINE_TRAITS(base) \
	using value_type = T; \
	using Lcvr = const base<T>&; \
	using Rvr = base<T>&&; \
	template<class fromT> using LcvrFrom = const base<fromT>&; \
	template<class fromT> using RvrFrom = base<fromT>&&;



// define assignment operator template

#define TEMPLATE_ASSIGNMENT_OPERATOR_PROCESS_AUX_1(type, arg) arg ##type##= v.##arg;
#define TEMPLATE_ASSIGNMENT_OPERATOR_PROCESS_AUX_2(type, arg) arg ##type##= v;

#define TEMPLATE_ASSIGNMENT_OPERATOR_base(t, type, ...) \
	template<typeis::Arithmetic fromT> constexpr t &operator##type##=(t<fromT> v) noexcept { MACRO_FOR_EACH_VA_ARGS_ARG1(TEMPLATE_ASSIGNMENT_OPERATOR_PROCESS_AUX_1, type, __VA_ARGS__) return *this; }\
	template<typeis::Arithmetic fromT> constexpr t &operator##type##=(fromT v) noexcept { MACRO_FOR_EACH_VA_ARGS_ARG1(TEMPLATE_ASSIGNMENT_OPERATOR_PROCESS_AUX_2, type, __VA_ARGS__) return *this; }

#define TEMPLATE_ASSIGNMENT_OPERATOR(t, ...) \
	TEMPLATE_ASSIGNMENT_OPERATOR_base(t, +, __VA_ARGS__) \
	TEMPLATE_ASSIGNMENT_OPERATOR_base(t, -, __VA_ARGS__) \
	TEMPLATE_ASSIGNMENT_OPERATOR_base(t, *, __VA_ARGS__) \
	TEMPLATE_ASSIGNMENT_OPERATOR_base(t, /, __VA_ARGS__)

// define binary operator template

#define TEMPLATE_BINARY_OPERATOR_base(t, type) \
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT, typeis::Arithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(t<lfromT> lhs, t<rfromT> rhs) noexcept { return t<returnT>(lhs) type##= rhs; } \
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT, typeis::Arithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(t<lfromT> lhs, rfromT rhs) noexcept { return t<returnT>(lhs) type##= rhs;} \
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT, typeis::Arithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(lfromT lhs, t<rfromT> rhs) noexcept { return t<returnT>(rhs) type##= lhs; }

#define TEMPLATE_BINARY_OPERATOR(t) \
	TEMPLATE_BINARY_OPERATOR_base(t, +)\
	TEMPLATE_BINARY_OPERATOR_base(t, -)\
	TEMPLATE_BINARY_OPERATOR_base(t, *)\
	TEMPLATE_BINARY_OPERATOR_base(t, /)

#define TEMPLATE_COMPARE_OPERATOR_base(t, _min) \
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator< (t<lfromT> lhs, t<rfromT> rhs) noexcept { return _min; }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator> (t<lfromT> lhs, t<rfromT> rhs) noexcept { return rhs < lhs; }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator<=(t<lfromT> lhs, t<rfromT> rhs) noexcept { return !(lhs > rhs); }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator>=(t<lfromT> lhs, t<rfromT> rhs) noexcept { return !(lhs < rhs); }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator==(t<lfromT> lhs, t<rfromT> rhs) noexcept { return lhs >= rhs && lhs <= rhs; }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator!=(t<lfromT> lhs, t<rfromT> rhs) noexcept { return !(lhs == rhs); }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator< (t<lfromT> lhs, std::initializer_list<rfromT> rhs) noexcept { return lhs < t<rfromT>(rhs); }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator> (t<lfromT> lhs, std::initializer_list<rfromT> rhs) noexcept { return t<rfromT>(rhs) < lhs; }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator<=(t<lfromT> lhs, std::initializer_list<rfromT> rhs) noexcept { return !(lhs > t<rfromT>(rhs)); }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator>=(t<lfromT> lhs, std::initializer_list<rfromT> rhs) noexcept { return !(lhs < t<rfromT>(rhs)); }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator==(t<lfromT> lhs, std::initializer_list<rfromT> rhs) noexcept { return lhs >= t<rfromT>(rhs) && lhs <= t<rfromT>(rhs); }\
	template<typeis::Arithmetic lfromT, typeis::Arithmetic rfromT> constexpr bool operator!=(t<lfromT> lhs, std::initializer_list<rfromT> rhs) noexcept { return !(lhs == t<rfromT>(rhs)); }
	
#define TEMPLATE_COMPARE_OPERATOR(t, _min) \
	TEMPLATE_COMPARE_OPERATOR_base(t, _min)

