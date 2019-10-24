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
	//ʱ����㣬�ȶ�ʱ�ӣ�����ϵͳʱ�䣬��Ӱ���ʱ��
	std::chrono::high_resolution_clock::time_point m_timePoint;
	int m_lastFPS;
	int m_frameCount;
};

