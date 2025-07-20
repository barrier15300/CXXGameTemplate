#pragma once
#include "Include.hpp"

class ClientTest : public IObjectBase {
public:
	virtual bool Init() override;
	virtual void Proc() override;
	virtual void Draw() override;
	virtual void End() override;

	TCPSocket server;
	int current = 0;
	RingArray<int, 8> RecvData;
};

bool ClientTest::Init() {
	return true;
}

void ClientTest::Proc() {
	if (Input.Keyboard[Keys::Up].Down()) {
		++current;
	}
	if (Input.Keyboard[Keys::Down].Down()) {
		--current;
	}

	if (Input.Keyboard[Keys::C].Down()) {
		server.Connect("106.179.19.81", 12345);
	}

	if (Input.Keyboard[Keys::D].Down()) {
		server.Close();
	}

	if (Input.Keyboard[Keys::I].Down()) {
		std::vector<byte> buffer;
		buffer.resize(4);
		memcpy(buffer.data(), &current, 4);
		server.Send(buffer);
	}

	if (server.Available() > 0) {
		std::vector<byte> buffer = server.Receive();
		int recv = 0;
		memcpy(&recv, buffer.data(), 4);
		RecvData.write_back(recv);
	}

	return;
}

void ClientTest::Draw() {

	DrawFormatString(0, 0, Color3{ 255,255,255 }, "current: %d", current);
	DrawFormatString(0, 16, Color3{ 255,255,255 }, "connected: %d", server.IsConnected());

	for (int i = 0; auto&& elem : RecvData) {
		DrawFormatString(
			0,
			48 + i * 16,
			Color3{ 255,255,255 },
			"%d :  %d",
			i,
			elem
		);
		++i;
	}

	return;
}

void ClientTest::End() {
	return;
}