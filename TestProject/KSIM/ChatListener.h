#ifndef _CHATLISTENER_H
#define _CHATLISTENER_H
#include "emchatmanager_listener.h"


class ChatListener : public easemob::EMChatManagerListener
{
public:
	ChatListener(int nClientId);
	virtual ~ChatListener();
public:
	virtual void onReceiveMessages(const easemob::EMMessageList &messages)override;
private:
	const int m_nClientId;
};
#endif