#include "SystemTime.h"

SystemTime::SystemTime()
	: m_timePoint()
	, m_baseTimeUs()
{
	setBaseTimeUs(0);//预先初始化下m_timePoint，只计算两个点的时差，可以直接使用
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
	setBaseTimeUs(baseTimeMs * 1000);
}

void SystemTime::setBaseTimeUs(long long baseTimeUs){
	m_baseTimeUs = baseTimeUs;
	m_timePoint = std::chrono::high_resolution_clock::now();//稳定时钟，更改系统时间，不影响此时钟
}

long long SystemTime::getBaseTime() const
{
	return getBaseTimeMs() / 1000;
}

long long SystemTime::getBaseTimeMs() const
{
	return getBaseTimeUs() / 1000;
}

long long SystemTime::getBaseTimeUs()const{
	return m_baseTimeUs;
}

long long SystemTime::getCurrentTime()
{
	return getCurrentTimeMs() / 1000;
}

long long SystemTime::getCurrentTimeMs()
{
	return getCurrentTimeUs() / 1000;
}

long long SystemTime::getCurrentTimeUs(){
	//计算时钟的差
	auto diff = std::chrono::high_resolution_clock::now() - m_timePoint;
	std::chrono::microseconds diffUs = std::chrono::duration_cast<std::chrono::microseconds>(diff);
	return m_baseTimeUs + diffUs.count();
}
