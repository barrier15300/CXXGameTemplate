#pragma once
#include "TCPSocket.h"
#include <deque>

class TCPServer {

	TCPServer(const TCPServer&) = default;
	TCPServer& operator=(const TCPServer&) = default;

public:

	TCPServer() = default;
	~TCPServer() = default;

	void Start(int port) {
		if (isListening) {
			return;
		}
		PreparationListenNetWork(port);
		isListening = true;
	}
	void Stop() {
		if (!isListening) {
			return;
		}
		StopListenNetWork();
		isListening = false;
	}
	bool Pending() {
		if (!isListening) {
			return false;
		}

		int n = GetNewAcceptNetWork();
		if (n != -1) {
			pendingClients.push_back(n);
		}

		return !pendingClients.empty();
	}
	TCPSocket Accept() {
		TCPSocket ret;
		if (pendingClients.empty()) {
			return ret;
		}
		int h = pendingClients.front();
		pendingClients.pop_front();
		ret.handle = h;
		return ret;
	}

private:
	std::deque<int> pendingClients;
	static inline bool isListening = false;
};