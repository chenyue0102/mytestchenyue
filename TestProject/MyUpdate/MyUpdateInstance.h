#pragma once
#include <map>
#include <memory>
#include <mutex>

class UpdateManager;
class MyUpdateInstance
{
public:
	MyUpdateInstance();
	~MyUpdateInstance();
public:
	int createUpdate();
	void setUpdateParam(int ctx, int type, va_list argp);
	void startUpdate(int ctx);
	void cancelUpdate(int ctx);
	void destroyUpdate(int ctx);
public:
	std::mutex m_mtx;
	int m_nKey;
	std::map<int, std::shared_ptr<UpdateManager>> m_updateManagers;
};
extern MyUpdateInstance g_instance;

