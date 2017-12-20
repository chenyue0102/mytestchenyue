// TestHook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include "xhook.h"
using namespace std;
typedef void(WINAPI *SleepF)(DWORD dwMilliseconds);
SleepF sleep_fn = &::Sleep;

void WINAPI MySleep(DWORD ms)
{
	cout << "MySleep(" << ms << ")" << endl;
	return sleep_fn(ms);
}

void TestSleep()
{
	Sleep(100);
}

typedef int(__cdecl*atoiF)(const char*);
atoiF atoi_Fn = &atoi;

int __cdecl myatoi(const char *p)
{
	return atoi_Fn(p);
}

int main()
{
	::Sleep(1);
	sleep_fn(1);
	XHookRestoreAfterWith();
	XHookTransactionBegin();
	XHookUpdateThread(GetCurrentThread());
	XHookAttach(&(PVOID&)sleep_fn, MySleep);
	XHookAttach((PVOID*)&atoi_Fn, &myatoi);
	XHookTransactionCommit();
	int n = atoi("100");
	std::thread t(&TestSleep);
	t.join();
	::Sleep(1);
	auto ps = &::Sleep;
	ps(10);
	sleep_fn(1);
	auto p1 = &Sleep;
	auto p2 = &MySleep;
    return 0;
}

