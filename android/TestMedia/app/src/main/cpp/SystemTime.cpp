#include "SystemTime.h"

SystemTime::SystemTime()
	: m_timePoint()
	, m_baseTimeMs()
{
	setBaseTimeMs(0);//预先初始化下m_timePoint，只计算两个点的时差，可以直接使用
}

SystemTime::~SystemTime()
{
}

void SystemTime::setBaseTime(long long baseTime)
{
	setBaseTimeMs(baseTime * 1000);
}

void SystemTime::setBaseTimeMs(long long baseTimeMs)
{
	m_baseTimeMs = baseTimeMs;
	m_timePoint = std::chrono::high_resolution_clock::now();//稳定时钟，更改系统时间，不影响此时钟
}

long long SystemTime::getBaseTime() const
{
	return getBaseTimeMs() / 1000;
}

long long SystemTime::getBaseTimeMs() const
{
	return m_baseTimeMs;
}

long long SystemTime::getCurrentTime()
{
	return getCurrentTimeMs() / 1000;
}

long long SystemTime::getCurrentTimeMs()
{
	//计算时钟的差
	auto diff = std::chrono::high_resolution_clock::now() - m_timePoint;
	std::chrono::milliseconds diffMs = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
	return m_baseTimeMs + diffMs.count();
}
