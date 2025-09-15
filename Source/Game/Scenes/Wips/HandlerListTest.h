#pragma once
#include "Include.hpp"

class HandlerListTest : public IObjectBase {
public:
	virtual bool Init() override;
	virtual void Proc() override;
	virtual void Draw() override;
	virtual void End() override;

	HandlerList<void(Packet)> list;

	std::vector<Packet> packets = {
		Packet(0, nullptr),
		Packet(1, "hello"),
		Packet(2, 60),
		Packet(3, std::vector<int>{3,4,6,7,8})
	};

	void pak1_unpack(Packet pak) {
		log << __FUNCTION__ << std::endl;
		log << pak.Get<std::string>() << std::endl;
	}

	void pak2_unpack(Packet pak) {
		log << __FUNCTION__ << std::endl;
		log << fmt::format("{}", pak.Get<int>()) << std::endl;
	}
	
	void pak3_unpack(Packet pak) {
		log << __FUNCTION__ << std::endl;
		log << fmt::format("{}{}{}", "{", fmt::join(pak.Get<std::vector<int>>(), ","), "}") << std::endl;
	}
	
	std::random_device engine;
	std::uniform_int_distribution<> dist = std::uniform_int_distribution(1, 3);
	std::stringstream log;
};

bool HandlerListTest::Init() {

	list.Regist(
		{ 1, { &HandlerListTest::pak1_unpack, *this} }
	);

	list.Regist(
		{ 2, { &HandlerListTest::pak2_unpack, *this} }
	);

	list.Regist(
		{ 3, { &HandlerListTest::pak3_unpack, *this} }
	);

	constexpr size_t count = 10;
	
	for (size_t i = 0; i < count; ++i) {
		auto&& p = packets[dist(engine)];
		list[p.GetHeader().rawType](p);
		log << i << std::endl;
	}

	return true;
}

void HandlerListTest::Proc() {

	return;
}

void HandlerListTest::Draw() {

	DrawString(0, 0, log.str().c_str(), Color3{ 255,255,255 });

	return;
}

void HandlerListTest::End() {
	return;
}

