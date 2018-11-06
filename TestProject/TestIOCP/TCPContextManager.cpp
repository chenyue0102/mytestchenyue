#include "stdafx.h"
#include <assert.h>
#include "TCPContextManager.h"


TCPContextManager::TCPContextManager()
{
}


TCPContextManager::~TCPContextManager()
{
}

CUserObject* TCPContextManager::CreateContext(const char *pBuffer, DWORD dwRecvLen, SOCKET s, const sockaddr_in &addr)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	CComPtr<CUserObject> pUserObject;

	do 
	{
		if (nullptr == pBuffer
			|| dwRecvLen < sizeof(MSGHEADERNET))
		{
			assert(false);
			break;
		}
		MSGHEADERNET net = { 0 };
		memcpy(&net, pBuffer, sizeof(MSGHEADERNET));
		MSGHEADERLOCAL local = Net2Local(net);
		pUserObject = InnerCreateUserObject(local.dwObjectTye);
		if (!pUserObject)
		{
			assert(false);
			break;
		}
		pUserObject->SetClientInfo(s, addr);
		m_UserObjectSet.insert(pUserObject);
	} while (false);
	return pUserObject;
}

void TCPContextManager::FreeContext(CUserObject *pDeleteObject)
{
	CComPtr<CUserObject> pUserObject;
	{
		std::lock_guard<std::mutex> lk(m_mutex);

		auto iter = m_UserObjectSet.find(pDeleteObject);
		if (iter != m_UserObjectSet.end())
		{
			pUserObject = *iter;
			m_UserObjectSet.erase(iter);
		}
		else
		{
			assert(false);
		}
	}
	if (pUserObject)
	{
		pUserObject->OnClose();
	}
}

bool TCPContextManager::OnRecvData(const char *pBuffer, DWORD dwRecvLen, CUserObject *pUserObject)
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
		auto iter = m_UserObjectSet.find(pUserObject);
		if (iter == m_UserObjectSet.end())
		{
			assert(false);
			break;
		}
		CComPtr<CUserObject> pUserObject = *iter;
		if (!pUserObject)
		{
			assert(false);
			break;
		}
		bRes = pUserObject->OnRecvData(pBuffer, dwRecvLen);
	} while (false);
	
	return bRes;
}

CUserObject * TCPContextManager::InnerCreateUserObject(DWORD dwObjectType)
{
	return new CUserObject;
}
