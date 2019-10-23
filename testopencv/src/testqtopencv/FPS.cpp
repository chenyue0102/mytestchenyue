#include "FPS.h"



FPS::FPS()
	: m_timePoint(std::chrono::high_resolution_clock::now())
{
}


FPS::~FPS()
{
}

int FPS::fps()
{
	auto cur = std::chrono::high_resolution_clock::now();
	auto diffMs = std::chrono::duration_cast<std::chrono::milliseconds>(cur - m_timePoint);
	m_timePoint = cur;
	if (diffMs.count() > 0)
	{
		return 1000 / diffMs.count();
	}
	else
	{
		return 0;
	}
}
