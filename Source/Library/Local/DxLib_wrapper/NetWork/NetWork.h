#pragma once
#include "TCPServer.h"

template<class T>
size_t GetTypeHashCode() {
	return typeid(T).hash_code();
}

struct NetUtils {

	template<typeis::Enum enumT>
	struct Header {
		Header(enumT type) : Type(type) {}

		uint32_t Size = 0;
		union {
			enumT Type;
			size_t rawType;
		};
	};

	struct Packet {

		template<typeis::Enum enumT>
		Packet(Header<enumT> head) {
			
		}
		
	private:

		bool m_available = false;
		std::vector<uint8_t> m_buffer;
	};
};
