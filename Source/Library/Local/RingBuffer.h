#pragma once
#include <iterator>
#include <array>
#include <vector>
#include <compare>

template<class, class>
class ringbuffer_iterator;

template<class T, class _container_T>
class ringbuffer_base : private _container_T {
public:

	using value_type = T;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;

	using container_base = _container_T;

	using iterator = ringbuffer_iterator<value_type, container_base>;
	using const_iterator = ringbuffer_iterator<const value_type, container_base>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	using container_base::container_base;

	friend class ringbuffer_iterator<value_type, container_base>;
	friend class ringbuffer_iterator<const value_type, container_base>;

	constexpr iterator begin() noexcept {
		return iterator(std::next(container_base::begin(), m_index), this);
	}
	constexpr iterator end() noexcept {
		return iterator(begin() + m_current_size, this);
	}
	constexpr const_iterator begin() const noexcept {
		return const_iterator(std::next(container_base::begin(), m_index), this);
	}
	constexpr const_iterator end() const noexcept {
		return const_iterator(begin() + m_current_size, this);
	}
	constexpr const_iterator cbegin() const noexcept {
		return begin();
	}
	constexpr const_iterator cend() const noexcept {
		return end();
	}
	constexpr reverse_iterator rbegin() noexcept {
		return reverse_iterator(end());
	}
	constexpr reverse_iterator rend() noexcept {
		return reverse_iterator(begin());
	}
	constexpr const_reverse_iterator rbegin() const noexcept {
		return const_reverse_iterator(rbegin());
	}
	constexpr const_reverse_iterator rend() const noexcept {
		return const_reverse_iterator(rend());
	}
	constexpr const_reverse_iterator crbegin() const noexcept {
		return rbegin();
	}
	constexpr const_reverse_iterator crend() const noexcept {
		return rend();
	}

	constexpr size_t size() const noexcept {
		return container_base::size();
	}
	constexpr void resize(size_t newsize, const_reference val = value_type()) {
		if constexpr (!requires (container_base x, size_t s, value_type v) { x.resize(s, v); }) {
			throw std::runtime_error("Container does not support resizing.");
		}
		container_base::resize(newsize, val);
	}

	template<class InputIterator>
	constexpr void assign(InputIterator first, InputIterator last) {
		for (auto&& elem : *this) {
			if (first != last) {
				break;
			}
			elem = *first;
			++first;
		}
	}
	constexpr void assign(size_t n, const_reference t) {
		size_t c = 0;
		for (auto&& elem : *this) {
			if (!(c < n)) {
				break;
			}
			elem = t;
			++c;
		}
	}
	constexpr void assign(std::initializer_list<value_type> il) {
		assign(il.begin(), il.end());
	}

	constexpr reference front() noexcept {
		return *begin();
	}
	constexpr reference back() noexcept {
		return *(end() - 1);
	}

	constexpr void write_back(const T& v) noexcept {
		write_back_impl(v);
	}
	constexpr void write_back(T&& v) noexcept {
		write_back_impl(v);
	}
	constexpr void clear_front() noexcept {
		this->front() = value_type();

		if (!(++m_index < size())) {
			m_index = 0;
		}

		if (!(--m_current_size < size())) {
			m_current_size = 0;
		}
	}
private:
	template<class fT>
	constexpr void write_back_impl(fT&& v) requires std::is_same<fT, T>::value noexcept {
		(*this)[m_current_size] = std::forward<fT>(v);

		if (++m_current_size >= size()) {
			m_current_size = size() - 1;
		}
		else {
			return;
		}

		if (++m_index >= size()) {
			m_index = 0;
		}
	}

public:

	constexpr reference operator[](size_t pos) noexcept { return *(begin() + pos); }
	constexpr const_reference operator[](size_t pos) const noexcept { return *(begin() + pos); }

	constexpr reference at(size_t pos) {
		if (!(pos < m_current_size)) { throw std::out_of_range(""); }
		return (*this)[pos];
	}
	constexpr const_reference at(size_t pos) const {
		if (!(pos < m_current_size)) { throw std::out_of_range(""); }
		return (*this)[pos];
	}

