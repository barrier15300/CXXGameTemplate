#pragma once
#include <type_traits>

namespace typeis { 

	template<class T>
	concept Pointer = std::is_pointer<T>::value;

	template<class T>
	concept Integral = std::is_integral<T>::value;

	template<class T>
	concept FloatingPoint = std::is_floating_point<T>::value;

	template<class T>
	concept Arithmetic = std::is_arithmetic<T>::value;

	template<class T>
	concept Enum = std::is_enum<T>::value;

	template<class T>
	concept Union = std::is_union<T>::value;

	template<class T>
	concept Function = std::is_function<T>::value;
}

