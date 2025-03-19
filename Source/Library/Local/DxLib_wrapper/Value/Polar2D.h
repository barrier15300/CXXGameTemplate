#pragma once
#include "Val2D.h"

template<IsArithmetic radiusT, IsArithmetic thetaT = double>
struct Polar2D {

	constexpr Polar2D() : radius(0), theta(0) {}
	constexpr Polar2D(radiusT r, thetaT t) : radius(r), theta(t) {}
	template<IsArithmetic fRT, IsArithmetic fTT> constexpr Polar2D(fRT r, fTT t) : radius(r), theta(t) {}
	template<IsArithmetic fT> constexpr Polar2D(const Val2D<fT> &pos) { Parse<fT>(pos); }

	radiusT radius;
	thetaT theta;

	template<class rT = thetaT>
	constexpr Val2D<rT> Pos() const {
		return Val2D<rT>(radius, 0).Rotate<rT>(theta);
	}

	template<class fT>
	static Polar2D Parse(const Val2D<fT> &from) {
		return Polar2D(from.Length(), from.Angle());
	}
};

template<IsArithmetic fRT, IsArithmetic fTT> Polar2D(fRT, fTT) -> Polar2D<fRT, fTT>;
template<IsArithmetic fT> Polar2D(const Val2D<fT> &) -> Polar2D<fT>;