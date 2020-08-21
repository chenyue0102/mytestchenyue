/*
服务器时间计时器
*/
#pragma once
#include <chrono>
#include <stdint.h>

class BaseTime
{
public:
	BaseTime();
	~BaseTime();
public:
	//设置UTC基准时间，单位秒
	void setBaseTime(int64_t baseTime);
	//设置UTC基准时间，单位毫秒
	void setBaseTimeMs(int64_t baseTimeMs);
	//设置UTC基准时间，单位微秒
	void setBaseTimeUs(int64_t baseTimeUs);
	//获取基准消息
	int64_t getBaseTime()const;
	//获取基准时间，单位毫秒
	int64_t getBaseTimeMs()const;
	//获取基准时间，单位微秒
	int64_t getBaseTimeUs()const;
public:
	//获取UTC基准时间，单位秒
	int64_t getCurrentTime();
	//获取UTC基准时间，单位毫秒
	int64_t getCurrentTimeMs();
	//获取UTC基准时间，单位微秒
	int64_t getCurrentTimeUs();
private:
	//时间起点
	std::chrono::high_resolution_clock::time_point m_timePoint;
	//服务器基准时间点
	int64_t m_baseTimeUs;
};