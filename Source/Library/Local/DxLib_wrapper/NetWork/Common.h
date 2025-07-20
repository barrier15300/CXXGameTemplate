#pragma once
#include <vector>

template<class T>
size_t GetTypeHashCode() {
	return typeid(T).hash_code();
}

struct NetUtils {

	template<typeis::Enum enumT>
	struct Header {
		Header(enumT type) : Type(type) {}

		uint32_t Size = 0;

		enumT GetType() const {
			return Type;
		}
		size_t GetRawType() const {
			return rawType;
		}

	private:
		union {
			enumT Type;
			size_t rawType;
		};
	};

	struct Packet {

		template<typeis::Enum enumT>
		Packet(enumT type, const void* src, size_t size) {
			Header<enumT> head(type);
			head.Size = size;
			m_buffer.resize(sizeof(head) + size);
			std::memcpy(m_buffer.data(), &head, sizeof(head));
			std::memcpy(m_buffer.data() + sizeof(head), src, size);
		}

		void* GetBuffer() {
			return m_buffer.data();
		}

	private:

		bool m_available = false;
		std::vector<uint8_t> m_buffer;
	};
};
