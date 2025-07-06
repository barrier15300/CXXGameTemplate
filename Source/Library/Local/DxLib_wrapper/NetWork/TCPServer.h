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
		listeningPort = port;
		isListening = true;
	}
	void Stop() {
		if (!isListening) {
			return;
		}
		StopListenNetWork();
		listeningPort = 0;
		isListening = false;
	}
	bool Pending() {
		if (!isListening) {
			return false;
		}

		int n = GetNewAcceptNetWork();
		if (n != TCPSocket::HandleNull) {
			pendingClients.push_back(n);
		}

		return !pendingClients.empty();
	}
	TCPSocket Accept() {
		TCPSocket ret;
		if (pendingClients.empty()) {
			return ret;
		}
		ret.Init(pendingClients.front());
		pendingClients.pop_front();
		return ret;
	}

private:
	std::deque<int> pendingClients;
	static inline bool isListening = false;
	static inline uint16_t listeningPort = 0;
};