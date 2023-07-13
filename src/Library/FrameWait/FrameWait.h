#pragma once
#include "include.h"

class FrameWait final {

	FrameWait(int framerate);
	~FrameWait() = default;

	FrameWait(const FrameWait&) = delete;
	FrameWait& operator=(const FrameWait&) = delete;
	FrameWait(FrameWait&&) = delete;
	FrameWait& operator=(FrameWait&&) = delete;

	int m_memframe = 0;
	double m_frametime = 0;
	Timer m_t;

public:

	static FrameWait& GetInstance() {
		static FrameWait _instance = FrameWait(GetRefreshRate());
		return _instance;
	}

	int GetNowFrameValue();
	void Sleep();

	inline void SetFrameRate(const int& val) { if (val > 0) { m_frametime = 1. / val; } }

};

#define FRAMEWAIT FrameWait::GetInstance()