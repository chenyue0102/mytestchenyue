#ifndef _GROUPMANAGERLISTENER_H_
#define _GROUPMANAGERLISTENER_H_
#include "emgroupmanager_listener.h"

class GroupManagerListener : public easemob::EMGroupManagerListener
{
public:
	GroupManagerListener(int clientId);
	virtual ~GroupManagerListener();
public:
	//���������
	virtual void onReceiveInviteFromGroup(const std::string groupId, const std::string& inviter, const std::string& inviteMessage)override;
	//�����ͬ�����
	virtual void onReceiveInviteAcceptionFromGroup(const easemob::EMGroupPtr group, const std::string& invitee)override;
	//����ľܾ�����
	virtual void onReceiveInviteDeclineFromGroup(const easemob::EMGroupPtr group, const std::string& invitee, const std::string &reason)override;
	//������Զ�ͬ�����
	virtual void onAutoAcceptInvitationFromGroup(const easemob::EMGroupPtr group, const std::string& inviter, const std::string& inviteMessage)override;
	//���������
	virtual void onReceiveJoinGroupApplication(const easemob::EMGroupPtr group, const std::string& from, const std::string& message)override;
	//�����ͬ�����
	virtual void onReceiveAcceptionFromGroup(const easemob::EMGroupPtr group)override;
	//����ľܾ�����
	virtual void onReceiveRejectionFromGroup(const std::string &groupId, const std::string &reason)override;
	//����Ⱥ���б�
	virtual void onUpdateMyGroupList(const std::vector<easemob::EMGroupPtr> &list)override;
	//�뿪Ⱥ��
	virtual void onLeaveGroup(const easemob::EMGroupPtr group, easemob::EMGroup::EMGroupLeaveReason reason)override;
private:
	const int m_clientId;
};

#endif