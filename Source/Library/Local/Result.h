#pragma once
#include <optional>

template<class T, class E>
class Result : public std::optional<T> {
public:

	using base = std::optional<T>;

	using base::base;



};

#ifdef false

template<class T>
class Option {
public:

	using value_type = T;

	constexpr Option() noexcept {}
	constexpr Option(T v) noexcept : m_val(v), m_valid(true) {}
	[[maybe_unused]] constexpr Option(std::nullopt_t v) noexcept : m_val(T()), m_valid(false) {}

	explicit operator bool() const {
		return m_valid;
	}
	
	constexpr T &get() noexcept {
		return m_val;
	}

	constexpr const T &get() const noexcept {
		return m_val;
	}

	static T typeget() {
		return std::declval<value_type>();
	}

private:
	value_type m_val;
	bool m_valid;
};

template<class enumT, class... T>
class EnumOption {
public:

	constexpr EnumOption() noexcept {}
	constexpr EnumOption(T v) noexcept : m_val(v) {}
	[[maybe_unused]] constexpr EnumOption(std::nullopt_t v) noexcept : m_val(T()) {}

	explicit operator bool() const {
		return m_valid;
	}
	
	constexpr T &get() noexcept {
		return m_val;
	}

	constexpr const T &get() const noexcept {
		return m_val;
	}

	static T typeget() {
		return std::declval<value_type>();
	}

private:
	union a : std::tuple<T...> {
	} a;
};

template<class optT>
	requires requires (optT x) { x = optT(); x.typeget(); }
inline void match(optT v, void(*f)(decltype(optT::typeget()))) {
	
	while () {

	}

}

#endif