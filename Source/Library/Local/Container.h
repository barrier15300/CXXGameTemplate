#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <ranges>
#include "member_pointer_traits.h"


template <class ArrT>
	requires requires(ArrT a) {
	a.begin();
	a.end();
}
class ContainerUtility : public ArrT {
public:

	using ArrT::ArrT;

	using this_type = ContainerUtility;

	template<class T>
		requires requires(T x) {
		x == x;
	}
	using has_equal_operator = T;

	using value_type = typename ArrT::value_type;
	using equalable_type = has_equal_operator<value_type>;
	using class_type = std::conditional_t<std::is_class_v<value_type>, value_type, void>;
	template<class T>
	using data_member_pointer = T class_type::*;

	using iterator = typename ArrT::iterator;
	
	using reference = value_type&;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reference = const value_type&;
	using const_iterator = const iterator;
	using const_reverse_iterator = const reverse_iterator;
	
	using size_type = size_t;

	template<class T>
		requires requires(T x) {
			{ x(const_reference) } -> bool;
	}


#pragma region ____bool any();

	bool any() {

	}

#pragma endregion


#pragma region ____iterator find();
	iterator find(const_reference v, size_type frontoff, size_type backoff, require_class_type project = {}) {
		auto first = this->begin() + frontoff;
		auto last = this->end() - backoff;
		if (first >= last) {
			return this->end();
		}
		return std::ranges::find(first, last, v);
	}
	const_iterator find(const_reference v, size_type frontoff, size_type backoff) const {
		return this->find(v, frontoff, backoff);
	}
	iterator find(const_reference v) {
		return this->find(v, 0, 0);
	}
	const_iterator find(const_reference v) const {
		return this->find(v, 0, 0);
	}
	iterator find(const_reference v, size_type frontoff) {
		return this->find(v, frontoff, 0);
	}
	const_iterator find(const_reference v, size_type frontoff) const {
		return this->find(v, frontoff, 0);
	}
#pragma endregion

#pragma region ____size_type index_of();
	size_type index_of(const_reference v, size_type frontoff, size_type backoff) {
		auto it = this->find(v, frontoff, backoff);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	size_type index_of(const_reference v, size_type frontoff, size_type backoff) const {
		return this->index_of(v, frontoff, backoff);
	}
	size_type index_of(const_reference v) {
		return this->index_of(v, 0, 0);
	}
	size_type index_of(const_reference v) const {
		return this->index_of(v, 0, 0);
	}
	size_type index_of(const_reference v, size_type frontoff) {
		return this->index_of(v, frontoff, 0);
	}
	size_type index_of(const_reference v, size_type frontoff) const {
		return this->index_of(v, frontoff, 0);
	}
#pragma endregion

#pragma region ____this_type reverse();

	this_type reverse() const {
		return this_type(this->rbegin(), this->rend());
	}

#pragma endregion

#pragma region ____size_type remove();



#pragma endregion


	static constexpr size_type npos = ~0;
};
