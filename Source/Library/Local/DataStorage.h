#pragma once
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"
#include "exstring.h"

template<size_t Size>
class static_string {
public:
	static constexpr int length = Size - 1;

	constexpr static_string(const char(&s_literal)[Size]) {
		for (int i = 0; i < Size; i++) buf[i] = s_literal[i];
		buf[length] = '\0';
	}

	char buf[Size];
};

namespace Storage {
	template<class T>
	concept ValueType = std::is_copy_constructible_v<T>;

	using namespace nlohmann;

	template<static_string Filepath>
	class __Data_sc {
		static inline std::filesystem::path _filepath = Filepath.buf;
		std::ifstream ifs;
		std::ofstream ofs;
	public:

		__Data_sc() { Read(); };
		~__Data_sc() { Write(); };

		ordered_json Data;

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

		ordered_json *TraverseToKey(const std::string &key) {
			ordered_json *data = &Data;
			const auto keys = split(key, '/');

			for (size_t i = 0; i < keys.size(); ++i) {
				auto &currentKey = keys[i];

				if (data->find(currentKey) == data->end()) {
					(*data)[currentKey] = json{};
				}
				data = &(*data)[currentKey];
			}

			return data;
		}

		template<ValueType _type>
		ordered_json &KeyFind(const std::string &keyname, const _type &defaultval = _type()) {
			ordered_json *accessdata = &Data;

			ordered_json *target = TraverseToKey(keyname);

			if (target->empty()) {
				(*target) = defaultval;
			}

			return (*target);
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

	template<class T, class fT>
	concept FromValueType = std::constructible_from<T, fT>;

	template<static_string Filepath = "none.json">
	class Data {
		using StorageType = Data<Filepath>;
		using Storage_sc_Type = __Data_sc<Filepath>;

	public:

		template<ValueType T, static_string Jsonpath>
		struct Value {

			explicit Value(const T &defaultval) { m_value = StorageType::Storage.Get<T>(Jsonpath.buf, defaultval); }
			explicit Value(T &&defaultval) { m_value = StorageType::Storage.Get<T>(Jsonpath.buf, defaultval); }
			~Value() { StorageType::Storage.Set(Jsonpath.buf, m_value); }

			template<FromValueType<T> fT>
			Value &operator=(const fT &lhs) & { m_value = lhs; return *this; }

			template<FromValueType<T> fT>
			Value &operator=(fT &&lhs) & { m_value = std::forward<fT>(lhs); return *this; }

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

		inline static Storage_sc_Type Storage = Storage_sc_Type();
	};
}
