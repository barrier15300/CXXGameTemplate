#pragma once
#include <string>
#include <vector>

namespace TextAnalize {

	std::string_view GetInBraket(std::string_view str, size_t off = 0, const char lb = '(',const char rb = ')') {
		size_t s = 0, e = ~0;
		size_t in = 0;
		for (size_t i = off; auto c : str.substr(off)) {
			if (c == lb) {
				if (in == 0) {
					s = i + 1;
				}
				++in;
			}
			else if (c == rb) {
				--in;
				if (in == 0) {
					e = i;
				}
			}
			
			if (e != ~0) {
				break;
			}
			++i;
		}

		if (e == ~0) { throw std::exception("doesn't right-braket"); }

		return str.substr(s, e - s);
	}
	
	std::string_view GetForChar(std::string_view str, char c, size_t off = 0) {
		return str.substr(off, str.find(c, off) - off);
	}

	std::vector<std::string_view> Split(std::string_view str, const char c) noexcept {
		size_t s = 0, e = 0;
		std::vector<std::string_view> ret;
		do {
			std::string_view item;
			e = str.find(c, s);
			item = str.substr(s, e - s);
			ret.push_back(item);
			s = e + 1;
		} while (e != std::string_view::npos);
		return ret;
	}

	std::vector<std::string_view> Split_NoEmpty(std::string_view str, const char c) noexcept {
		size_t s = 0, e = 0;
		std::vector<std::string_view> ret;
		do {
			std::string_view item;
			e = str.find(c, s);
			item = str.substr(s, e - s);
			if (!item.empty()) { ret.push_back(item); }
			s = e + 1;
		} while (e != std::string_view::npos);
		return ret;
	}

	
	class TextAnalizer {
	public:

		TextAnalizer(){}

		void Parse(std::string &str) {

		}

		

	};
}