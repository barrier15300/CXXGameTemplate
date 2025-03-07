#pragma once
#include <iterator>
#include <array>
#include <vector>
#include <compare>

template<class,class>
class ringbuffer_iterator;

template<class T, class _container_T>
class ringbuffer_base : private _container_T {
public:

	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;

	using container_base = _container_T;

	using iterator = ringbuffer_iterator<T, _container_T>;
	using const_iterator = ringbuffer_iterator<const T, _container_T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	
	using container_base::container_base;

	friend class iterator;
	friend class const_iterator;

	constexpr iterator begin() noexcept {
		return iterator(container_base::_Unchecked_begin() + m_index, this);
	}
	
	constexpr iterator end() noexcept {
		return iterator(begin() + m_current_size, this);
	}
	
	constexpr const_iterator begin() const noexcept {
		return const_iterator(container_base::_Unchecked_begin() + m_index ,this);
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

	constexpr reference front() noexcept {
		return *begin();
	}

	constexpr reference back() noexcept {
		return *(end() - 1);
	}

	constexpr void write_back(const value_type &v) noexcept {
		*(begin() + m_current_size++) = v;

		if (!(m_current_size < size())) {
			m_current_size = size() - 1;
		}
		else {
			return;
		}

		if (!(++m_index < size())) {
			m_index = 0;
		}
	}

	constexpr void pop_front() noexcept {
		*(begin()) = value_type();
		
		if (!(++m_index < size())) {
			m_index = 0;
		}

		if (!(--m_current_size < size())) {
			m_current_size = 0;
		}
	}

protected:

#undef min
#undef max

	size_t m_index = 0;
	size_t m_current_size = 0;
};

template<class T, class _container_T>
class ringbuffer_iterator {
public:

	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;

	using base = ringbuffer_base<std::remove_cv_t<value_type>, _container_T>;
	using iterator = ringbuffer_iterator<value_type, _container_T>;
	
	constexpr ringbuffer_iterator() noexcept = default;
	constexpr explicit ringbuffer_iterator(pointer ptr) noexcept : m_ptr(ptr) {}
	constexpr ringbuffer_iterator(pointer ptr, const base *parent) noexcept : m_ptr(ptr), m_parent(parent) {}
	constexpr ringbuffer_iterator(iterator it, const base *parent) noexcept : m_ptr(it._Unwrapped()), m_parent(parent) {}
	constexpr ~ringbuffer_iterator() noexcept = default;

	constexpr iterator &operator=(const iterator&) noexcept = default;

	constexpr reference operator*() const { return *m_ptr; }
	constexpr reference operator->() const { return *m_ptr; }
	constexpr iterator &operator++() noexcept { check_add(1); return *this; }
	constexpr iterator operator++(int) noexcept { iterator tmp = *this; check_add(1); return tmp; }
	constexpr iterator &operator--() noexcept { check_sub(1); return *this; }
	constexpr iterator operator--(int) noexcept { iterator tmp = *this; check_sub(1); return tmp; }
	constexpr iterator &operator+=(difference_type n) noexcept { check_add(n); return *this; }
	constexpr iterator &operator-=(difference_type n) noexcept { check_sub(n); return *this; }

	friend constexpr void parent_check(const iterator &lhs, const iterator &rhs) {
		if (lhs.m_parent != rhs.m_parent) {
			throw std::exception("parent ptr is not equal");
		}
	}

	constexpr void check_add(difference_type n) noexcept {
		size_t size = m_parent->size();
		const_pointer _begin_ptr = m_parent->base::container_base::_Unchecked_begin();

		size_t diff = (((m_ptr - _begin_ptr) + n) % size);
		m_ptr = (pointer)(_begin_ptr + diff);

		//m_ptr += n & ((1 << std::bit_width<size_t>(size)) - 1);
		//if (m_ptr >= m_parent->end()) {
		//	m_ptr = m_parent->begin() + (m_ptr - m_parent->end());
		//}
	}

	constexpr void check_sub(difference_type n) noexcept { check_add(-n); }
	
	constexpr pointer _Unwrapped() const noexcept { return m_ptr; }

	friend constexpr iterator operator+(const iterator &it, difference_type n) noexcept { iterator temp = it; temp += n; return temp; }
	friend constexpr iterator operator+(difference_type n, const iterator &it) noexcept { iterator temp = it; temp += n; return temp; }
	friend constexpr iterator operator-(const iterator &it, difference_type n) noexcept { iterator temp = it; temp -= n; return temp; }
	friend constexpr size_t operator-(const iterator &lhs, const iterator &rhs) { parent_check(lhs, rhs); return lhs._Unwrapped() - rhs._Unwrapped(); }

	friend constexpr auto operator<=>(const iterator &, const iterator &) noexcept = default;

private:

	const base *m_parent = nullptr;
	pointer m_ptr = nullptr;
	
};

template<class T, class _containar_T>
class basic_RingBuffer : public ringbuffer_base<T, _containar_T> {
public:

	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;

	using base = ringbuffer_base<value_type, _containar_T>;
	using container_base = _containar_T;

	using iterator = base::iterator;
	using const_iterator = base::const_iterator;
	using reverse_iterator = base::reverse_iterator;
	using const_reverse_iterator = base::const_reverse_iterator;

	using base::base;

	size_t get_current_size() { return base::m_current_size; }
	size_t get_index() { return base::m_index; }
};

template<class T, size_t _capacity>
using RingArray = basic_RingBuffer<T, std::array<T, _capacity>>;

template<class T>
using RingVector = basic_RingBuffer<T, std::vector<T>>;

