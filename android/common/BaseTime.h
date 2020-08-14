/*
服务器时间计时器
*/
#pragma once
#include <chrono>

class BaseTime
{
public:
	BaseTime();
	~BaseTime();
public:
	//设置UTC基准时间，单位秒
	void setBaseTime(long long baseTime);
	//设置UTC基准时间，单位毫秒
	void setBaseTimeMs(long long baseTimeMs);
	//设置UTC基准时间，单位微秒
	void setBaseTimeUs(long long baseTimeUs);
	//获取基准消息
	long long getBaseTime()const;
	//获取基准时间，单位毫秒
	long long getBaseTimeMs()const;
	//获取基准时间，单位微秒
	long long getBaseTimeUs()const;
public:
	//获取UTC基准时间，单位秒
	long long getCurrentTime();
	//获取UTC基准时间，单位毫秒
	long long getCurrentTimeMs();
	//获取UTC基准时间，单位微秒
	long long getCurrentTimeUs();
private:
	//时间起点
	std::chrono::high_resolution_clock::time_point m_timePoint;
	//服务器基准时间点
	long long m_baseTimeUs;
};