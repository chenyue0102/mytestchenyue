#ifndef _CONNECTIONLISTENER_H_
#define _CONNECTIONLISTENER_H_
#include "emconnection_listener.h"

class ConnectionListener : public easemob::EMConnectionListener
{
public:
	ConnectionListener(int clientId);
	virtual ~ConnectionListener();
public:
	virtual void onDisconnect(easemob::EMErrorPtr error)override;
	virtual void onConnect()override;
private:
	const int m_clientId;
};

#endif