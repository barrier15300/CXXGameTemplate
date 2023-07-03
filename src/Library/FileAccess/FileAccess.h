#pragma once
#include "include.h"

enum class FAO {
	rc_slash,
	rc_sharp,
	rc_slas,
	rc_all
};

class FileAccess {
public:

	FileAccess(std::string path);
	FileAccess(std::string path, FAO option);
	~FileAccess();

	std::string operator[](size_t index);

	inline size_t GetSize() { return m_list.size(); }

private:

	std::vector<std::string> m_list;
};