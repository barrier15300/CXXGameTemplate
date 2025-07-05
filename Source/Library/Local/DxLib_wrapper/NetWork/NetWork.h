#pragma once
#include "TCPServer.h"

template<class T>
size_t GetTypeHashCode() {
	return typeid(T).hash_code();
}

struct NetUtils {
	
	template<class T>
	struct DataPacket {
		size_t header = GetTypeHashCode<T>();
		T data;
	};

	template<class T>
	static std::vector<byte> ToBytes(const T& fromdata) {
		union {
			DataPacket<T> data;
			std::array<byte, sizeof(DataPacket<T>)> _rawbuffer{};
		};
		data.data = *reinterpret_cast<T*>(this);
		std::vector<byte> buffer(_rawbuffer.begin(), _rawbuffer.end());
		return buffer;
	}

	template<class T>
	static std::vector<byte> ToBytesNonHedaer(const T& fromdata) {
		union {
			T data;
			std::array<byte, sizeof(T)> _rawbuffer{};
		};
		data = *reinterpret_cast<T*>(this);
		std::vector<byte> buffer(_rawbuffer.begin(), _rawbuffer.end());
		return buffer;
	}

	template<class T>
	static T FromBytes(const std::vector<byte>& buf) {
		if (buf.size() < sizeof(DataPacket<T>)) {
			throw std::invalid_argument("Buffer size is too small to contain DataPacket.");
		}
		union {
			DataPacket<T> data;
			std::array<byte, sizeof(DataPacket<T>)> _rawbuffer{};
		};
		std::copy(buf.begin(), buf.begin() + sizeof(DataPacket<T>), _rawbuffer.begin());
		if (data.header == GetTypeHashCode<T>()) {
			throw std::invalid_argument("Header does not match expected type hash code.");
		}
		return data.data;
	}

	static size_t FromBytesToHeader(const std::vector<byte>& buf) {
		if (buf.size() < sizeof(size_t)) {
			throw std::invalid_argument("Buffer size is too small to contain T.");
		}
		union {
			size_t data;
			std::array<byte, sizeof(size_t)> _rawbuffer{};
		};
		std::copy(buf.begin(), buf.end(), _rawbuffer.begin());
		return data;
	}
};
