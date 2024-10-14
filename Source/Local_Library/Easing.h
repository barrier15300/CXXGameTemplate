#pragma once
#include <cmath>
#define PI (3.1415926535897932384626433832795028841971)

class Easing {

	Easing() = delete;
	Easing(const Easing &) = delete;
	Easing(Easing &&) = delete;

	Easing &operator=(const Easing &) = delete;
	Easing &operator=(Easing &&) = delete;

	static inline bool valuecheck(double &x) {
		return x <= 0 ? (bool)(x = 0) && false : x >= 1 ? (bool)(x = 1) && false : (bool)(x) || true;
	}

public:

	enum Base {
		In,
		Out,
		InOut,
		OutIn
	};

	enum Line {
		Linear,
		Sine,
		Quad,
		Cubic,
		Quart,
		Quint,
		Expo,
		Cric,
		Back,
		Elastic,
		Bounce
	};

	static inline double GetRate(double x, const Base ebt, const Line elt) {
		if (!valuecheck(x)) { return x; }

		switch (ebt) {
			case Base::InOut:
				return x < 0.5 ?
					GetRate(x * 2, Base::In, elt) * 0.5 :
					0.5 + (GetRate((x - 0.5) * 2, Base::Out, elt) * 0.5);
				break;
			case Base::OutIn:
				return x < 0.5 ?
					GetRate(x * 2, Base::Out, elt) * 0.5 :
					0.5 + (GetRate((x - 0.5) * 2, Base::In, elt) * 0.5);
				break;
		}

		switch (elt) {
			case Line::Linear:
				return x;
				break;
			case Line::Sine:
				switch (ebt) {
					case Base::In:
						return 1 - cos(x * PI / 2);
						break;
					case Base::Out:
						return sin(x * PI / 2);
						break;
				}
				break;
			case Line::Quad:
				switch (ebt) {
					case Base::In:
						return x * x;
						break;
					case Base::Out:
						return 1 - (1 - x) * (1 - x);
						break;
				}
				break;
			case Line::Cubic:
				switch (ebt) {
					case Base::In:
						return x * x * x;
						break;
					case Base::Out:
						return 1 - (1 - x) * (1 - x) * (1 - x);
						break;
				}
				break;
			case Line::Quart:
				switch (ebt) {
					case Base::In:
						return x * x * x * x;
						break;
					case Base::Out:
						return 1 - (1 - x) * (1 - x) * (1 - x) * (1 - x);
						break;
				}
				break;
			case Line::Quint:
				switch (ebt) {
					case Base::In:
						return x * x * x * x * x;
						break;
					case Base::Out:
						return 1 - (1 - x) * (1 - x) * (1 - x) * (1 - x) * (1 - x);
						break;
				}
				break;
			case Line::Expo:
				switch (ebt) {
					case Base::In:
						return x == 0 ? 0 : pow(2, 10 * x - 10);
						break;
					case Base::Out:
						return x == 1 ? 1 : 1 - pow(2, -10 * x);
						break;
				}
				break;
			case Line::Cric:
				switch (ebt) {
					case Base::In:
						return 1 - sqrt(1 - pow(x, 2));
						break;
					case Base::Out:
						return sqrt(1 - pow(x - 1, 2));
						break;
				}
				break;
			case Line::Back: {
				const double c1 = 1.70158;
				const double c3 = c1 + 1;
				switch (ebt) {
					case Base::In:
						return c3 * x * x * x - c1 * x * x;
						break;
					case Base::Out:
						return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
						break;
				}
			}	break;
			case Line::Elastic: {
				const double c4 = 2 * PI / 3;
				switch (ebt) {
					case Base::In:
						return
							x == 0 ?
							0 :
							x == 1 ?
							1 : -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
						break;
					case Base::Out:
						return
							x == 0 ?
							0 :
							x == 1 ?
							1 :
							pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
						break;
				}
			} break;
			case Line::Bounce:
				switch (ebt) {
					case Base::In:
						return 1 - GetRate(1 - x, Base::Out, elt);
						break;
					case Base::Out:
					{
						const double n1 = 7.5625;
						const double d1 = 2.75;

						if (x < 1 / d1) {
							return n1 * x * x;
						}
						else if (x < 2 / d1) {
							return n1 * (x -= 1.5 / d1) * x + 0.75;
						}
						else if (x < 2.5 / d1) {
							return n1 * (x -= 2.25 / d1) * x + 0.9375;
						}
						else {
							return n1 * (x -= 2.625 / d1) * x + 0.984375;
						}
					}
					break;
				}
				break;
		}
		return 0;
	}
	static inline double GetSigmoidRate(double x, const Base sbt, double a = 1) {
		static auto sigmoidfunc = [&](double x, double a){
			return (
				1 +
				(
					(
						(1 - std::pow(std::numbers::e, -a * (2 * x - 1)))
						/
						(1 + std::pow(std::numbers::e, -a * (2 * x - 1)))
					)
					*
					(
						(1 + std::pow(std::numbers::e, -a))
						/
						(1 - std::pow(std::numbers::e, -a))
					)
				)
			) * 0.5;
		};
		
		if (!valuecheck(x)) { return x; }

		switch (sbt) {
			case Base::In:
				return sigmoidfunc(x / 2, a) * 2;
				break;
			case Base::Out:
				return (sigmoidfunc((x / 2) + 0.5, a) - 0.5) * 2;
				break;
			case Base::InOut:
				return sigmoidfunc(x, a);
				break;
			case Base::OutIn:
				return x < 0.5 ?
					GetSigmoidRate(x * 2, Base::Out, a) * 0.5 :
					0.5 + (GetSigmoidRate((x - 0.5) * 2, Base::In, a) * 0.5);
				break;
		}
	}
	static inline double GetBounceRate(double x, double a) {
		static auto bouncefunc = [&](double x, double a) {
			return x < 0.5 ?
				1 - std::pow(1 - (x * 2), a) :
				1 - std::pow(((x - 0.5) * 2), a);
		};
		
		if (!valuecheck(x)) { return x; }

		return bouncefunc(x, a);
	}
};

#undef PI