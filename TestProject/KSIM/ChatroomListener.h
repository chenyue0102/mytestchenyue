#ifndef _CHATROOMLISTENER_H_
#define _CHATROOMLISTENER_H_
#include "emchatroommanager_listener.h"

class ChatroomListener : public easemob::EMChatroomManagerListener
{
public:
	ChatroomListener(int clientId);
	virtual ~ChatroomListener();
public:
	/**
	* \brief Callback user when user is kicked out from a chatroom or the chatroom is destroyed.
	*
	* @param  The chatroom that user left.
	* @param  The leave reason.
	* @return NA
	*/
	virtual void onLeaveChatroom(const easemob::EMChatroomPtr chatroom, easemob::EMChatroom::EMChatroomLeaveReason reason)override;

	/**
	* \brief Callback user when a user join the chatroom.
	*
	* @param  The chatroom that user joined.
	* @param  The member.
	* @return NA
	*/
	virtual void onMemberJoinedChatroom(const easemob::EMChatroomPtr chatroom, const std::string &member)override;

	/**
	* \brief Callback user when a user leave the chatroom.
	*
	* @param  The chatroom that user left.
	* @param  The member.
	* @return NA
	*/
	virtual void onMemberLeftChatroom(const easemob::EMChatroomPtr chatroom, const std::string &member)override;
private:
	const int m_nClientId;
};
#endif