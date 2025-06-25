#pragma once
#include <type_traits>

template<class T>
concept IsArithmetic =
std::is_arithmetic<T>::value
//||	requires (T x) {
//	x = x + x;
//	x = x - x;
//	x = x * x;
//	x = x / x;
//	x += x;
//	x -= x;
//	x *= x;
//	x /= x;
//	x < x;
//	x > x;
//	x <= x;
//	x >= x;
//	x == x;
//	x != x;
//	x++;
//	++x;
//	x--;
//	--x;
//}
;

template<class T>
concept IsFunction = std::is_function<T>::value;
