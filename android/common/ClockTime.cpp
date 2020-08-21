#include "ClockTime.h"



ClockTime::ClockTime()
	: mBaseTimeMs(0)
	, mIsPause(false)
	, mTimePoint()
{
}


ClockTime::~ClockTime()
{
}

void ClockTime::setTimeMs(int64_t baseTimeMs)
{
	mBaseTimeMs = baseTimeMs;
	mTimePoint = std::chrono::high_resolution_clock::now();
}

int64_t ClockTime::getTimeMs() const
{
	if (mIsPause) {
		return mBaseTimeMs;
	}
	else {
		auto diff = std::chrono::high_resolution_clock::now() - mTimePoint;
		std::chrono::milliseconds diffMs = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
		return mBaseTimeMs + diffMs.count();
	}
}

void ClockTime::pause()
{
	mBaseTimeMs = getTimeMs();
	mIsPause = true;
}

void ClockTime::resume()
{
	mBaseTimeMs = getTimeMs();
	mIsPause = false;
	mTimePoint = std::chrono::high_resolution_clock::now();
}
