#pragma once
#include "Val2D.h"

template<IsArithmetic radiusT, IsArithmetic thetaT = double>
struct Polar2D {

	Polar2D() : r(0), x(0) {}

	radiusT r;
	thetaT x;

	// TODO: maybe later



	template<class fT>
	Polar2D Parse(const Val2D<fT> &from) {
		r = from.Length();
		x = from.Angle();
		return *this;
	}

	template<class rT = thetaT>
	Val2D<rT> Pos() const {
		Val2D<rT> ret{r, 0};
		return ret.Rotate(x);
	}
};