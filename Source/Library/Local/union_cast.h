#pragma once

// low level bit cast
template<class retT, class fromT>
static inline retT union_cast(fromT from) {
	union {
		retT ret{};
		fromT _cast;
	};
	_cast = from;
	return ret;
}