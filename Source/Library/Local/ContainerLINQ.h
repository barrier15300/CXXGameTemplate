#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <ranges>


template <std::ranges::viewable_range ArrT>
class ContainerUtility : public ArrT {
public:

	using ArrT::ArrT;
	template<std::ranges::viewable_range arrT>
	ContainerUtility(arrT arr) : ArrT(arr) {};

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
	using difference_type = std::ptrdiff_t;

#pragma region ____algorithm wrapper

#pragma region ____bool all();

	template<class Project = std::identity, std::indirect_unary_predicate<std::projected<iterator, Project>> Predicate>
	constexpr bool all(Predicate predicate, Project project = {}) const {
		return std::ranges::all_of(*this, predicate, project);
	}

#pragma endregion

#pragma region ____bool any();

	template<class Project = std::identity, std::indirect_unary_predicate<std::projected<iterator, Project>> Predicate>
	constexpr bool any(Predicate predicate, Project project = {}) const {
		return std::ranges::any_of(*this, predicate, project);
	}

#pragma endregion

#pragma region ____bool contains();
	template<class Project = std::identity>
	constexpr bool contains(const_reference v, Project project = {}) const {
		return std::ranges::contains(*this, v, project);
	}
#pragma endregion

#pragma region ____iterator find();
	template<class Project = std::identity>
	iterator find(const_reference v, size_type frontoff, Project project = {})
		requires !std::is_class_v<value_type>
	{
		auto first = this->begin() + frontoff;
		auto last = this->end();
		if (first >= last) {
			return this->end();
		}
		return std::ranges::find(first, last, v, project);
	}
	template<class Project = std::identity>
	const_iterator find(const_reference v, size_type frontoff, Project project = {}) const
		requires !std::is_class_v<value_type>
	{
		auto first = this->begin() + frontoff;
		auto last = this->end();
		if (first >= last) {
			return this->end();
		}
		return std::ranges::find(first, last, v, project);
	}
	iterator find(const_reference v, size_type frontoff)
		requires !std::is_class_v<value_type>
	{
		return this->find(v, frontoff, {});
	}
	const_iterator find(const_reference v, size_type frontoff) const
		requires !std::is_class_v<value_type>
	{
		return this->find(v, frontoff, {});
	}
	template<class Project = std::identity>
	iterator find(const_reference v, Project project = {}) {
		return std::ranges::find(*this, v, project);
	}
	template<class Project = std::identity>
	const_iterator find(const_reference v, Project project = {}) const {
		return std::ranges::find(*this, v, project);
	}
	iterator find(const_reference v)
		requires !std::is_class_v<value_type>
	{
		return this->find(v, std::identity{});
	}
	const_iterator find(const_reference v) const
		requires !std::is_class_v<value_type>
	{
		return this->find(v, std::identity{});
	}
#pragma endregion

#pragma region ____size_type index_of();
	template<class Project = std::identity>
	size_type index_of(const_reference v, size_type frontoff, Project project = {})
		requires !std::is_class_v<value_type>
	{
		auto it = this->find(v, frontoff, backoff, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	template<class Project = std::identity>
	size_type index_of(const_reference v, size_type frontoff, Project project = {}) const
		requires !std::is_class_v<value_type>
	{
		auto it = this->find(v, frontoff, backoff, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	size_type index_of(const_reference v, size_type frontoff)
		requires !std::is_class_v<value_type>
	{
		return this->index_of(v, frontoff, {});
	}
	size_type index_of(const_reference v, size_type frontoff) const
		requires !std::is_class_v<value_type>
	{
		return this->index_of(v, frontoff, {});
	}
	template<class Project = std::identity>
	size_type index_of(const_reference v, Project project = {})
		requires !std::is_class_v<value_type>
	{
		auto it = this->find(v, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	template<class Project = std::identity>
	size_type index_of(const_reference v, Project project = {}) const
		requires !std::is_class_v<value_type>
	{
		auto it = this->find(v, project);
		if (it == this->end()) {
			return npos;
		}
		return it - this->begin();
	}
	size_type index_of(const_reference v)
		requires !std::is_class_v<value_type>
	{
		return this->index_of(v, std::identity{});
	}
	size_type index_of(const_reference v) const
		requires !std::is_class_v<value_type>
	{
		return this->index_of(v, std::identity{});
	}
#pragma endregion

#pragma endregion

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



#pragma endregion

	static constexpr size_type npos = ~0;
};
