#pragma once

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