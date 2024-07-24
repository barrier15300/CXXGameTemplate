#pragma once
#include "DxLib.h"

class Timer {
public:

	Timer(bool startflag = false) :
		m_tp(0), m_stp(0),
		m_isrunning(false), m_isstopping(false)
	{ if (startflag) { this->Start(); } }

	enum Type {
		second      = 1000000000,
		millisecond = 1000000,
		microsecond = 1000,
		nanosecond  = 1
	};

	void Start() { m_tp = GetNowNanoSeconds() - m_stp; m_isrunning = true; m_isstopping = false; }
	void Stop() { m_stp = GetNowNanoSeconds(); m_isstopping = true; }
	void Reset() { *this = Timer(); }
	void Restart() {
		this->Reset();
		this->Start();
	}

	double Elapsed(Type divscale = millisecond) const {
		if (m_isrunning) { return 0; }
		return ((m_isstopping ? m_stp - m_tp : GetNowNanoSeconds()) - m_tp) / static_cast<double>(divscale);
	}

	ULONGLONG ElapsedFrameCount() const {
		return (ULONGLONG)(Elapsed(second) * m_framerefreshrate);
	}
	double ElapsedFrameTime(Type scale = second) const {
		return (ElapsedFrameCount() / static_cast<double>(m_framerefreshrate)) * (second / scale);
	}

	static void SetFrameRefleshRate(int rate) {
		m_framerefreshrate = rate;
	}

private:
	static ULONGLONG GetNowNanoSeconds() { return ConvSysPerformanceCountToNanoSeconds(GetNowSysPerformanceCount()); }
	inline static int m_framerefreshrate = GetRefreshRate();

	bool m_isrunning, m_isstopping;
	ULONGLONG m_tp, m_stp;
};