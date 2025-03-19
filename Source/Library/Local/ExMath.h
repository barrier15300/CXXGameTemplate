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