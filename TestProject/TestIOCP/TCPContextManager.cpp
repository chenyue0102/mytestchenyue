#include "stdafx.h"
#include "TCPContextManager.h"


TCPContextManager::TCPContextManager()
{
}


TCPContextManager::~TCPContextManager()
{
}

TCPContext* TCPContextManager::CreateContext()
{
	TCPContext *pTCPContext = new TCPContext();
	m_TCPContextSet.insert(pTCPContext);
	return pTCPContext;
}

void TCPContextManager::FreeContext(TCPContext *pTCPContext)
{
	if (m_TCPContextSet.erase(pTCPContext))
	{
		delete pTCPContext;
	}
}

void TCPContextManager::OnRecvData(const char *pBuffer, DWORD dwRecvLen, TCPContext *pTCPContext)
{

}
