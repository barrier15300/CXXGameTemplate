#pragma once
#include "DxLib.h"

#include "../Helper/JsonHelper.h"

#include "fmt/core.h"
#include "fmt/ranges.h"
#include <array>
#include <utility>

#include "Local_Library/template_type.h"

#define SCAST(x) static_cast<T>(x)

#define TEMPLATE_OPERATOR_BASE(t, type)\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(const t<lfT> &lhs, const t<rfT> &rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(const t<lfT> &lhs, const rfT &rhs) { return t<rT>(lhs) ##type##= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT, IsArithmetic rT = std::common_type_t<lfT, rfT>> t<rT> operator##type##(const lfT &lhs, const t<rfT> &rhs) { return t<rT>(lhs) ##type##= rhs; }

#define COMPARE_OPERATOR_BASE(t, _min) \
template<IsArithmetic lfT, IsArithmetic rfT> bool operator<(const t<lfT> &lhs, const t<rfT> &rhs) { return _min; }\
template<IsArithmetic lfT, IsArithmetic rfT> bool operator>(const t<lfT> &lhs, const t<rfT> &rhs) { return rhs < lhs; }\
template<IsArithmetic lfT, IsArithmetic rfT> bool operator<=(const t<lfT> &lhs, const t<rfT> &rhs) { return !(lhs > rhs); }\
template<IsArithmetic lfT, IsArithmetic rfT> bool operator>=(const t<lfT> &lhs, const t<rfT> &rhs) { return !(lhs < rhs); }\
template<IsArithmetic lfT, IsArithmetic rfT> bool operator==(const t<lfT> &lhs, const t<rfT> &rhs) { return lhs >= rhs && lhs <= rhs; }\
template<IsArithmetic lfT, IsArithmetic rfT> bool operator!=(const t<lfT> &lhs, const t<rfT> &rhs) { return !(lhs == rhs); }
