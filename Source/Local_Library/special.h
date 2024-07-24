#pragma once

template<class T>
struct rename_member final {

	rename_member() {};
	rename_member(T &v) : m_val(&v) {}

	constexpr T &operator=(const T &v) { *m_val = v; }
	constexpr T &operator=(T &&v) { *m_val = v; }

	constexpr operator T &() { return *m_val; }
	constexpr T *operator&() { return m_val; }
	
	constexpr operator const T &() const { return *m_val; }
	constexpr const T *operator&() const { return m_val; }

private:

	T *m_val = nullptr;
};