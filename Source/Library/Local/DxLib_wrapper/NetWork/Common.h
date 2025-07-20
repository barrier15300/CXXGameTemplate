#pragma once
#include <vector>
#include <utility>

template<class T>
constexpr size_t GetTypeHashCode() {
	return typeid(T).hash_code();
}

enum NullEnum {};

enum class BasicType : size_t {
	_byte,
	_short,
	_int,
	_long,
	_float,
	_double,
	_string,
	_vector = 0x8000000000000000
};

template<typeis::Enum enumT = NullEnum>
struct Header {
	Header() : rawType(0) {}
	Header(enumT type) : Type(type) {}
	
	template<class T>
	bool IsSameType() {
		return rawType == GetTypeHashCode<T>();
	}

	size_t Size = 0;
	union {
		enumT Type;
		size_t rawType;
	};
};

struct Packet {

private:

	template <typename T, typename = void>
	struct is_vector_like : std::false_type {};

	template <typename T>
	struct is_vector_like<T, std::void_t<typename T::value_type>>
		: std::is_same<T, std::vector<typename T::value_type>> {};

public:

	Packet() = default;

	template<typeis::Enum enumT>
	Packet(enumT type, const void* src, size_t size) {
		Header head(type);
		head.Size = size;
		m_buffer.resize(HeaderSize + head.Size);
		std::memcpy(m_buffer.data(), &head, HeaderSize);
		std::memcpy(m_buffer.data() + HeaderSize, src, head.Size);
	}
	
	Packet(size_t hash, const void* src, size_t size) {
		Header<> head;
		head.Size = size;
		head.rawType = hash;
		m_buffer.resize(HeaderSize + head.Size);
		std::memcpy(m_buffer.data(), &head, HeaderSize);
		std::memcpy(m_buffer.data() + HeaderSize, src, head.Size);
	}

	template<typeis::Enum enumT>
	Packet(enumT type, const std::vector<uint8_t>& data) : Packet(type, data.data(), data.size()) {}

	template<typeis::Enum enumT, class T>
	Packet(enumT type, const std::vector<T>& data) : Packet(type, data.data(), data.size() * sizeof(T)) {}

	template<typeis::Enum enumT>
	Packet(enumT type, const std::string& data) : Packet(type, data.data(), data.size()) {}
	
	template<typeis::Enum enumT, class T>
	Packet(enumT type, const T& data) : Packet(type, std::addressof(data), sizeof(T)) {}

	Packet(const std::vector<uint8_t>& data) : Packet(GetTypeHashCode<std::vector<uint8_t>>(), data.data(), data.size()) {}

	template<class T>
	Packet(const std::vector<T>& data) : Packet(GetTypeHashCode<std::vector<T>>(), data.data(), data.size() * sizeof(T)) {}

	Packet(const std::string& data) : Packet(GetTypeHashCode<std::string>(), data.data(), data.size()) {}
	
	template<class T>
	Packet(const T& data) : Packet(GetTypeHashCode<T>(), std::addressof(data), sizeof(T)) {}

	const std::vector<uint8_t>& GetBuffer() {
		return m_buffer;
	}

	void SetBuffer(std::vector<uint8_t>&& buffer) {
		m_buffer = std::move(buffer);
	}

	template<typeis::Enum enumT = NullEnum>
	Header<enumT> GetHeader() const {
		if (m_buffer.size() < HeaderSize) {
			throw std::runtime_error("Buffer size is too small for header.");
		}
		return *reinterpret_cast<const Header<enumT>*>(m_buffer.data());
	}

	template<class T>
	T Get() const {
		if constexpr (std::is_same<T, std::string>::value) {
			return GetString();
		}
		if constexpr (is_vector_like<T>::value) {
			return GetArray<typename T::value_type>();
		}
		if (m_buffer.size() < HeaderSize + sizeof(T)) {
			throw std::runtime_error("Buffer size is too small for data.");
		}
		T data;
		std::memcpy(&data, m_buffer.data() + HeaderSize, sizeof(T));
		return data;
	}

	template<class T>
	T GetAt(size_t idx) const {
		if (m_buffer.size() < HeaderSize + sizeof(T) * (idx + 1)) {
			throw std::out_of_range("idx is out of buffer range.");
		}
		T data;
		std::memcpy(&data, m_buffer.data() + HeaderSize + sizeof(T) * idx, sizeof(T));
		return data;
	}

	template<class T>
	std::vector<T> GetArray() const {
		if (m_buffer.size() < HeaderSize + sizeof(T)) {
			throw std::runtime_error("Buffer size is too small for data vector.");
		}
		size_t dataSize = (m_buffer.size() - HeaderSize) / sizeof(T);
		std::vector<T> data(dataSize);
		std::memcpy(data.data(), m_buffer.data() + HeaderSize, m_buffer.size() - HeaderSize);
		return data;
	}

	std::string GetString() const {
		if (m_buffer.size() < HeaderSize + 1) {
			throw std::runtime_error("Buffer size is too small for string.");
		}
		return std::string(reinterpret_cast<const char*>(m_buffer.data() + HeaderSize), m_buffer.size() - HeaderSize);
	}

private:

	std::vector<uint8_t> m_buffer;
	constexpr static size_t HeaderSize = sizeof(Header<>);
};