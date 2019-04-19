#pragma once
#include <set>
#include <mutex>
#include <Windows.h>

struct ILoader;
class LoaderInstance
{
public:
	LoaderInstance();
	~LoaderInstance();
public:
	void EnterInstance(HMODULE hModule);
	void ExitInstance();
public:
	ILoader* CreateLoader();
	void DestroyLoader(ILoader *pLoader);
private:
	HMODULE m_hModule;
	std::mutex m_mutex;
	std::set<ILoader*> m_loads;
};

extern LoaderInstance theApp;