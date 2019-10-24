#pragma once
#include <chrono>
class FPS
{
public:
	FPS();
	~FPS();
public:
	int fps();
private:
	//时间基点，稳定时钟，更改系统时间，不影响此时钟
	std::chrono::high_resolution_clock::time_point m_timePoint;
	int m_lastFPS;
	int m_frameCount;
};

