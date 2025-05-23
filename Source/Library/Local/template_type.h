#pragma once
#include <type_traits>

template<class T>
concept IsArithmetic =
std::is_arithmetic_v<T> ||
!std::is_pointer_v<T> ||
	requires (T x) {
	x = x + x;
	x = x - x;
	x = x * x;
	x = x / x;
	{ x += x } -> std::convertible_to<T>;
	{ x -= x } -> std::convertible_to<T>;
	{ x *= x } -> std::convertible_to<T>;
	{ x /= x } -> std::convertible_to<T>;
	x < x;
	x > x;
	x <= x;
	x >= x;
	x == x;
	x != x;
	x++;
	++x;
	x--;
	--x;
};

template<class T>
concept IsFunction = std::is_function_v<T>;
