#pragma once
#include <chrono>
class CalcTime
{
	typedef std::chrono::high_resolution_clock::time_point TIME_POINT;
public:
	CalcTime();
	~CalcTime();
public:
	void start();
	TIME_POINT::duration end();
	int endMs();
private:
	TIME_POINT m_timePoint;
};

