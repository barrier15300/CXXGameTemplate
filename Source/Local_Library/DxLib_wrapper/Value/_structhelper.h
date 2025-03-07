#pragma once
#include "DxLib.h"

#include "../Helper/JsonHelper.h"

#include "fmt/core.h"
#include "fmt/ranges.h"
#include <array>

#include "Local_Library/template_type.h"

#define FUNC_GETTER(T, name) const T& name() const { return m_##name; }

#define SCAST(x) static_cast<T>(x)


// define assinment operator template

#define TEMPLATE_ASSINMENT_OPERATOR_base(t, type, cv, ref) \
template<IsArithmetic fromT> constexpr t &operator##type##=(cv t<fromT> ref v) noexcept { x ##type##= v.x; y ##type##= v.y; return *this; }\
template<IsArithmetic fromT> constexpr t &operator##type##=(cv fromT ref v) noexcept { x ##type##= v; y ##type##= v; return *this; }

#define TEMPLATE_ASSINMENT_OPERATOR_s1(t, type) \
TEMPLATE_ASSINMENT_OPERATOR_base(t, type, const, &) \
TEMPLATE_ASSINMENT_OPERATOR_base(t, type, , &&) \

#define TEMPLATE_ASSINMENT_OPERATOR(t) \
TEMPLATE_ASSINMENT_OPERATOR_s1(t, +) \
TEMPLATE_ASSINMENT_OPERATOR_s1(t, -) \
TEMPLATE_ASSINMENT_OPERATOR_s1(t, *) \
TEMPLATE_ASSINMENT_OPERATOR_s1(t, /)

// define binary operator template

#define TEMPLATE_BINARY_OPERATOR_base(t, type, cva, refa, cvb, refb) \
template<IsArithmetic lfromT, IsArithmetic rfromT, IsArithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(cva t<lfromT> refa lhs, cvb t<rfromT> refb rhs) noexcept { return t<returnT>(lhs) ##type##= t<returnT>(rhs); } \
template<IsArithmetic lfromT, IsArithmetic rfromT, IsArithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(cva t<lfromT> refa lhs, cvb rfromT refb rhs) noexcept { return t<returnT>(lhs) ##type##= t<returnT>(rhs);} \
template<IsArithmetic lfromT, IsArithmetic rfromT, IsArithmetic returnT = std::common_type_t<lfromT, rfromT>> constexpr t<returnT> operator##type##(cva lfromT refa lhs, cvb t<rfromT> refb rhs) noexcept { return t<returnT>(rhs) ##type##= t<returnT>(lhs); }

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

