#ifndef _GROUPMANAGERLISTENER_H_
#define _GROUPMANAGERLISTENER_H_
#include "emgroupmanager_listener.h"

class GroupManagerListener : public easemob::EMGroupManagerListener
{
public:
	GroupManagerListener(int clientId);
	virtual ~GroupManagerListener();
public:
	//邀请的请求
	virtual void onReceiveInviteFromGroup(const std::string groupId, const std::string& inviter, const std::string& inviteMessage)override;
	//邀请的同意回馈
	virtual void onReceiveInviteAcceptionFromGroup(const easemob::EMGroupPtr group, const std::string& invitee)override;
	//邀请的拒绝回馈
	virtual void onReceiveInviteDeclineFromGroup(const easemob::EMGroupPtr group, const std::string& invitee, const std::string &reason)override;
	//邀请的自动同意回馈
	virtual void onAutoAcceptInvitationFromGroup(const easemob::EMGroupPtr group, const std::string& inviter, const std::string& inviteMessage)override;
	//申请的请求
	virtual void onReceiveJoinGroupApplication(const easemob::EMGroupPtr group, const std::string& from, const std::string& message)override;
	//申请的同意回馈
	virtual void onReceiveAcceptionFromGroup(const easemob::EMGroupPtr group)override;
	//申请的拒绝回馈
	virtual void onReceiveRejectionFromGroup(const std::string &groupId, const std::string &reason)override;
	//更新群组列表
	virtual void onUpdateMyGroupList(const std::vector<easemob::EMGroupPtr> &list)override;
	//离开群组
	virtual void onLeaveGroup(const easemob::EMGroupPtr group, easemob::EMGroup::EMGroupLeaveReason reason)override;
private:
	const int m_clientId;
};

#endif