#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <ranges>

template <std::ranges::viewable_range ArrT> class ExtendContainerUtility;

template<std::ranges::viewable_range R>
class LINQ : public ExtendContainerUtility<R> {



#pragma region ____views wrapper

#pragma region ____this_type reverse();

	auto reverse() {
		return *this | std::views::reverse;
	}
	auto reverse() const {
		return *this | std::views::reverse;
	}

#pragma endregion

#pragma endregion



};

template <std::ranges::viewable_range ContainerT>
class ExtendContainerUtility : public ContainerT {
public:

	using ContainerT::ContainerT;
	template<std::ranges::viewable_range arrT>
	ExtendContainerUtility(arrT arr) : ContainerT(arr) {};

	using this_type = ExtendContainerUtility;

	using value_type = typename ContainerT::value_type;
	using class_type = std::conditional_t<std::is_class_v<value_type>, value_type, void>;
	template<class T>
	using data_member_pointer = T class_type::*;

	using iterator = typename ContainerT::iterator;
	using const_iterator = const ContainerT::const_iterator;
	
	using reference = value_type&;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reference = const value_type&;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;

#define _TEMP_PREDICATE template<class Project = std::identity, std::indirect_unary_predicate<std::projected<iterator, Project>> Predicate>
#define _TEMP_PROJECT template<class Project = std::identity>

#pragma region ____algorithm wrapper

#pragma region ____bool all();

	_TEMP_PREDICATE constexpr bool all(Predicate predicate, Project project = {}) const {
		return std::ranges::all_of(*this, predicate, project);
	}

#pragma endregion

#pragma region ____bool any();

	_TEMP_PREDICATE constexpr bool any(Predicate predicate, Project project = {}) const {
		return std::ranges::any_of(*this, predicate, project);
	}

#pragma endregion

#pragma region ____bool contains();
#if __cplusplus >= 202302L
	_TEMP_PROJECT constexpr bool contains(const_reference v, Project project = {}) const {
		return std::ranges::contains(*this, v, project);
	}
#endif
#pragma endregion

#pragma region ____void copy();

#pragma endregion

#pragma region ____iterator find();
	_TEMP_PROJECT constexpr iterator find(const_reference v, size_type frontoff, Project project) {
		auto first = this->begin() + frontoff;
		auto last = this->end();
		if (first >= last) {
			return this->end();
		}
		return std::ranges::find(first, last, v, project);
	}
	_TEMP_PROJECT constexpr const_iterator find(const_reference v, size_type frontoff, Project project) const {
		auto first = this->begin() + frontoff;
		auto last = this->end();
		if (first >= last) {
			return this->end();
		}
		return std::ranges::find(first, last, v, project);
	}
	constexpr iterator find(const_reference v, size_type frontoff) {
		return this->find(v, frontoff, {});
	}
	constexpr const_iterator find(const_reference v, size_type frontoff) const {
		return this->find(v, frontoff, {});
	}
	_TEMP_PROJECT constexpr iterator find(const_reference v, Project project) {
		return std::ranges::find(*this, v, project);
	}
	_TEMP_PROJECT constexpr const_iterator find(const_reference v, Project project) const {
		return std::ranges::find(*this, v, project);
	}
	constexpr iterator find(const_reference v) {
		return this->find(v, std::identity{});
	}
	constexpr const_iterator find(const_reference v) const {
		return this->find(v, std::identity{});
	}
#pragma endregion

#pragma region ____size_type index_of();
	_TEMP_PROJECT size_type index_of(const_reference v, size_type frontoff, Project project = {}) {
		auto it = this->find(v, frontoff, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	_TEMP_PROJECT size_type index_of(const_reference v, size_type frontoff, Project project = {}) const {
		auto it = this->find(v, frontoff, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	size_type index_of(const_reference v, size_type frontoff) {
		return this->index_of(v, frontoff, {});
	}
	size_type index_of(const_reference v, size_type frontoff) const {
		return this->index_of(v, frontoff, {});
	}
	_TEMP_PROJECT size_type index_of(const_reference v, Project project = {}) {
		auto it = this->find(v, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	_TEMP_PROJECT size_type index_of(const_reference v, Project project = {}) const {
		auto it = this->find(v, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	size_type index_of(const_reference v) {
		return this->index_of(v, std::identity{});
	}
	size_type index_of(const_reference v) const {
		return this->index_of(v, std::identity{});
	}
#pragma endregion

#pragma endregion



#pragma endregion

	static constexpr size_type npos = ~0;
};
