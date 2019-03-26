#include "KSIMLogic.h"
#include <vector>
#include "KSIMBuffer.h"

#include "KSSerializeHelper.h"
#include "KSEnumDefine.h"
#include "KSStructDefine.h"
#include "KSStructSerialize.h"

#include "net2local.h"

#include "emerror.h"
#include "EMClient.h"
#include "emgroupmanager_interface.h"
#include "emgroup.h"
#include "emlogininfo.h"
#include "emchatmanager_interface.h"

#include "message/emmessage.h"
#include "message/emtextmessagebody.h"
#include "message/emmessagebody.h"
#include "message/emcmdmessagebody.h"

#ifdef _DEBUG
#pragma comment(lib, "../lib/KSSerializeD.lib")
#else
#pragma comment(lib, "../lib/KSSerialize.lib")
#endif

using namespace easemob;
namespace KSIM{
KSIMLogic::KSIMLogic()
{
}


KSIMLogic::~KSIMLogic()
{
}

int KSIMLogic::invoke(easemob::EMClient & client, int msgid, KSIMBuffer & data)
{
	int ret = -1;
	switch (msgid)
	{
		case EKSMsgIMLogin:
		{
			ret = innerInvoke(client, data, &KSIMLogic::login);
			break;
		}
		case EKSMsgIMLogout:
		{
			ret = logout(client);
			break;
		}
		case EKSMsgIMGetGroupList:
		{
			ret = innerInvoke(client, data, &KSIMLogic::getGroupList);
			break;
		}
		case EKSMsgIMMMessage:
		{
			ret = innerInvoke(client, data, &KSIMLogic::sendMessage);
			break;
		}
		default:
		{
			assert(false);
			break;
		}
	}
	return ret;
}

template<typename PARAM>
int KSIMLogic::innerInvoke(easemob::EMClient &client, KSIMBuffer & data, int(KSIMLogic::*callFun)(easemob::EMClient &client, const PARAM &req))
{
	int ret = -1;

	do
	{
		PARAM req;
		if (!SerializeHelper::UnpackValue(data.data(), data.size(), req, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
		ret = (this->*callFun)(client, req);
	} while (false);
	return ret;
}

template<typename PARAM>
int KSIMLogic::innerInvoke(easemob::EMClient &client, KSIMBuffer & data, int(KSIMLogic::*callFun)(easemob::EMClient &client, PARAM &req))
{
	int ret = -1;

	do
	{
		PARAM ack;
		if ((ret = (this->*callFun)(client, ack)) != 0)
		{
			assert(false);
			break;
		}
		data.clear();
		if (!SerializeHelper::PackValue(ack, data, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
		ret = 0;
	} while (false);
	return ret;
}

int KSIMLogic::login(easemob::EMClient &client, const KSIMLogin & req)
{
	easemob::EMErrorPtr result = client.login(req.username, req.password);
	if (result->mErrorCode == easemob::EMError::EM_NO_ERROR)
	{
		//登录成功 
		return 0;
	}
	else 
	{
		return -result->mErrorCode;
	}
}

int KSIMLogic::logout(easemob::EMClient & client)
{
	client.logout();
	return 0;
}

easemob::EMMessageBodyPtr makeMessageBody(const KSIMMessageBody & req)
{
	easemob::EMMessageBodyPtr body;
	switch (req.type)
	{
		case EMessageBodyTypeText:
		{
			KSIMTextMessageBody textBody;
			if (SerializeHelper::UnpackValue(req.body.data(), req.body.size(), textBody, SerializeExport::EnumSerializeFormatJson))
			{
				body = easemob::EMTextMessageBodyPtr(new easemob::EMTextMessageBody(textBody.text.c_str()));
			}
			else
			{
				assert(false);
			}
			break;
		}
		case EMessageBodyTypeCommand:
		{
			KSIMCmdMessageBody cmdBody;
			if (SerializeHelper::UnpackValue(req.body.data(), req.body.size(), cmdBody, SerializeExport::EnumSerializeFormatJson))
			{
				easemob::EMCmdMessageBodyPtr tempBody = easemob::EMCmdMessageBodyPtr(new easemob::EMCmdMessageBody(cmdBody.action));
				tempBody->setParams(cmdBody.params);
				body = tempBody;
			}
			else
			{
				assert(false);
			}
			break;
		}
		default:
		{
			assert(false);
			break;
		}
	}
	return body;
}

int KSIMLogic::sendMessage(easemob::EMClient & client, const KSIMMessage & req)
{
	int ret = -1;

	do
	{
		if (req.bodies.empty())
		{
			assert(false);
			break;
		}
		easemob::EMMessageBodyPtr body = makeMessageBody(req.bodies[0]);
		easemob::EMMessagePtr msg = easemob::EMMessage::createSendMessage(
			client.getLoginInfo().loginUser(), req.to, body, static_cast<easemob::EMMessage::EMChatType>(req.chatType));

		//EMCallbackPtr msgCallback(new EMCallback(m_coh,
		//	[=](void)->bool
		//{
		//	//std::string enc = URLEncode(utf8);
		//	//callback->Success(enc.c_str());
		//	return true;
		//},
		//	[=](const easemob::EMErrorPtr)->bool
		//{
		//	return false;
		//},
		//	[](int) {}));
		////设置消息回调
		//msg->setCallback(msgCallback);

		//发送消息
		client.getChatManager().sendMessage(msg);
		ret = 0;
	} while (false);
	return ret;
}

int KSIMLogic::getGroupList(easemob::EMClient & client, KSIMGetGroupList & out)
{
	int ret = -1;

	do
	{
		easemob::EMError error;
		easemob::EMGroupList groupList = client.getGroupManager().fetchAllMyGroups(error);
		if (error.mErrorCode != easemob::EMError::EM_NO_ERROR)
		{
			assert(false);
			break;
		}
		for (auto &group : groupList)
		{
			if (group)
			{
				out.groupList.push_back(net2local::Conver(*group));
			}
			else
			{
				assert(false);
			}
		}
		ret = 0;
	} while (false);
	return ret;
}
}