#include "stdafx.h"
#include <assert.h>
#include "TCPContextManager.h"


TCPContextManager::TCPContextManager()
{
}


TCPContextManager::~TCPContextManager()
{
}

TCPContext* TCPContextManager::CreateContext()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	TCPContext *pTCPContext = new TCPContext();
	m_TCPContextSet.insert(pTCPContext);
	return pTCPContext;
}

void TCPContextManager::FreeContext(TCPContext *pTCPContext)
{
	CComPtr<CUserObject> pUserObject;
	{
		std::lock_guard<std::mutex> lk(m_mutex);

		auto iter = m_ContextObjectMap.find(pTCPContext);
		if (iter != m_ContextObjectMap.end())
		{
			pUserObject = iter->second;
		}
		m_ContextObjectMap.erase(pTCPContext);
		if (m_TCPContextSet.erase(pTCPContext))
		{
			delete pTCPContext;
		}
	}
	if (pUserObject)
	{
		pUserObject->OnClose();
	}
}

bool TCPContextManager::OnRecvData(const char *pBuffer, DWORD dwRecvLen, TCPContext *pTCPContext)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	bool bRes = false;

	do 
	{
		if (nullptr == pBuffer
			|| 0 == dwRecvLen)
		{
			assert(false);
			break;
		}
		auto iter = m_ContextObjectMap.find(pTCPContext);
		if (iter == m_ContextObjectMap.end())
		{
			if (dwRecvLen < sizeof(MSGHEADERNET))
			{
				assert(false);
				break;
			}
			MSGHEADERNET net = { 0 };
			memcpy(&net, pBuffer, sizeof(MSGHEADERNET));
			MSGHEADERLOCAL local = Net2Local(net);
			CComPtr<CUserObject> pUserObject = CreateUserObject(local.dwObjectTye);
			if (!pUserObject)
			{
				assert(false);
				break;
			}
			pUserObject->SetClientInfo(pTCPContext->m_hSocket, pTCPContext->addr);
			if (!pUserObject->OnRecvData(pBuffer, dwRecvLen))
			{
				assert(false);
				break;
			}
			m_ContextObjectMap.insert(std::make_pair(pTCPContext, pUserObject));
			bRes = true;
		}
		else
		{
			CComPtr<CUserObject> pUserObject = iter->second;
			if (!pUserObject)
			{
				assert(false);
				break;
			}
			bRes = pUserObject->OnRecvData(pBuffer, dwRecvLen);
		}
	} while (false);
	
	return bRes;
}

CUserObject * TCPContextManager::CreateUserObject(DWORD dwObjectType)
{
	return new CUserObject;
}