	constexpr typename container_base::iterator base_begin() noexcept {
		return container_base::begin();
	}
	constexpr typename container_base::iterator base_end() noexcept {
		return container_base::end();
	}
	constexpr typename container_base::const_iterator base_begin() const noexcept {
		return container_base::begin();
	}
	constexpr typename container_base::const_iterator base_end() const noexcept {
		return container_base::end();
	}

protected:

	size_t m_index = 0;
	size_t m_current_size = 0;

};

template<class T, class _container_T>
class ringbuffer_iterator {
public:

	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using parent = ringbuffer_base<value_type, _container_T>;
	using parent_pointer = typename std::conditional<std::is_const<value_type>::value, const parent*, parent*>::type;
	using container_iterator = typename std::conditional<std::is_const<value_type>::value, typename parent::container_base::const_iterator, typename parent::container_base::iterator>::type;
	using iterator = ringbuffer_iterator<value_type, _container_T>;

	constexpr ringbuffer_iterator() noexcept = default;
	constexpr ringbuffer_iterator(iterator it, parent_pointer parent) noexcept : m_it(it.m_it), m_parent(parent) {}
	constexpr ringbuffer_iterator(container_iterator it, parent_pointer parent) noexcept : m_it(it), m_parent(parent) {}
	constexpr ~ringbuffer_iterator() noexcept = default;

	constexpr iterator& operator=(const iterator&) noexcept = default;

	constexpr reference operator*() const { return *m_it; }
	constexpr reference operator->() const { return *m_it; }
	constexpr iterator& operator++() noexcept { check_add(1); return *this; }
	constexpr iterator operator++(int) noexcept { iterator tmp = *this; check_add(1); return tmp; }
	constexpr iterator& operator--() noexcept { check_sub(1); return *this; }
	constexpr iterator operator--(int) noexcept { iterator tmp = *this; check_sub(1); return tmp; }
	constexpr iterator& operator+=(difference_type n) noexcept { check_add(n); return *this; }
	constexpr iterator& operator-=(difference_type n) noexcept { check_sub(n); return *this; }
	
	static constexpr void check_parent(const iterator& lhs, const iterator& rhs) {
		if (lhs.m_parent != rhs.m_parent) {
			throw std::runtime_error("Iterators do not belong to the same ringbuffer.");
		}
	}
	constexpr void check_add(difference_type n) noexcept {
		difference_type size = m_parent->size();
		container_iterator _begin = m_parent->base_begin();
		difference_type diff = ((std::distance(_begin, m_it) + n) % size);
		m_it = std::next(_begin, diff);
	}
	constexpr void check_sub(difference_type n) noexcept { check_add(-n); }

	friend constexpr iterator operator+(const iterator& it, difference_type n) noexcept { iterator tmp = it; tmp += n; return tmp; }
	friend constexpr iterator operator+(difference_type n, const iterator& it) noexcept { iterator tmp = it; tmp += n; return tmp; }
	friend constexpr iterator operator-(const iterator& it, difference_type n) noexcept { iterator tmp = it; tmp += n; return tmp; }
	friend constexpr difference_type operator-(const iterator& lhs, const iterator& rhs) { check_parent(lhs, rhs); return std::distance(rhs, lhs); }

	friend constexpr auto operator<=>(const iterator&, const iterator&) noexcept = default;

private:

	parent_pointer m_parent = nullptr;
	container_iterator m_it;
};

template<class T, class _containar_T>
class basic_ringbuffer_any : public ringbuffer_base<T, _containar_T> {
public:

	using value_type = T;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;

	using container_base = _containar_T;
	using base = ringbuffer_base<value_type, container_base>;

	using iterator = typename base::iterator;
	using const_iterator = typename base::const_iterator;
	using reverse_iterator = typename base::reverse_iterator;
	using const_reverse_iterator = typename base::const_reverse_iterator;

	using base::base;

	constexpr size_t get_current_size() const { return base::m_current_size; }
	constexpr size_t get_index() const { return base::m_index; }
};

template<class T, std::ranges::random_access_range _container_T>
using basic_ringbuffer = basic_ringbuffer_any<T, _container_T>;

namespace ring {
	template<class T, size_t _capacity>
	using array = basic_ringbuffer<T, std::array<T, _capacity>>;

	template<class T>
	using vector = basic_ringbuffer<T, std::vector<T>>;
}

