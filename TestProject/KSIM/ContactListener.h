#ifndef _CONTACTLISTENER_H_
#define _CONTACTLISTENER_H_
#include "emcontactlistener.h"


class ContactListener : public easemob::EMContactListener
{
public:
	ContactListener(int clientId);
	virtual ~ContactListener();
public:
	virtual void onContactAdded(const std::string &username)override;
	virtual void onContactDeleted(const std::string &username)override;
	virtual void onContactInvited(const std::string &username, std::string &reason)override;
	virtual void onContactAgreed(const std::string &username)override;
	virtual void onContactRefused(const std::string &username)override;
private:
	const int m_clientId;
};
#endif