#pragma once

/// @brief low level bit cast
/// @tparam retT -> return type of POD
/// @tparam fromT -> from type of POD
/// @param from -> convert as value
/// @return converted retT value
template<class retT, class fromT>
static inline retT union_cast(fromT from) {
	union {
		retT ret{};
		fromT _cast;
	};
	_cast = from;
	return ret;
}