// TestFiber.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

struct FiberData
{
	LPVOID lpThreadAddress;
	LPVOID lpFiber1;
	LPVOID lpFiber2;
};

VOID CALLBACK FiberProc1(PVOID lpParameter)
{
	FiberData *pfd = (FiberData*)::GetFiberData();
	std::cout << "FiberProc1  " << std::endl;
	SwitchToFiber(pfd->lpFiber2);
	std::cout << "FiberProc1  2" << std::endl;
	SwitchToFiber(pfd->lpFiber2);
	std::cout << "FiberProc1  exit" << std::endl;
	SwitchToFiber(pfd->lpThreadAddress);
}

VOID CALLBACK FiberProc2(PVOID lpParameter)
{
	FiberData *pfd = (FiberData*)::GetFiberData();
	std::cout << "FiberProc2  " << std::endl;
	SwitchToFiber(pfd->lpFiber1);
	std::cout << "FiberProc2  2" << std::endl;
	SwitchToFiber(pfd->lpFiber1);
}

int main()
{
	FiberData fd = { 0 };
	fd.lpThreadAddress = ConvertThreadToFiber(&fd);
	fd.lpFiber1 = CreateFiberEx(4 * 1024, 0, FIBER_FLAG_FLOAT_SWITCH, &FiberProc1, &fd);
	fd.lpFiber2 = CreateFiberEx(4 * 1024, 0, FIBER_FLAG_FLOAT_SWITCH, &FiberProc2, &fd);
	SwitchToFiber(fd.lpFiber1);
	DeleteFiber(fd.lpFiber1);
	DeleteFiber(fd.lpFiber2);

	auto b = ConvertFiberToThread();
	std::cout << "main" << std::endl;
    return 0;
}
