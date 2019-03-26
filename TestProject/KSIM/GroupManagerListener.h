#ifndef _GROUPMANAGERLISTENER_H_
#define _GROUPMANAGERLISTENER_H_
#include "emgroupmanager_listener.h"

class GroupManagerListener : public easemob::EMGroupManagerListener
{
public:
	GroupManagerListener(int clientId);
	~GroupManagerListener();
public:
	virtual void onReceiveInviteFromGroup(const std::string groupId, const std::string& inviter, const std::string& inviteMessage)override;
	virtual void onReceiveInviteAcceptionFromGroup(const easemob::EMGroupPtr group, const std::string& invitee)override;
	virtual void onReceiveInviteDeclineFromGroup(const easemob::EMGroupPtr group, const std::string& invitee, const std::string &reason)override;
	virtual void onAutoAcceptInvitationFromGroup(const easemob::EMGroupPtr group, const std::string& inviter, const std::string& inviteMessage)override;
	virtual void onLeaveGroup(const easemob::EMGroupPtr group, easemob::EMGroup::EMGroupLeaveReason reason)override;
	virtual void onReceiveJoinGroupApplication(const easemob::EMGroupPtr group, const std::string& from, const std::string& message)override;
	virtual void onReceiveAcceptionFromGroup(const easemob::EMGroupPtr group)override;
	virtual void onReceiveRejectionFromGroup(const std::string &groupId, const std::string &reason)override;
	virtual void onUpdateMyGroupList(const std::vector<easemob::EMGroupPtr> &list)override;
private:
	int m_clientId;
};

#endif