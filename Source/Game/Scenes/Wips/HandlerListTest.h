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
		unpack1 = pak.Get<std::string>();
		log << __FUNCTION__ << std::endl;
	}

	void pak2_unpack(Packet pak) {
		unpack2 = pak.Get<int>();
		log << __FUNCTION__ << std::endl;
	}
	
	void pak3_unpack(Packet pak) {
		unpack3 = pak.Get<std::vector<int>>();
		log << __FUNCTION__ << std::endl;
	}
	
	std::string unpack1;
	int unpack2 = 5;
	std::vector<int> unpack3;

	std::random_device engine;
	std::uniform_int_distribution<> dist = std::uniform_int_distribution(1, 3);
	std::stringstream log;
};

template<typename>
struct func_parent_base;

template<class T, class R, class ...Args>
struct func_parent_base<R (T::*)(Args...)> {
	using type = T;
};

#define member_func_ptr(p) (func_parent_base<decltype(p)*>::type::p)

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
		auto p = packets[dist(engine)];
		list[p.GetHeader().rawType](p);
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

