#pragma once
#include <string>
#include <vector>

inline std::vector<std::string> split(const std::string& str, char delim) {
	std::vector<std::string> ret;
	size_t index = 0, findindex = 0;
	while (1) {
		ret.push_back(str.substr(index, (findindex = str.find_first_of(delim, index + 1)) - index));
		index = findindex + 1;
		if (findindex == std::string::npos) {
			break;
		}
	};
	return ret;
}