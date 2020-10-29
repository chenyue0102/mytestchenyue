#include "BaseTime.h"

BaseTime::BaseTime()
	: m_timePoint()
	, m_baseTimeUs()
{
	setBaseTimeUs(0);//预先初始化下m_timePoint，只计算两个点的时差，可以直接使用
}

BaseTime::~BaseTime()
{
}

void BaseTime::setBaseTime(int64_t baseTime)
{
	setBaseTimeMs(baseTime * 1000);
}

void BaseTime::setBaseTimeMs(int64_t baseTimeMs)
{
	setBaseTimeUs(baseTimeMs * 1000);
}

void BaseTime::setBaseTimeUs(int64_t baseTimeUs){
	m_baseTimeUs = baseTimeUs;
	m_timePoint = std::chrono::high_resolution_clock::now();//稳定时钟，更改系统时间，不影响此时钟
}

int64_t BaseTime::getBaseTime() const
{
	return getBaseTimeMs() / 1000;
}

int64_t BaseTime::getBaseTimeMs() const
{
	return getBaseTimeUs() / 1000;
}

int64_t BaseTime::getBaseTimeUs()const{
	return m_baseTimeUs;
}

int64_t BaseTime::getCurrentTime()
{
	return getCurrentTimeMs() / 1000;
}

int64_t BaseTime::getCurrentTimeMs()
{
	return getCurrentTimeUs() / 1000;
}

int64_t BaseTime::getCurrentTimeUs(){
	//计算时钟的差
	auto diff = std::chrono::high_resolution_clock::now() - m_timePoint;
	std::chrono::microseconds diffUs = std::chrono::duration_cast<std::chrono::microseconds>(diff);
	return m_baseTimeUs + diffUs.count();
}
