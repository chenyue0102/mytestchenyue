#include "ConnectionListener.h"
#include "KSIMInstance.h"
#include "KSEnumDefine.h"

ConnectionListener::ConnectionListener(int clientId)
	: m_clientId(clientId)
{

}

ConnectionListener::~ConnectionListener()
{

}

void ConnectionListener::onDisconnect(easemob::EMErrorPtr error)
{
	KSIM::KSIMBuffer data;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMDisconnect, data);
}

void ConnectionListener::onConnect()
{
	KSIM::KSIMBuffer data;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMConnect, data);
}