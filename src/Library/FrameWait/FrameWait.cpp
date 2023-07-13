#include "FrameWait.h"

FrameWait::FrameWait(int framerate) {
	m_frametime = 1. / framerate;
}

int FrameWait::GetNowFrameValue() {
	return (int)(m_t.getnowtime(Timer::t_nanoseconds) / (m_frametime * m_t.sv_nanosecond));
}

void FrameWait::Sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(m_t.getnowtime(Timer::t_milliseconds) % static_cast<int>(m_frametime * m_t.sv_millisecond)));
	while (m_memframe == GetNowFrameValue()) { }
	m_memframe = GetNowFrameValue();
}
