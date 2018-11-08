#include "stdafx.h"
#include <atlcomcli.h>
#include "UserObject.h"
#include "Single.h"
#include "TaskPool.h"
#include "IOCPServer.h"

#define HEART_BEAT_SECOND (5 * 60)

CUserObject::CUserObject()
	: m_ulRef(0)
	, m_tLastMsgTime(time(nullptr))
	, m_mutex()
	, m_hSocket(INVALID_SOCKET)
	, m_addr()
	, m_MsgData()
	, m_tempData()
{
}


CUserObject::~CUserObject()
{
}

void CUserObject::SetClientInfo(SOCKET s, const sockaddr_in & addr)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	m_hSocket = s;
	m_addr = addr;
}

void CUserObject::SetSocket(SOCKET s)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	m_hSocket = s;
}

void CUserObject::Close()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	if (INVALID_SOCKET != m_hSocket)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
}

SOCKET CUserObject::GetSocket() const
{
	std::lock_guard<std::mutex> lk(m_mutex);

	return m_hSocket;
}

bool CUserObject::SendMsg(MSGHEADERLOCAL * pHeader)
{
	MSGHEADERLOCAL local = { 0 };
	memcpy(&local, pHeader, sizeof(local));
	MSGHEADERNET net = Local2Net(local);
	memcpy(pHeader, &net, sizeof(net));
	CSingle<CIOCPServer>::Instance().Send(GetSocket(), (char*)pHeader, local.dwMsgLen + sizeof(MSGHEADERLOCAL));
	return false;
}

bool CUserObject::OnRecvData(const char *pBuffer, DWORD dwDataLen)
{
	m_tLastMsgTime = time(nullptr);

	std::lock_guard<std::mutex> lk(m_mutex);
	
	m_tempData.append(pBuffer, dwDataLen);
	while (m_tempData.size() >= sizeof(MSGHEADERNET))
	{
		MSGHEADERNET net = { 0 };
		memcpy(&net, m_tempData.data(), sizeof(MSGHEADERNET));
		MSGHEADERLOCAL local = Net2Local(net);
		DWORD dwOneMsgLen = local.dwMsgLen + sizeof(MSGHEADERLOCAL);
		if (m_tempData.size() >= dwOneMsgLen)
		{
			memcpy(&*m_tempData.begin(), &local, sizeof(MSGHEADERLOCAL));//包头转换成本地结构体
			m_MsgData.push_back(std::string(m_tempData.data(), dwOneMsgLen));
			m_tempData.erase(0, dwOneMsgLen);
		}
		else
		{
			break;
		}
	}
	if (!m_MsgData.empty())
	{
		CComPtr<CUserObject> pUserObject(this);
		auto doRecvFun = [pUserObject]() 
		{
			if (pUserObject)
			{
				pUserObject->InnerDoRecvMsg();
			}
		};
		//同一个Object的Recv由同一个线程调用
		static_assert(sizeof(void*) == sizeof(std::size_t), "");
		CSingle<CTaskPool>::Instance().AddTask(doRecvFun, (std::size_t)this);
	}
	return true;
}

bool CUserObject::CheckSocket()
{
	time_t tCurTime = time(nullptr);
	return (m_tLastMsgTime + HEART_BEAT_SECOND) < tCurTime;
}

ULONG CUserObject::AddRef(void)
{
	return ++m_ulRef;
}

ULONG CUserObject::Release(void)
{
	ULONG ulResult = --m_ulRef;
	if (0 == ulResult)
	{
		delete this;
	}
	return ulResult;
}

bool CUserObject::OnMsg(MSGHEADERLOCAL * pHeader)
{
	return true;
}

void CUserObject::OnClose()
{

}

void CUserObject::InnerDoRecvMsg()
{
	std::list<std::string> tempList;
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		tempList = std::move(m_MsgData);
	}
	bool bRes = true;
	for (auto &oneMsg : tempList)
	{
		if (!OnMsg((MSGHEADERLOCAL*)oneMsg.data()))
		{
			bRes = false;
			break;
		}
	}
	if (!bRes)
	{
		Close();
	}
}
