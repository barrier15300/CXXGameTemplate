#pragma once
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"
#include "exstring.h"

template<size_t Size = 1>
class static_string {
public:
	static constexpr int length = Size - 1;

	constexpr static_string(const char(&s_literal)[Size]) {
		for (int i = 0; i < Size; i++) buf[i] = s_literal[i];
		buf[length] = '\0';
	}

	char buf[Size];
};

template<static_string Filepath>
class __DataStorage_sc {
	static constexpr static_string _filepath = Filepath;
	std::ifstream ifs;
	std::ofstream ofs;
public:

	__DataStorage_sc() { Read(); }
	~__DataStorage_sc() {
		Write();
	};

	nlohmann::ordered_json Data;

	void Read() {
		ifs.open(_filepath.buf);
		if (!ifs.is_open()) {
			return;
		}

		ifs >> Data;

		ifs.close();
	}

	void Write() {
		ofs.open(_filepath.buf);
		if (!ofs.is_open()) {
			return;
		}

		ofs << std::setw(4) << Data;

		ofs.close();
	}
};

template<static_string Filepath = static_string{"none.json"}>
class DataStorage {
public:

	template<class _type = int>
	_type& Get(const std::string& keyname, _type&& defaultval = _type()) {
#define STATIC_MESSAGE "This data type is not available in json."
		if constexpr (std::is_integral_v<_type>) { static_assert(std::is_same_v<_type, int64_t> || std::is_same_v<_type, bool>, STATIC_MESSAGE); } else {}
		if constexpr (std::is_floating_point_v<_type>) { static_assert(std::is_same_v<_type, double_t>, STATIC_MESSAGE); } else {}
#undef STATIC_MESSAGE

		auto *accessdata = &Storage.Data;
		auto keys = split(keyname, '/');

		for (size_t i = 0, size = keys.size() - 1; i < size; ++i) {
			auto& key = keys[i];
			if (accessdata->find(key) == accessdata->end()) {
				(*accessdata)[key] = nlohmann::json{};
			}
			accessdata = &(*accessdata)[key];
		}
		
		auto& key = keys.back();
		if (accessdata->find(key) == accessdata->end()) {
			(*accessdata)[key] = defaultval;
		}
		return *(*accessdata)[key].get_ptr<_type*>();
	}

	inline static __DataStorage_sc<Filepath> Storage = __DataStorage_sc<Filepath>();
};
