/*
服务器时间计时器
*/
#pragma once
#include <chrono>

class SystemTime
{
public:
	SystemTime();
	~SystemTime();
public:
	//设置UTC基准时间，单位秒
	void setBaseTime(long long baseTime);
	//设置UTC基准时间，单位毫秒
	void setBaseTimeMs(long long baseTimeMs);
	//获取基准消息
	long long getBaseTime()const;
	//获取基准时间，单位毫秒
	long long getBaseTimeMs()const;
public:
	//获取UTC基准时间，单位秒
	long long getCurrentTime();
	//获取UTC基准时间，单位毫秒
	long long getCurrentTimeMs();
private:
	//时间起点
	std::chrono::high_resolution_clock::time_point m_timePoint;
	//服务器基准时间点
	long long m_baseTimeMs;
};