#pragma once
#include <concepts>
#include "function_ref.h"

template<class T>
class Properties {
	
	Properties() {};

public:

	using getF = function_ref<T(void)>;
	using setF = function_ref<void(T)>;

	Properties& operator=(const T& value) const {
		set(value);
		return *this;
	}

	operator T() const {
		return get();
	}

	T get() const {
		if (getter == nullptr) {
			throw std::runtime_error("Getter not set");
		}
		return getter();
	}

	void set(T value) const {
		if (setter == nullptr) {
			throw std::runtime_error("Setter not set");
		}
		setter(value);
	}

	constexpr static Properties Make(getF get, setF set) {
		Properties ret{};
		ret.getter = get;
		ret.setter = set;
		return ret;
	}

	static inline getF getter = nullptr;
	static inline setF setter = nullptr;

};