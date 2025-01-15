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

	char buf[Size]{};
};

namespace Storage {
	template<class T>
	concept ValueType = std::is_copy_constructible_v<T>;

	template<static_string Filepath>
	class __Data_sc {
		static inline std::filesystem::path _filepath = Filepath.buf;
		std::ifstream ifs;
		std::ofstream ofs;
	public:

		__Data_sc() { Read(); }
		~__Data_sc() { Write(); };

		nlohmann::ordered_json Data;

		void Read() {
			ifs.open(_filepath);
			if (!ifs.is_open()) {
				// No Touch
				return;
			}

			try {
				ifs >> Data;
			}
			catch (const std::exception &e) {
				return;
			}

			ifs.close();
		}

		void Write() {
			if (_filepath.has_parent_path()) {
				std::filesystem::create_directories(_filepath.parent_path());
			}

			ofs.open(_filepath);
			if (!ofs.is_open()) {
				return;
			}

			ofs << std::setw(4) << Data;

			ofs.close();
		}

		auto* TraverseToKey(const std::vector<std::string> &keys) {
			auto *data = &Data;

			for(size_t i = 0; i < keys.size() - 1; ++i) {
			
				auto &key = keys[i];
				
				if (data->find(key) == data->end()) {
					(*data)[key] = nlohmann::json{};
				}
				data = &(*data)[key];
			}
			
			return data;
		}

		template<ValueType _type>
		auto &KeyFind(const std::string &keyname, const _type &defaultval = _type()) {
			auto *accessdata = &Data;
			const auto keys = split(keyname, '/');

			auto* target = TraverseToKey(keys);

			auto &key = keys.back();
			if (target->find(key) == target->end()) {
				(*target)[key] = defaultval;
			}

			return (*target)[key];
		}

		template<ValueType _type>
		_type Get(const std::string &keyname, const _type &defaultval = _type()) {
			return KeyFind(keyname, defaultval).get<_type>();
		}

		template<ValueType _type>
		void Set(const std::string &keyname, const _type &setval) {
			KeyFind<_type>(keyname) = setval;
		}
	};

	template<static_string Filepath = static_string{"none.json"} >
	class Data {
		using StorageType = Data<Filepath>;
		using Storage_sc_Type = __Data_sc<Filepath>;
		
	public:

		template<class T, static_string Jsonpath>
		struct Value {

			Value(const T &defaultval) { m_value = StorageType::Storage.Get<T>(Jsonpath.buf, defaultval); }
			Value(T &&defaultval) { m_value = StorageType::Storage.Get<T>(Jsonpath.buf, defaultval); }
			~Value() { StorageType::Storage.Set(Jsonpath.buf, m_value); }

			template<std::constructible_from<T> fT>
			Value &operator=(const fT &lhs) & { m_value = lhs; return *this; }
			
			template<std::constructible_from<T> fT>
			Value &operator=(fT &&lhs) & { m_value = std::move(lhs); return *this; }

			operator T &() & {
				return m_value;
			}
			operator const T &() const & {
				return m_value;
			}

			T &Get() & { return m_value; }
			const T &Get() const & { return m_value; }

			inline static T m_value = T();
		};

		inline static __Data_sc<Filepath> Storage = __Data_sc<Filepath>();
	};
}
