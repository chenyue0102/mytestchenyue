#include "ContactListener.h"
#include "KSStructDefine.h"
#include "KSEnumDefine.h"
#include "KSStructSerialize.h"
#include "KSIMInstance.h"

ContactListener::ContactListener(int clientId)
	: m_clientId(clientId)
{

}

ContactListener::~ContactListener()
{

}

void ContactListener::onContactAdded(const std::string &username)
{
	KSIMAddContact contact;
	contact.username = username;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMAddContact, contact);
}

void ContactListener::onContactDeleted(const std::string &username)
{
	KSIMDeleteContact contact;
	contact.username = username;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMDeleteContact, contact);
}

void ContactListener::onContactInvited(const std::string &username, std::string &reason)
{
	KSIMInviteContact inviteContact;
	inviteContact.type = EKSIMInviteReq;
	inviteContact.username = username;
	inviteContact.reason = reason;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteContact, inviteContact);
}

void ContactListener::onContactAgreed(const std::string &username)
{
	KSIMInviteContact inviteContact;
	inviteContact.type = EKSIMInviteAck;
	inviteContact.result = EKSIMResultAgree;
	inviteContact.username = username;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteContact, inviteContact);
}

void ContactListener::onContactRefused(const std::string &username)
{
	KSIMInviteContact inviteContact;
	inviteContact.type = EKSIMInviteAck;
	inviteContact.result = EKSIMResultRefuse;
	inviteContact.username = username;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteContact, inviteContact);
}