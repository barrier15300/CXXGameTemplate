#pragma once
#include "../Value/Value.h"

template<class T>
struct Triangle {

	Triangle() {}
	Triangle(const Val2D<T> &size) {
		*this = Triangle({0,0}, {size.x,0}, {0,size.y});
	}
	Triangle(const Val2D<T> &p1, const Val2D<T> &p2, const Val2D<T> &p3) :
		Poses{p1, p2, p3} {}


	Val2D<T> Poses[3]{};

};