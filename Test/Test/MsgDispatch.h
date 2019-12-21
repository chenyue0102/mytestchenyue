#pragma once
#include <mutex>
#include <map>
#include <list>
#include <time.h>
#include <string>
#include <Windows.h>


class MsgDispatch
{
	typedef std::map<UINT, std::list<HWND>> MSG_HWND_ARRAY;
	struct MsgDataInfo
	{
		int nRef;
		int nKey;
		time_t tStamp;
		std::string strData;
	};
public:
	MsgDispatch();
	~MsgDispatch();
public:
	bool regMsg(HWND hwnd, UINT uMsg);
	bool unregMsg(HWND hwnd, UINT uMsg);
	bool pushMsg(UINT uMsg, const char *pBuffer, int nBufLen);
	bool getMsg(int nKey, char *pBuf, int nBufLen);
private:
	std::mutex m_mutex;
	int m_nKey;
	MSG_HWND_ARRAY m_msgHWndArray;
	std::list<std::unique_ptr<MsgDataInfo>> m_dataCacheArray;
};

