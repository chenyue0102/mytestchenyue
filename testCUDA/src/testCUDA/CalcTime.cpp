#include "CalcTime.h"



CalcTime::CalcTime()
{
}


CalcTime::~CalcTime()
{
}

void CalcTime::start()
{
	m_timePoint = std::chrono::high_resolution_clock::now();
}

CalcTime::TIME_POINT::duration CalcTime::end()
{
	return (std::chrono::high_resolution_clock::now() - m_timePoint);
}

int CalcTime::endMs()
{
	return (int)std::chrono::duration_cast<std::chrono::milliseconds>(end()).count();
}
