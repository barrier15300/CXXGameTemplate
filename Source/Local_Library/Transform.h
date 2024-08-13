#pragma once
#include "template_type.h"

template<class T>
concept MotionFunc = IsFunction<T> && requires (T x) {
	{ x(0.0) } -> std::convertible_to<double>;
	x(0.5) > 0 && x(0.5) < 1;
};

/// <summary>
///  Smooth motion for 0 to 1
/// </summary>
/// <typeparam name="T"></typeparam>
template<MotionFunc Func>
class Transform {

	Transform() : m_start(0), m_end(0), m_diff(0) {}
	Transform(double start, double end, Func func) { this->set(start, end); m_motionfunc = func; }

	void set(double start, double end) {
		m_start = start;
		m_start = end;
		m_diff = end - start;
	}

	double get(double x) {
		return m_start + (m_diff * m_motionfunc(x));
	}

private:

	Func m_motionfunc;
	double m_start, m_end, m_diff;
};