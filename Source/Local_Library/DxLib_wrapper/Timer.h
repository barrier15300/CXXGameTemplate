#pragma once
#include "DxLib.h"

class Timer {
public:

	struct ElapsedTime;

	Timer(bool startflag = false) :
		m_timepoint(0), m_stoptime(0),
		m_isstopping(false)
	{
		if (startflag) {
			this->Start();
		}
	}

	void Start() {
		size_t nanotime = GetNowNanoSeconds();
		if (m_isstopping) {
			m_timepoint = nanotime - (m_stoptime - m_timepoint);
		}
		else if (!Running()) {
			m_timepoint = nanotime;
		}
		m_isstopping = false;
	}
	void Stop() {
		if (!Running() || m_isstopping) { return; }
		m_stoptime = GetNowNanoSeconds();
		m_isstopping = true;
	}
	void Reset() {
		*this = Timer();
	}
	void Restart() {
		this->Reset();
		this->Start();
	}

	bool Running() const {
		return m_timepoint != 0;
	}

	ElapsedTime Elapsed() const {
		if (!Running()) { return 0; }
		return ElapsedTime((m_isstopping ? m_stoptime : GetNowNanoSeconds()) - m_timepoint);
	}

	static void SetFrameRefleshRate(double rate) {
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

		operator double() {
			return Second();
		}

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
		size_t FrameCount() const {
			return static_cast<size_t>(Second() * m_framerefreshrate);
		}
		double FrameTime() const {
			return (FrameCount() / m_framerefreshrate);
		}

	private:
		double t;
	};

	static size_t GetNowNanoSeconds() {
		size_t nanosecond = static_cast<size_t>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch()
			).count()
			);
		return nanosecond;
	}
	inline static double m_framerefreshrate = GetRefreshRate();

	bool m_isstopping;
	size_t m_timepoint, m_stoptime;
};