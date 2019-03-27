#include "stdafx.h"
#include <assert.h>
#include "KSIMInstance.h"
#include "ChatListener.h"
#include "ConnectionListener.h"
#include "ContactListener.h"
#include "ChatroomListener.h"
//
#include "EMClient.h"
#include "emchatconfigs.h"
#include "emchatmanager_interface.h"
#include "emcontactmanager_interface.h"
#include "emchatroommanager_interface.h"

#ifdef _DEBUG
#pragma comment(lib, "../lib/easemob_d.lib")
#else
#pragma comment(lib, "../lib/easemob.lib")
#endif

using namespace easemob;
namespace KSIM{
KSIMInstance g_KSIMInstance;
KSIMInstance::KSIMInstance()
	: m_hModule(nullptr)
	, m_mutex()
	, m_nKey(1)
	, m_clientArray()
	, m_KSIMLogic()
{
}

KSIMInstance::~KSIMInstance()
{
}

void KSIMInstance::init(HMODULE hModule)
{
	m_hModule = hModule;
}

void KSIMInstance::destroy()
{
	m_hModule = nullptr;
}

static std::string GetExePath()
{
	std::string strPath;

	do
	{
		char szModule[MAX_PATH] = { 0 };
		if (0 == GetModuleFileNameA(nullptr, szModule, _countof(szModule) - 1))
		{
			assert(false);
			break;
		}
		char *pPos = strrchr(szModule, '\\');
		if (nullptr == pPos)
		{
			assert(false);
			break;
		}
		*pPos = '\0';
		strPath = szModule;
	} while (false);
	
	return strPath;
}

int KSIMInstance::createClient(int *pclientId)
{
	int error = -1;

	do
	{
		if (nullptr == pclientId)
		{
			assert(false);
			break;
		}
		std::string sAppDir = GetExePath();
		sAppDir += "/easemob";
		EMChatConfigsPtr configs(new EMChatConfigs(sAppDir, sAppDir, "easemob-demo#chatdemoui"));
		configs->setOs(EMChatConfigs::OS_MSWIN);
		configs->setEnableConsoleLog(false);
		configs->setClientResource("windows");
		std::shared_ptr<EMClient> chatClient(EMClient::create(configs));
		if (!chatClient)
		{
			assert(false);
			break;
		}
		std::lock_guard<std::mutex> lk(m_mutex);
		while (true)
		{
			if (m_clientArray.find(static_cast<int>(m_nKey)) == m_clientArray.end())
			{
				break;
			}
			else
			{
				m_nKey++;
			}
		}

		int clientId = m_nKey++;

		std::shared_ptr<ChatListener> chatListener(new ChatListener(clientId));
		chatClient->getChatManager().addListener(chatListener.get());

		std::shared_ptr<ConnectionListener> connectionListener(new ConnectionListener(clientId));
		chatClient->addConnectionListener(connectionListener.get());

		std::shared_ptr<ContactListener> contactListener(new ContactListener(clientId));
		chatClient->getContactManager().registerContactListener(contactListener.get());

		std::shared_ptr<ChatroomListener> chatroomListener(new ChatroomListener(clientId));
		chatClient->getChatroomManager().addListener(chatroomListener.get());
		
		ClientInfo info;
		info.client = chatClient;
		info.callback = nullptr;
		info.chatListener = chatListener;
		info.connectionListener = connectionListener;
		info.contactListener = contactListener;
		info.chatroomListener = chatroomListener;
		m_clientArray[clientId] = info;
		*pclientId = clientId;
		
		error = 0;
	} while (false);
	
	return error;
}

int KSIMInstance::destroyClient(int clientId)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	auto iter = m_clientArray.find(clientId);
	if (iter != m_clientArray.end())
	{
		ClientInfo &info = iter->second;
		if (info.client)
		{
			if (info.chatListener)
			{
				info.client->getChatManager().removeListener(info.chatListener.get());
			}
			if (info.connectionListener)
			{
				info.client->removeConnectionListener(info.connectionListener.get());
			}
			if (info.contactListener)
			{
				info.client->getContactManager().removeContactListener(info.contactListener.get());
			}
			if (info.chatroomListener)
			{
				info.client->getChatroomManager().removeListener(info.chatroomListener.get());
			}
			info.client->logout();
		}
		m_clientArray.erase(iter);
		return 0;
	}
	else
	{
		assert(false);
		return -1;
	}
}

int KSIMInstance::invoke(int clientId, int msgid, KSIMBuffer & data)
{
	std::shared_ptr<easemob::EMClient> pClient;
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		auto iter = m_clientArray.find(clientId);
		if (iter != m_clientArray.end())
		{
			pClient = iter->second.client;
		}
	}
	if (!pClient)
	{
		assert(false);
		return -1;
	}
	auto &client = *pClient;
	return m_KSIMLogic.invoke(client, msgid, data);
}

int KSIMInstance::setCallback(int clientId, void *pUserData, KSIMCALLBACK callback)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	auto iter = m_clientArray.find(clientId);
	if (iter != m_clientArray.end())
	{
		assert(nullptr == iter->second.callback);
		iter->second.callback = callback;
		iter->second.pUserData = pUserData;
		return 0;
	}
	else
	{
		assert(false);
		return -1;
	}
}

void KSIMInstance::doCallback(int clientId, int msgId, const KSIMBuffer & data)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	auto iter = m_clientArray.find(clientId);
	if (iter != m_clientArray.end()
		&& iter->second.callback != nullptr)
	{
		KSIMCALLBACK callback = iter->second.callback;
		void *pUserData = iter->second.pUserData;
		
		lk.unlock();
		//如果正在处理回调，则removeListener会阻塞，不会造成回调函数访问非法
		callback(clientId, msgId, data, pUserData);
	}
	else
	{
		assert(false);
	}
}
}