#pragma once
#include "KSStructDefine.h"

namespace easemob
{
	class EMClient;
}

namespace KSIM{
class KSIMBuffer;
class KSIMLogic
{
public:
	KSIMLogic();
	~KSIMLogic();
public:
	int invoke(easemob::EMClient &client, int msgid, KSIMBuffer & data);
private:
	template<typename PARAM>
	int innerInvoke(easemob::EMClient &client, KSIMBuffer & data, int(KSIMLogic::*callFun)(easemob::EMClient &client, const PARAM &req));
	template<typename PARAM>
	int innerInvoke(easemob::EMClient &client, KSIMBuffer & data, int(KSIMLogic::*callFun)(easemob::EMClient &client, PARAM &req));
private:
	int login(easemob::EMClient &client, const KSIMLogin &req);
	int logout(easemob::EMClient &client);
	int sendMessage(easemob::EMClient &client, const KSIMMessage &req);
private:
	int getContacts(easemob::EMClient &client, KSIMGetContacts &out);
	int deleteContact(easemob::EMClient &client, const KSIMDeleteContact &req);
	int InviteContact(easemob::EMClient &client, const KSIMInviteContact &req);
private:
	int getGroupList(easemob::EMClient &client, KSIMGetGroupList &out);
	int createGroup(easemob::EMClient &client, const KSIMCreateGroup &req);
	int leaveGroup(easemob::EMClient &client, const KSIMLeaveGroupReq &req);
	int destroyGroup(easemob::EMClient &client, const KSIMDestroyGroupReq &req);
	int ModifyGroupPropery(easemob::EMClient &client, const KSIMModifyGroupProperty &req);
private:
	int getChatRoomList(easemob::EMClient &client, KSIMGetChatRoomList &out);
	int joinChatRoom(easemob::EMClient &client, const KSIMJoinChatRoom &req);
	int leaveChatRoom(easemob::EMClient &client, const KSIMLeaveChatRoomReq &req);
};

}