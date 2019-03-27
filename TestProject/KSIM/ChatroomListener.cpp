#include "ChatroomListener.h"
#include "KSEnumDefine.h"
#include "KSStructDefine.h"
#include "KSStructSerialize.h"
#include "net2local.h"
#include "KSIMInstance.h"

ChatroomListener::ChatroomListener(int clientId)
	: m_nClientId(clientId)
{

}

ChatroomListener::~ChatroomListener()
{

}

void ChatroomListener::onLeaveChatroom(const easemob::EMChatroomPtr chatroom, easemob::EMChatroom::EMChatroomLeaveReason reason)
{
	if (chatroom)
	{
		KSIMLeaveChatRoomAck leaveChatroom;
		leaveChatroom.chatroom = net2local::Conver(*chatroom);
		leaveChatroom.reason = reason;
		KSIM::g_KSIMInstance.doCallback(m_nClientId, EKSMsgIMLeaveChatRoom, leaveChatroom);
	}
	else
	{
		assert(false);
	}
}

void ChatroomListener::onMemberJoinedChatroom(const easemob::EMChatroomPtr chatroom, const std::string & member)
{
	if (chatroom)
	{
		KSIMAddChatRoomMember addChatroomMember;
		addChatroomMember.chatroom = net2local::Conver(*chatroom);
		addChatroomMember.member = member;
		KSIM::g_KSIMInstance.doCallback(m_nClientId, EKSMsgIMAddChatRoomMember, addChatroomMember);
	}
	else
	{
		assert(false);
	}
}

void ChatroomListener::onMemberLeftChatroom(const easemob::EMChatroomPtr chatroom, const std::string & member)
{
	if (chatroom)
	{
		KSIMDeleteChatRoomMember deleteChatroomMember;
		deleteChatroomMember.chatroom = net2local::Conver(*chatroom);
		deleteChatroomMember.member = member;
		KSIM::g_KSIMInstance.doCallback(m_nClientId, EKSMsgIMDeleteChatRoomMember, deleteChatroomMember);
	}
	else
	{
		assert(false);
	}
}
