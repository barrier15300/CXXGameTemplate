#pragma once
#include "function_ref.h"
#include <utility>
#include <unordered_map>

class HandlerListException : std::exception {
public:

	HandlerListException(std::string msg, size_t id) : std::exception((msg + " id: " + std::to_string(id)).c_str()) {}
	~HandlerListException() = default;

};

template<typename F>
class HandlerList : private std::unordered_map<size_t, function_ref<F>> {
public:

	using handler = function_ref<F>;

	void Regist(std::pair<size_t, handler> idhandler) {
		auto&& [id, handler] = idhandler;
		auto [it, flag] = (*this).emplace(id, handler);
	}

	handler& operator[](size_t id) {
		auto it = this->find(id);
		if (it == this->end()) {
			throw HandlerListException("HandlerList: No such handler.", id);
		}
		auto&& [_, handler] = *it;
		return handler;
	}
};



