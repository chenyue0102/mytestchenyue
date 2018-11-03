#pragma once
#include <list>
#include <string>
#include <mutex>
#include <wtypes.h>

struct MSG_HEADER
{
	DWORD dwMsgType;
	DWORD dwMsgLen;
};
class CUserObject
{
public:
	CUserObject();
	~CUserObject();
public:
	void OnRecvData(const char *pBuffer, DWORD dwDataLen);
private:
	std::mutex m_mutex;
	std::list<std::string> m_MsgData;
	std::string m_tempData;
};

