#pragma once

template<class T>
struct rename_member final {

	rename_member(T &v) : m_val(&v) {};
	
	rename_member(const rename_member &v) { m_val = v.m_val; };
	rename_member(rename_member &&v) { m_val = v.m_val; };
	
	rename_member &operator=(const rename_member &v) { *m_val = v; return *this; };
	rename_member &operator=(rename_member &&v) { *m_val = v; return *this; };
	rename_member &operator=(const rename_member &v) const { *m_val = v; return *this; };
	rename_member &operator=(rename_member &&v) const { *m_val = v; return *this; };
	
	constexpr operator T &() { return *m_val; }
	constexpr T *operator&() { return m_val; }
	constexpr operator const T &() const { return *m_val; }
	constexpr const T *operator&() const { return m_val; }

private:

	T *m_val = nullptr;
};