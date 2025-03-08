#pragma once
#include <string>
#include <vector>

constexpr std::vector<std::string_view> split(std::string_view str, std::string_view delim) {
	std::vector<std::string_view> ret;
	size_t index = 0, findindex = 0;
	do {
		ret.push_back(str.substr(index, (findindex = str.find(delim, index + 1)) - index));
		index = findindex + delim.size();
	}
	while (findindex != std::string_view::npos);
	return ret;
}

constexpr std::vector<std::string_view> split(std::string_view str, char delim) {
	char delim_str[2] = {delim, '\0'};
	return split(str, delim_str);
}

