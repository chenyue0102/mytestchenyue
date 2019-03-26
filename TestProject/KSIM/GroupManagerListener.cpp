#include "GroupManagerListener.h"
#include <assert.h>
#include "net2local.h"
#include "KSIMInstance.h"
#include "KSIMBuffer.h"
#include "KSEnumDefine.h"
#include "KSStructDefine.h"
#include "KSStructSerialize.h"
#include "KSSerializeHelper.h"

GroupManagerListener::GroupManagerListener(int clientId)
	: m_clientId(clientId)
{

}

GroupManagerListener::~GroupManagerListener()
{

}

void GroupManagerListener::onReceiveInviteFromGroup(const std::string groupId, const std::string & inviter, const std::string & inviteMessage)
{
	KSIMReceiveInviteFromGroup data;
	data.groupId = groupId;
	data.inviter = inviter;
	data.inviteMessage = inviteMessage;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMReceiveInviteFromGroup, data);
}

void GroupManagerListener::onReceiveInviteAcceptionFromGroup(const easemob::EMGroupPtr group, const std::string & invitee)
{
	KSIMReceiveInviteAcceptionFromGroup data;
	data.group = net2local::Conver(*group);
	data.invitee = invitee;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMReceiveInviteAcceptionFromGroup, data);
}

void GroupManagerListener::onReceiveInviteDeclineFromGroup(const easemob::EMGroupPtr group, const std::string & invitee, const std::string & reason)
{
	KSIMReceiveInviteDeclineFromGroup data;
	data.group = net2local::Conver(*group);
	data.invitee = invitee;
	data.reason = reason;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMReceiveInviteDeclineFromGroup, data);
}

void GroupManagerListener::onAutoAcceptInvitationFromGroup(const easemob::EMGroupPtr group, const std::string & inviter, const std::string & inviteMessage)
{
	KSIMAutoAcceptInvitationFromGroup data;
	data.group = net2local::Conver(*group);
	data.inviter = inviter;
	data.inviteMessage = inviteMessage;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMAutoAcceptInvitationFromGroup, data);
}

void GroupManagerListener::onLeaveGroup(const easemob::EMGroupPtr group, easemob::EMGroup::EMGroupLeaveReason reason)
{
	KSIMLeaveGroup data;
	data.group = net2local::Conver(*group);
	data.reason = reason;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMLeaveGroup, data);
}

void GroupManagerListener::onReceiveJoinGroupApplication(const easemob::EMGroupPtr group, const std::string & from, const std::string & message)
{
	KSIMReceiveJoinGroupApplication data;
	data.group = net2local::Conver(*group);
	data.from = from;
	data.message = message;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMReceiveJoinGroupApplication, data);
}

void GroupManagerListener::onReceiveAcceptionFromGroup(const easemob::EMGroupPtr group)
{
	KSIMReceiveAcceptionFromGroup data;
	data.group = net2local::Conver(*group);
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMReceiveAcceptionFromGroup, data);
}

void GroupManagerListener::onReceiveRejectionFromGroup(const std::string & groupId, const std::string & reason)
{
	KSIMReceiveRejectionFromGroup data;
	data.groupId = groupId;
	data.reason = reason;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMReceiveRejectionFromGroup, data);
}

void GroupManagerListener::onUpdateMyGroupList(const std::vector<easemob::EMGroupPtr>& list)
{
	KSIMUpdateMyGroupList data;
	for (auto group : list)
	{
		data.list.push_back(net2local::Conver(*group));
	}
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMUpdateMyGroupList, data);
}
