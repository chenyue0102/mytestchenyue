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
	KSIMInviteGroup inviteGroup;
	inviteGroup.type = EKSIMInviteReq;
	inviteGroup.groupId = groupId;
	inviteGroup.username = inviter;
	inviteGroup.message = inviteMessage;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteGroup, inviteGroup);
}

void GroupManagerListener::onReceiveInviteAcceptionFromGroup(const easemob::EMGroupPtr group, const std::string & invitee)
{
	if (group)
	{
		KSIMInviteGroup inviteGroup;
		inviteGroup.type = EKSIMInviteAck;
		inviteGroup.result = EKSIMResultAgree;
		inviteGroup.group = net2local::Conver(*group);
		inviteGroup.username = invitee;
		KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteGroup, inviteGroup);
	}
	else
	{
		assert(false);
	}
}

void GroupManagerListener::onReceiveInviteDeclineFromGroup(const easemob::EMGroupPtr group, const std::string & invitee, const std::string & reason)
{
	if (group)
	{
		KSIMInviteGroup inviteGroup;
		inviteGroup.type = EKSIMInviteAck;
		inviteGroup.result = EKSIMResultRefuse;
		inviteGroup.group = net2local::Conver(*group);
		inviteGroup.username = invitee;
		inviteGroup.reason = reason;
		KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteGroup, inviteGroup);
	}
	else
	{
		assert(false);
	}
}

void GroupManagerListener::onAutoAcceptInvitationFromGroup(const easemob::EMGroupPtr group, const std::string & inviter, const std::string & inviteMessage)
{
	if (group)
	{
		KSIMInviteGroup inviteGroup;
		inviteGroup.type = EKSIMInviteAck;
		inviteGroup.result = EKSIMResultAutoAgree;
		inviteGroup.group = net2local::Conver(*group);
		inviteGroup.username = inviter;
		inviteGroup.message = inviteMessage;
		KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteGroup, inviteGroup);
	}
	else
	{
		assert(false);
	}
}

void GroupManagerListener::onReceiveJoinGroupApplication(const easemob::EMGroupPtr group, const std::string & from, const std::string & message)
{
	if (group)
	{
		KSIMInviteGroup inviteGroup;
		inviteGroup.type = EKSIMApplyReq;
		inviteGroup.group = net2local::Conver(*group);
		inviteGroup.username = from;
		inviteGroup.message = message;
		KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteGroup, inviteGroup);
	}
	else
	{
		assert(false);
	}
}

void GroupManagerListener::onReceiveAcceptionFromGroup(const easemob::EMGroupPtr group)
{
	if (group)
	{
		KSIMInviteGroup inviteGroup;
		inviteGroup.type = EKSIMApplyAck;
		inviteGroup.result = EKSIMResultAgree;
		inviteGroup.group = net2local::Conver(*group);
		KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteGroup, inviteGroup);
	}
	else
	{
		assert(false);
	}
}

void GroupManagerListener::onReceiveRejectionFromGroup(const std::string & groupId, const std::string & reason)
{
	KSIMInviteGroup inviteGroup;
	inviteGroup.type = EKSIMApplyAck;
	inviteGroup.result = EKSIMResultRefuse;
	inviteGroup.groupId = groupId;
	inviteGroup.reason = reason;
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMInviteGroup, inviteGroup);
}

void GroupManagerListener::onUpdateMyGroupList(const std::vector<easemob::EMGroupPtr>& list)
{
	KSIMUpdateMyGroupList data;
	for (auto group : list)
	{
		if (!group)
		{
			assert(false);
			continue;
		}
		data.list.push_back(net2local::Conver(*group));
	}
	KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMUpdateMyGroupList, data);
}

void GroupManagerListener::onLeaveGroup(const easemob::EMGroupPtr group, easemob::EMGroup::EMGroupLeaveReason reason)
{
	if (group)
	{
		KSIMLeaveGroup data;
		data.group = net2local::Conver(*group);
		data.reason = reason;
		KSIM::g_KSIMInstance.doCallback(m_clientId, EKSMsgIMLeaveGroup, data);
	}
	else
	{
		assert(false);
	}
}