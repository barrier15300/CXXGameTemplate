#pragma once
#include "Include.hpp"

class ServerTest : public IObjectBase {
public:
	
	virtual bool Init() override;
	virtual void Proc() override;
	virtual void Draw() override;
	virtual void End() override;

	TCPServer server;
	std::vector<TCPSocket> clients;
	RingArray<int, 8> RecvData;

	

};

bool ServerTest::Init() {
	server.Start(12345);
	return true;
}

void ServerTest::Proc() {
	if (server.Pending()) {
		clients.push_back(server.Accept());
	}

	for (auto&& c : clients) {
		if (c.Available() > 0) {
			auto pak = c.Receive();
			int ret = 0;
			if (pak.GetHeader().IsSameType<int>()) {
				ret = pak.Get<int>();
				RecvData.write_back(ret);
				++ret;
				c.Send(Packet(ret));
			}
		}
	}

	return;
}

void ServerTest::Draw() {

	int p = 0;
	for (auto&& elem : clients) {
		DrawFormatString(
			0,
			16 * p,
			Color3{ 255,255,255 },
			"%d",
			elem.GetRawHandle()
			);
		++p;
	}

	for (int i = 0; auto&& elem : RecvData) {
		DrawFormatString(
			0,
			16 + p * 16 + 16 * i,
			Color3{ 255, 255, 255 },
			"%d :  %d",
			i,
			elem
		);
		++i;
	}

	return;
}

void ServerTest::End() {
	server.Stop();
	return;
}