#pragma once
#include "../../../template_type.h"

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

