#include "net2local.h"
#include <assert.h>
#include "KSSerializeHelper.h"
#include "KSStructDefine.h"
#include "KSStructSerialize.h"

#include "emgroupsetting.h"
#include "emgroup.h"
#include "message/emmessage.h"
#include "message/emtextmessagebody.h"
#include "message/emcmdmessagebody.h"
#include "message/emfilemessagebody.h"
#include "message/emimagemessagebody.h"
#include "message/emvideomessagebody.h"

namespace net2local
{
KSIMMessage Conver(easemob::EMMessage &in)
{
	KSIMMessage ret;
	ret.msgId = in.msgId();
	ret.from = in.from();
	ret.to = in.to();
	ret.conversationId = in.conversationId();
	ret.status = in.status();
	ret.chatType = in.chatType();
	ret.msgDirection = in.msgDirection();
	ret.isRead = in.isRead();
	ret.isListened = in.isListened();
	ret.isReadAcked = in.isReadAcked();
	ret.isDeliverAcked = in.isDeliverAcked();
	ret.isOffline = in.isOffline();
	ret.timestamp = in.timestamp();
	ret.localTime = in.localTime();
	for (auto body : in.bodies())
	{
		ret.bodies.push_back(makeBody(body));
	}
	//ext
	return ret;
}

template<typename ResultType, typename NetTypePointer>
std::string ConverAndPack(easemob::EMMessageBodyPtr &in)
{
	std::string ret;

	do
	{
		std::shared_ptr<typename NetTypePointer> body = std::dynamic_pointer_cast<typename NetTypePointer, easemob::EMMessageBody>(in);
		if (!body)
		{
			assert(false);
			break;
		}
		ResultType resultBody = Conver(*body);
		if (!SerializeHelper::PackValue(resultBody, ret, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
	} while (false);
	return ret;
}

KSIMTextMessageBody Conver(const easemob::EMTextMessageBody &in)
{
	KSIMTextMessageBody ret;
	ret.text = in.text();
	return ret;
}

KSIMFileMessageBody Conver(const easemob::EMFileMessageBody &in)
{
	KSIMFileMessageBody ret;
	ret.displayName = in.displayName();
	ret.localPath = in.localPath();
	ret.remotePath = in.remotePath();
	ret.secretKey = in.secretKey();
	ret.fileLength = in.fileLength();
	ret.downloadStatus = in.downloadStatus();
	return ret;
}

KSIMCmdMessageBody Conver(const easemob::EMCmdMessageBody &in)
{
	KSIMCmdMessageBody ret;
	ret.action = in.action();
	ret.params = in.params();
	return ret;
}

KSIMSize Conver(const easemob::EMImageMessageBody::Size &in)
{
	KSIMSize ret;
	ret.mWidth = in.mWidth;
	ret.mHeight = in.mHeight;
	return ret;
}

KSIMImageMessageBody Conver(const easemob::EMImageMessageBody &in)
{
	KSIMImageMessageBody ret;
	ret.displayName = in.displayName();
	ret.localPath = in.localPath();
	ret.remotePath = in.remotePath();
	ret.secretKey = in.secretKey();
	ret.fileLength = in.fileLength();
	ret.downloadStatus = in.downloadStatus();

	ret.thumbnailDisplayName = in.thumbnailDisplayName();
	ret.thumbnailLocalPath = in.thumbnailLocalPath();
	ret.thumbnailRemotePath = in.thumbnailRemotePath();
	ret.thumbnailSecretKey = in.thumbnailSecretKey();
	ret.thumbnailSize = Conver(in.thumbnailSize());
	ret.thumbnailFileLength = in.thumbnailFileLength();
	ret.thumbnailDownloadStatus = in.thumbnailDownloadStatus();
	ret.size = Conver(in.size());
	return ret;
}

KSIMMessageBody makeBody(easemob::EMMessageBodyPtr &in)
{
	KSIMMessageBody ret;
	ret.type = in->type();
	switch (in->type())
	{
	case easemob::EMMessageBody::TEXT:
	{
		ret.body = ConverAndPack<KSIMTextMessageBody, easemob::EMTextMessageBody>(in);
		break;
	}
	case easemob::EMMessageBody::IMAGE:
	{
		ret.body = ConverAndPack<KSIMImageMessageBody, easemob::EMImageMessageBody>(in);
		break;
	}
	case easemob::EMMessageBody::VIDEO:
	{
		break;
	}
	case easemob::EMMessageBody::LOCATION:
	{
		break;
	}
	case easemob::EMMessageBody::VOICE:
	{
		//ret.body = ConverAndPack<KSIMFileMessageBody, easemob::EMFileMessageBody>(in);
		break;
	}
	case easemob::EMMessageBody::FILE:
	{
		ret.body = ConverAndPack<KSIMFileMessageBody, easemob::EMFileMessageBody>(in);
		break;
	}
	case easemob::EMMessageBody::COMMAND:
	{
		ret.body = ConverAndPack<KSIMCmdMessageBody, easemob::EMCmdMessageBody>(in);
		break;
	}
	default:
	{
		ret.type = in->type();
		assert(false);
		break;
	}
	}

	return ret;
}

KSIMGroupSetting Conver(const easemob::EMGroupSetting &in)
{
	KSIMGroupSetting ret;
	ret.style = in.style();
	ret.maxUserCount = in.maxUserCount();
	return ret;
}

KSIMGroup Conver(const easemob::EMGroup &in)
{
	KSIMGroup ret;
	ret.groupId = in.groupId();
	ret.groupSubject = in.groupSubject();
	ret.groupDescription = in.groupDescription();
	ret.groupOwner = in.groupOwner();
	if (nullptr != in.groupSetting())
	{
		ret.groupSetting = Conver(*(in.groupSetting()));
	}
	ret.groupMembersCount = in.groupMembersCount();
	ret.isPushEnabled = in.isPushEnabled();
	ret.isMessageBlocked = in.isMessageBlocked();
	if (nullptr != in.groupMembers())
	{
		ret.groupMembers = *(in.groupMembers());
	}
	if (nullptr != in.groupBans())
	{
		ret.groupBans = *(in.groupBans());
	}
	return ret;
}
}
