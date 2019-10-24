#include "FPS.h"



FPS::FPS()
	: m_timePoint(std::chrono::high_resolution_clock::now())
	, m_lastFPS(0)
	, m_frameCount(0)
{
}


FPS::~FPS()
{
}

int FPS::fps()
{
	auto cur = std::chrono::high_resolution_clock::now();
	auto diffMs = std::chrono::duration_cast<std::chrono::milliseconds>(cur - m_timePoint);
	m_frameCount++;
	if (diffMs.count() >= 1000)
	{
		m_lastFPS = m_frameCount * 1000 / diffMs.count();
		m_timePoint = cur;
		m_frameCount = 0;
	}
	return m_lastFPS;
}
