#pragma once
#include <mutex>
#include <map>
#include <memory>
#include <Windows.h>
#include "KSIMLogic.h"
#include "KSIMExport.h"

namespace easemob {
	class EMClient;
}
class ChatListener;
class ConnectionListener;
class ContactListener;
class ChatroomListener;
namespace KSIM{
class KSIMBuffer;
class KSIMInstance
{
private:
	struct ClientInfo
	{
		std::shared_ptr<easemob::EMClient> client;
		std::shared_ptr<ChatListener> chatListener;
		std::shared_ptr<ConnectionListener> connectionListener;
		std::shared_ptr<ContactListener> contactListener;
		std::shared_ptr<ChatroomListener> chatroomListener;
		KSIMCALLBACK callback;
		void *pUserData;
		ClientInfo()
			: client()
			, chatListener()
			, connectionListener()
			, contactListener()
			, chatroomListener()
			, callback(nullptr)
			, pUserData(nullptr)
		{

		}
	};
public:
	KSIMInstance();
	~KSIMInstance();
public:
	void init(HMODULE hModule);
	void destroy();
public:
	int createClient(int *pclientId);
	int destroyClient(int clientId);
	int invoke(int clientId, int msgid, KSIMBuffer & data);
	int setCallback(int clientId, void *pUserData, KSIMCALLBACK callback);
public:
	void doCallback(int clientId, int msgId, const KSIMBuffer &data);

	template<typename T>
	void doCallback(int clientId, int msgId, const T &data)
	{
		KSIM::KSIMBuffer buf;
		if (SerializeHelper::PackValue(data, buf, SerializeExport::EnumSerializeFormatJson))
		{
			doCallback(clientId, msgId, buf);
		}
		else
		{
			assert(false);
		}
	}
private:
	HMODULE m_hModule;
	mutable std::mutex m_mutex;
	volatile int m_nKey;
	std::map<int, ClientInfo> m_clientArray;
	KSIMLogic m_KSIMLogic;
};
extern KSIMInstance g_KSIMInstance;

}