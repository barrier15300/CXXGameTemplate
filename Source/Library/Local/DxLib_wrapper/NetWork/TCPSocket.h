#pragma once
#include "DxLib.h"
#include <string>
#include <vector>

class TCPServer;

class TCPSocket {

	TCPSocket(const TCPSocket&) = default;
	TCPSocket& operator=(const TCPSocket&) = default;
	
	friend TCPServer;

public:

	TCPSocket() = default;
	~TCPSocket() = default;
	bool Connect(std::string address, unsigned short port) {
		if (address.empty() || port == 0) {
			return false;
		}
		IPDATA ip{};
		GetHostIPbyName(address.c_str(), &ip);
		handle = ConnectNetWork(ip, port);
		if (handle == -1) {
			return false;
		}
		return true;
	}
	void Close() {
		if (handle != -1) {
			CloseNetWork(handle);
			handle = -1;
		}
	}
	void Send(const std::vector<byte> &buffer) {
		NetWorkSend(handle, buffer.data(), buffer.size());
	}
	std::vector<byte> Receive() {
		int size = Available();
		std::vector<byte> buffer;
		buffer.resize(size);
		NetWorkRecv(handle, buffer.data(), size);
		return buffer;
	}
	int Available() const {
		return GetNetWorkDataLength(handle);
	}
	bool IsConnected() const {
		return GetNetWorkAcceptState(handle);
	}
	int GetHandle() const {
		return handle;
	}

protected:

	int handle = -1;
};