#include "KSIMExport.h"
#include "KSIMInstance.h"

namespace KSIM{

int KSIMDLL createClient(int *pclientId)
{
	return g_KSIMInstance.createClient(pclientId);
}

int KSIMDLL destroyClient(int clientId)
{
	return g_KSIMInstance.destroyClient(clientId);
}

int KSIMDLL invoke(int clientId, int msgid, KSIMBuffer & data)
{
	return g_KSIMInstance.invoke(clientId, msgid, data);
}

int KSIMDLL setCallback(int clientId, void *pUserData, KSIMCALLBACK callback)
{
	return g_KSIMInstance.setCallback(clientId, pUserData, callback);
}


}