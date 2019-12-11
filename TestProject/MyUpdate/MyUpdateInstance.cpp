#include "MyUpdateInstance.h"
#include <assert.h>
#include <stdarg.h>
#include "UpdateManager.h"


MyUpdateInstance g_instance;
MyUpdateInstance::MyUpdateInstance()
	: m_nKey(1)
{
}


MyUpdateInstance::~MyUpdateInstance()
{
	assert(!m_updateManagers.empty());
}

int MyUpdateInstance::createUpdate()
{
	std::lock_guard<std::mutex> lk(m_mtx);
	while (true)
	{
		if (0 == m_nKey)
		{
			m_nKey++;
		}
		if (m_updateManagers.find(m_nKey) == m_updateManagers.end())
		{
			break;
		}
		else
		{
			++m_nKey;
		}
	}
	int key = m_nKey++;
	std::shared_ptr<UpdateManager> pUpdate(std::make_shared<UpdateManager>());
	m_updateManagers.insert(std::make_pair(key, pUpdate));
	return key;
}

void MyUpdateInstance::setUpdateParam(int ctx, int type, va_list argp)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	auto iter = m_updateManagers.find(ctx);
	if (iter != m_updateManagers.end())
	{
		iter->second->setUpdateParam(type, argp);
	}
}

void MyUpdateInstance::startUpdate(int ctx)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	auto iter = m_updateManagers.find(ctx);
	if (iter != m_updateManagers.end())
	{
		iter->second->startUpdate();
	}
}

void MyUpdateInstance::cancelUpdate(int ctx)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	auto iter = m_updateManagers.find(ctx);
	if (iter != m_updateManagers.end())
	{
		iter->second->cancel();
	}
}

void MyUpdateInstance::destroyUpdate(int ctx)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	auto iter = m_updateManagers.find(ctx);
	if (iter != m_updateManagers.end())
	{
		iter->second->stopUpdate();
		m_updateManagers.erase(iter);
	}
}
