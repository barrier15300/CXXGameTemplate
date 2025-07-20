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
	void Send(Packet packet) {
		auto&& buf = packet.GetBuffer();
		NetWorkSend(*this, buf.data(), buf.size());
	}
	Packet Receive() {
		int size = Available();
		std::vector<byte> buffer(size);
		NetWorkRecv(*this, buffer.data(), size);
		Packet packet;
		packet.SetBuffer(std::move(buffer));
		return packet;
	}
	int Available() const {
		return GetNetWorkDataLength(*this);
	}
	bool IsConnected() const {
		return GetNetWorkAcceptState(*this);
	}
};