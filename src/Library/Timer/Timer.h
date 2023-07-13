#pragma once
#include "include.h"

class Timer {
	
	std::chrono::high_resolution_clock::time_point m_memtp;

public:
	Timer();
	~Timer();

	long long getnowtime(const short _type);
	long long getrecordingtime(const short _type);
	
	using seconds = std::chrono::seconds;
	using milliseconds = std::chrono::milliseconds;
	using microseconds = std::chrono::microseconds;
	using nanoseconds = std::chrono::nanoseconds;

	const long long sv_second = 1;
	const long long sv_millisecond = 1000;
	const long long sv_microsecond = 1000000;
	const long long sv_nanosecond = 1000000000;

	static const short t_seconds = 0x01;
	static const short t_milliseconds = 0x02;
	static const short t_microseconds = 0x03;
	static const short t_nanoseconds = 0x04;

};
