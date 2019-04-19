#include "LoaderInstance.h"
#include <assert.h>
#include "Loader.h"

LoaderInstance theApp;
LoaderInstance::LoaderInstance()
	: m_hModule(nullptr)
	, m_mutex()
	, m_loads()
{
}


LoaderInstance::~LoaderInstance()
{
}

void LoaderInstance::EnterInstance(HMODULE hModule)
{
	m_hModule = hModule;
}

void LoaderInstance::ExitInstance()
{
	m_hModule = nullptr;
}

ILoader * LoaderInstance::CreateLoader()
{
	std::lock_guard<std::mutex> lk(m_mutex);
	Loader *p = new Loader();
	p->AddRef();
	m_loads.insert(p);
	return p;
}

void LoaderInstance::DestroyLoader(ILoader * pLoader)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	auto iter = m_loads.find(pLoader);
	if (iter != m_loads.end())
	{
		(*iter)->Release();
		m_loads.erase(iter);
	}
	else
	{
		assert(false);
	}
}
