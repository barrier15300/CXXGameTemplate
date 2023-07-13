#include "Timer.h"

using namespace std::chrono;

Timer::Timer() {
	m_memtp = high_resolution_clock::now();
}

Timer::~Timer() {

}

long long Timer::getnowtime(const short _type) {
	switch (_type) {
	case 0x01:
		return duration_cast<Timer::seconds>(high_resolution_clock::now().time_since_epoch()).count();
		break;
	case 0x02:
		return duration_cast<Timer::milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
		break;
	case 0x03:
		return duration_cast<Timer::microseconds>(high_resolution_clock::now().time_since_epoch()).count();
		break;
	case 0x04:
		return duration_cast<Timer::nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
		break;
	}
	return 0;
}

long long Timer::getrecordingtime(const short _type) {
	switch (_type) {
	case 0x01:
		return duration_cast<Timer::seconds>(high_resolution_clock::now() - m_memtp).count();
		break;
	}
	switch (_type) {
	case 0x02:
		return duration_cast<Timer::milliseconds>(high_resolution_clock::now() - m_memtp).count();
		break;
	}
	switch (_type) {
	case 0x03:
		return duration_cast<Timer::microseconds>(high_resolution_clock::now() - m_memtp).count();
		break;
	}
	switch (_type) {
	case 0x04:
		return duration_cast<Timer::nanoseconds>(high_resolution_clock::now() - m_memtp).count();
		break;
	}
	return 0;
}
