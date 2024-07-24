#pragma once
#include <type_traits>

template<class T>
concept IsArithmetic = std::is_arithmetic_v<T>;

template<class T>
concept IsFunction = std::is_function_v<T>;
