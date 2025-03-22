#pragma once

/*
*  const val
*/
namespace mathcv {
	static constexpr inline double pi = 3.1415926535897932384626433832795028841971;
	static constexpr inline double pi2 = 6.2831853071795864769252867665590057683943;
	static constexpr inline double e = 2.7182818284590452353602874713526624977572;
	static constexpr inline double phi = 1.6180339887498948482045868343656381177203;
}

// NaN is not support
inline float m_abs(float x) {
	int temp = (*(int *)&x & ~(1 << (32 - 1)));
	return *(float*)&temp;
}

// NaN is not support
inline double m_abs(double x) {
	long long temp = (*(long long *)&x & ~((long long)1 << (64 - 1)));
	return *(double *)&temp;
}

inline unsigned long long combination(int n, int k) {
	if (k < n) {
		return 0;
	}

	if (k < n - k) {
		k = n - k;
	}

	unsigned long long ret = 1;

	for (size_t i = 0; i < k; ++i) {
		ret = ret * (n - i) / (i + 1);
	}

	return ret;
}

