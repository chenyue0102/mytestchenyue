#include "MsgDispatch.h"
#include <assert.h>
#include <algorithm>

#define TIME_OUT_SECOND 30

MsgDispatch::MsgDispatch()
	: m_mutex()
	, m_nKey(0)
{
}


MsgDispatch::~MsgDispatch()
{
}

bool MsgDispatch::regMsg(HWND hwnd, UINT uMsg)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	
	bool bRet = false;

	do
	{
		if (nullptr == hwnd
			|| 0 == uMsg)
		{
			assert(false);
			break;
		}
		auto &wndArray = m_msgHWndArray[uMsg];
		auto iter = std::find(wndArray.begin(), wndArray.end(), hwnd);
		if (iter != wndArray.end())
		{
			assert(false);
			bRet = true;
			break;
		}
		wndArray.push_back(hwnd);
		bRet = true;
	} while (false);
	return bRet;
}

bool MsgDispatch::unregMsg(HWND hwnd, UINT uMsg)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	bool bRet = false;

	do
	{
		if (0 == hwnd)
		{
			assert(false);
			break;
		}
		if (0 != uMsg)
		{
			auto &wndArray = m_msgHWndArray[uMsg];
			auto iterRemove = std::remove(wndArray.begin(), wndArray.end(), hwnd);
			if (iterRemove == wndArray.end())
			{
				assert(false);
				break;
			}
			wndArray.erase(iterRemove, wndArray.end());
		}
		else
		{
			for (auto &msgWndPair : m_msgHWndArray)
			{
				auto &wndArray = msgWndPair.second;
				auto iterRemove = std::remove(wndArray.begin(), wndArray.end(), hwnd);
				if (iterRemove == wndArray.end())
				{
					continue;
				}
				wndArray.erase(iterRemove, wndArray.end());
			}
		}
		bRet = true;
	} while (false);

	return bRet;
}

bool MsgDispatch::pushMsg(UINT uMsg, const char * pBuffer, int nBufLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	bool bRet = false;

	do
	{
		if (0 == uMsg)
		{
			assert(false);
			break;
		}
		++m_nKey;
		auto &wndArray = m_msgHWndArray[uMsg];
		auto iter = wndArray.begin();
		while (iter != wndArray.end())
		{
			HWND hwnd = *iter;
			if (IsWindow(hwnd))
			{
				PostMessage(hwnd, uMsg, m_nKey, nBufLen);
				++iter;
			}
			else
			{
				iter = wndArray.erase(iter);
			}
		}
		if (wndArray.empty())
		{
			break;
		}
		std::unique_ptr<MsgDataInfo> pDataInfo = std::make_unique<MsgDataInfo>();
		pDataInfo->nKey = m_nKey;
		pDataInfo->nRef = static_cast<int>(wndArray.size());
		if (nullptr != pBuffer
			|| nBufLen > 0)
		{
			pDataInfo->strData.append(pBuffer, nBufLen);
		}
		pDataInfo->tStamp = time(nullptr);
		m_dataCacheArray.push_back(std::move(pDataInfo));

		bRet = true;
	} while (false);
	return bRet;
}

bool MsgDispatch::getMsg(int nKey, char * pBuf, int nBufLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	bool bRet = false;
	time_t tCur = time(nullptr);

	auto iter = m_dataCacheArray.begin();
	while (iter != m_dataCacheArray.end())
	{
		auto &pDataInfo = (*iter);
		if (!pDataInfo
			|| (pDataInfo->tStamp + TIME_OUT_SECOND) < tCur)
		{
			assert(false);
			iter = m_dataCacheArray.erase(iter);
		}
		else if (pDataInfo->nKey == nKey)
		{
			if (pDataInfo->strData.empty())
			{
				bRet = true;
			}
			else if (nullptr != pBuf 
				&& nBufLen > 0
				&& static_cast<unsigned int>(nBufLen) >= pDataInfo->strData.size())
			{
				memcpy(pBuf, pDataInfo->strData.data(), pDataInfo->strData.size());
				bRet = true;
			}
			
			if (--pDataInfo->nRef == 0)
			{
				m_dataCacheArray.erase(iter);
			}
			break;
		}
		else
		{
			++iter;
		}
	}

	return bRet;
}
