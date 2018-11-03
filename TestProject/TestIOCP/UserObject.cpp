#include "stdafx.h"
#include "UserObject.h"


CUserObject::CUserObject()
{
}


CUserObject::~CUserObject()
{
}

void CUserObject::OnRecvData(const char *pBuffer, DWORD dwDataLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	
	m_tempData.append(pBuffer, dwDataLen);
	while (m_tempData.size() >= sizeof(MSG_HEADER))
	{
		const MSG_HEADER *pHeader = reinterpret_cast<const MSG_HEADER*>(m_tempData.data());
		DWORD dwOneMsgLen = pHeader->dwMsgLen + sizeof(MSG_HEADER);
		m_MsgData.push_back(std::string(m_tempData.data(), dwOneMsgLen));
		m_tempData.erase(0, dwOneMsgLen);
	}
}
