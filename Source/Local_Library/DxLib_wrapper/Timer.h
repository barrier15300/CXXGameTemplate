#pragma once
#include "DxLib.h"

class Timer {
public:

	struct ElapsedTime;

	Timer(bool startflag = false) :
		m_timepoint(0), m_stoptime(0),
		m_isrunning(false), m_isstopping(false)
	{ if (startflag) { this->Start(); } }

	void Start() {
		size_t nanotime = GetNowNanoSeconds();
		if (m_isstopping) {
			m_timepoint = nanotime - (m_stoptime - m_timepoint);
		}
		else {
			m_timepoint = m_isrunning ? m_timepoint : nanotime;
		}
		m_isrunning = true;
		m_isstopping = false;
	}
	void Stop() {
		if (!m_isrunning || m_isstopping) {
			return;
		}
		m_stoptime = GetNowNanoSeconds();
		m_isstopping = true;
	}
	void Reset() { *this = Timer(); }
	void Restart() {
		this->Reset();
		this->Start();
	}

	ElapsedTime Elapsed() const {
		if (!m_isrunning) { return 0; }
		return ElapsedTime((m_isstopping ? m_stoptime : GetNowNanoSeconds()) - m_timepoint);
	}

	static void SetFrameRefleshRate(int rate) {
		m_framerefreshrate = rate;
	}

private:
	
	enum class Type{
		second,
		millisecond,
		microsecond,
		nanosecond,
		framecount,
		frametime
	};

	struct ElapsedTime {

		ElapsedTime(size_t time) : t(static_cast<double>(time)) {}

		double Second() const {
			return t / 1000000000;
		}
		double MilliSecond() const {
			return t / 1000000;
		}
		double MicroSecond() const {
			return t / 1000;
		}
		double NanoSecond() const {
			return t;
		}
		ULONGLONG FrameCount() const {
			return (ULONGLONG)(Second() * m_framerefreshrate);
		}
		double FrameTime() const {
			return (FrameCount() / static_cast<double>(m_framerefreshrate));
		}

	private:
		double t;
	};

	static size_t GetNowNanoSeconds() { return ConvSysPerformanceCountToNanoSeconds(GetNowSysPerformanceCount()); }
	inline static int m_framerefreshrate = GetRefreshRate();

	bool m_isrunning, m_isstopping;
	size_t m_timepoint, m_stoptime;
};