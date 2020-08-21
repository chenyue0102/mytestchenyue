#ifndef _CLOCK_TIME_H_
#define _CLOCK_TIME_H_
#include <stdint.h>
#include <chrono>

class ClockTime
{
public:
	ClockTime();
	~ClockTime();
public:
	void setTimeMs(int64_t baseTimeMs);
	int64_t getTimeMs()const;
	void pause();
	void resume();
private:
	int64_t mBaseTimeMs;
	bool mIsPause;
	std::chrono::high_resolution_clock::time_point mTimePoint;
};

#endif