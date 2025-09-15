#include "function_ref.h"

constexpr int add_func(int l, int r) { return l + r + l + r + l + r + l + r; }

bool FunctionRefTest::Init() {

	auto f = [](int l, int r) { return l + r + l + r + l + r + l + r; };

	std::function<int(int, int)> add = f;
	function_ref<int(int, int)> add_ref = f;
	function_ref<int(int, int)> add_move = [](int l, int r) { return l + r + l + r + l + r + l + r; };
	function_ref<int(int, int)> add_func_ref = add_func;

	constexpr size_t count = 10000;

	Timer t;
	size_t _ret = 0;

	t.Restart();
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < count; ++j) {
			_ret += add(i, j);
		}
	}

	time[0] = t.Elapsed().Second();
	ret[0] = _ret;
	_ret = 0;

	t.Restart();
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < count; ++j) {
			_ret += add_ref(i, j);
		}
	}

	time[1] = t.Elapsed().Second();
	ret[1] = _ret;
	_ret = 0;

	t.Restart();
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < count; ++j) {
			_ret += add_move(i, j);
		}
	}

	time[2] = t.Elapsed().Second();
	ret[2] = _ret;
	_ret = 0;

	t.Restart();
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < count; ++j) {
			_ret += add_func_ref(i, j);
		}
	}

	time[3] = t.Elapsed().Second();
	ret[3] = _ret;
	_ret = 0;

	t.Restart();
	for (size_t i = 0; i < count; ++i) {
		for (size_t j = 0; j < count; ++j) {
			_ret += i + j + i + j + i + j + i + j;
		}
	}
	time[4] = t.Elapsed().Second();
	ret[4] = _ret;
	_ret = 0;

    return true;
}

void FunctionRefTest::Proc() {
    return;
}

void FunctionRefTest::Draw() {
	print();
    return;
}

void FunctionRefTest::End() {
    return;
}