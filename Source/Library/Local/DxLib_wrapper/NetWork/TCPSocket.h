#pragma once
#include "../Helper/Helper.h"
#include "../Value/Value.h"
#include <string>
#include <vector>

#include "Common.h"

class TCPServer;

class TCPSocket : public DXHandle<DXHandleType::NetWork, CloseNetWork> {
public:

	friend TCPServer;

	using DXHandle::DXHandle;
	
	bool Connect(const std::string& address, unsigned short port) {
		if (address.empty() || port == 0) {
			return false;
		}
		IPDATA ip{};
		GetHostIPbyName(address.c_str(), &ip);
		Init(ConnectNetWork(ip, port));
		if (*this == -1) {
			return false;
		}
		return true;
	}
	void Close() {
		if (IsConnected()) {
			CloseNetWork(*this);
			Init(HandleNull);
		}
	}
	void Send(const std::vector<byte> &buffer) {
		NetWorkSend(*this, buffer.data(), buffer.size());
	}
	std::vector<byte> Receive() {
		int size = Available();
		std::vector<byte> buffer;
		buffer.resize(size);
		NetWorkRecv(*this, buffer.data(), size);
		return buffer;
	}
	int Available() const {
		return GetNetWorkDataLength(*this);
	}
	bool IsConnected() const {
		return GetNetWorkAcceptState(*this);
	}

protected:

	struct ReceiveData {

		void Parse(byte* dataptr) {
			auto p = reinterpret_cast<uint32_t*>(dataptr);
			Header = *p++;
			Size = *p++;
			Data.reserve(Size);
			std::copy(p, p + Size, std::back_inserter(Data));
		}

		uint32_t Header = 0;
		uint32_t Size = 0;
		std::vector<byte> Data;
	};

};