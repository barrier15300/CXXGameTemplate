#pragma once
#include <string>
#include <vector>

inline std::vector<std::string_view> split(std::string_view str, char delim) {
	std::vector<std::string_view> ret;
	size_t index = 0, findindex = 0;
	do {
		ret.push_back(str.substr(index, (findindex = str.find_first_of(delim, index + 1)) - index));
		index = findindex + 1;
	} while (findindex != std::string_view::npos);
	return ret;
}