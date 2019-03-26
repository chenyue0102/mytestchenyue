#include "local2net.h"
#include <assert.h>
#include "KSEnumDefine.h"
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
#include "message/emlocationmessagebody.h"
#include "message/emvoicemessagebody.h"

namespace local2net
{

template<typename MsgBodyTypeSize>
typename MsgBodyTypeSize Conver(const KSIMSize &in)
{
	typename MsgBodyTypeSize ret = MsgBodyTypeSize();
	ret.mWidth = in.mWidth;
	ret.mHeight = in.mHeight;
	return ret;
}

template<typename LocalType, typename NetType>
std::shared_ptr<NetType> ConverAndUnPack(const std::string &in)
{
	std::shared_ptr<NetType> ret;

	do
	{
		LocalType localType = LocalType();
		if (!SerializeHelper::UnpackValue(in.data(), in.size(), localType, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
		ret = Conver(localType);
	} while (false);
	return ret;
}

easemob::EMTextMessageBodyPtr Conver(const KSIMTextMessageBody &in)
{
	easemob::EMTextMessageBodyPtr ret(new easemob::EMTextMessageBody(in.text.c_str()));
	return ret;
}

easemob::EMImageMessageBodyPtr Conver(const KSIMImageMessageBody &in)
{
	easemob::EMImageMessageBodyPtr ret(new easemob::EMImageMessageBody());

	ret->setDisplayName(in.displayName);
	ret->setLocalPath(in.localPath);
	ret->setRemotePath(in.remotePath);
	ret->setSecretKey(in.secretKey);
	ret->setFileLength(in.fileLength);
	ret->setDownloadStatus(static_cast<easemob::EMFileMessageBody::EMDownloadStatus>(in.downloadStatus));

	ret->setThumbnailDisplayName(in.thumbnailDisplayName);
	ret->setThumbnailLocalPath(in.thumbnailLocalPath);
	ret->setThumbnailRemotePath(in.thumbnailRemotePath);
	ret->setThumbnailSecretKey(in.thumbnailSecretKey);
	ret->setThumbnailSize(Conver<easemob::EMImageMessageBody::Size>(in.thumbnailSize));
	ret->setThumbnailFileLength(in.thumbnailFileLength);
	ret->setThumbnailDownloadStatus(static_cast<easemob::EMFileMessageBody::EMDownloadStatus>(in.thumbnailDownloadStatus));
	ret->setSize(Conver<easemob::EMImageMessageBody::Size>(in.size));
	return ret;
}

easemob::EMVideoMessageBodyPtr Conver(const KSIMVideoMessageBody &in)
{
	easemob::EMVideoMessageBodyPtr ret(new easemob::EMVideoMessageBody());

	ret->setDisplayName(in.displayName);
	ret->setLocalPath(in.localPath);
	ret->setRemotePath(in.remotePath);
	ret->setSecretKey(in.secretKey);
	ret->setFileLength(in.fileLength);
	ret->setDownloadStatus(static_cast<easemob::EMFileMessageBody::EMDownloadStatus>(in.downloadStatus));

	ret->setThumbnailLocalPath(in.thumbnailLocalPath);
	ret->setThumbnailRemotePath(in.thumbnailRemotePath);
	ret->setThumbnailSecretKey(in.thumbnailSecretKey);
	ret->setThumbnailDownloadStatus(static_cast<easemob::EMFileMessageBody::EMDownloadStatus>(in.thumbnailDownloadStatus));
	ret->setSize(Conver<easemob::EMVideoMessageBody::Size>(in.size));
	ret->setDuration(in.duration);
	return ret;
}

easemob::EMLocationMessageBodyPtr Conver(const KSIMLocationMessageBody &in)
{
	easemob::EMLocationMessageBodyPtr ret(new easemob::EMLocationMessageBody(in.latitude, in.longitude, in.address));
	
	return ret;
}

easemob::EMVoiceMessageBodyPtr Conver(const KSIMVoiceMessageBody &in)
{
	easemob::EMVoiceMessageBodyPtr ret(new easemob::EMVoiceMessageBody());

	ret->setDisplayName(in.displayName);
	ret->setLocalPath(in.localPath);
	ret->setRemotePath(in.remotePath);
	ret->setSecretKey(in.secretKey);
	ret->setFileLength(in.fileLength);
	ret->setDownloadStatus(static_cast<easemob::EMFileMessageBody::EMDownloadStatus>(in.downloadStatus));

	ret->setDuration(in.duration);

	return ret;
}

easemob::EMFileMessageBodyPtr Conver(const KSIMFileMessageBody &in)
{
	easemob::EMFileMessageBodyPtr ret(new easemob::EMFileMessageBody());

	ret->setDisplayName(in.displayName);
	ret->setLocalPath(in.localPath);
	ret->setRemotePath(in.remotePath);
	ret->setSecretKey(in.secretKey);
	ret->setFileLength(in.fileLength);
	ret->setDownloadStatus(static_cast<easemob::EMFileMessageBody::EMDownloadStatus>(in.downloadStatus));

	return ret;
}

easemob::EMCmdMessageBodyPtr Conver(const KSIMCmdMessageBody &in)
{
	easemob::EMCmdMessageBodyPtr ret(new easemob::EMCmdMessageBody(in.action));
	ret->setParams(in.params);
	return ret;
}

easemob::EMMessageBodyPtr makeMessageBody(const KSIMMessageBody & req)
{
	easemob::EMMessageBodyPtr body;
	switch (req.type)
	{
		case EKSIMMessageBodyText:
		{
			body = ConverAndUnPack<KSIMTextMessageBody, easemob::EMTextMessageBody>(req.body);
			break;
		}
		case EKSIMMessageBodyImage:
		{
			body = ConverAndUnPack<KSIMImageMessageBody, easemob::EMImageMessageBody>(req.body);
			break;
		}
		case EKSIMMessageBodyVideo:
		{
			body = ConverAndUnPack<KSIMVideoMessageBody, easemob::EMVideoMessageBody>(req.body);
			break;
		}
		case EKSIMMessageBodyLocation:
		{
			body = ConverAndUnPack<KSIMLocationMessageBody, easemob::EMLocationMessageBody>(req.body);
			break;
		}
		case EKSIMMessageBodyVoice:
		{
			body = ConverAndUnPack<KSIMVoiceMessageBody, easemob::EMVoiceMessageBody>(req.body);
			break;
		}
		case EKSIMMessageBodyFile:
		{
			body = ConverAndUnPack<KSIMFileMessageBody, easemob::EMFileMessageBody>(req.body);
			break;
		}
		case EKSIMMessageBodyCommand:
		{
			body = ConverAndUnPack<KSIMCmdMessageBody, easemob::EMCmdMessageBody>(req.body);
			break;
		}
		default:
		{
			assert(false);
			break;
		}
	}
	assert(body);
	return body;
}

easemob::EMGroupSetting Conver(const KSIMGroupSetting & req)
{
	easemob::EMGroupSetting ret;
	ret.setStyle(static_cast<easemob::EMGroupSetting::EMGroupStyle>(req.style));
	ret.setMaxUserCount(req.maxUserCount);
	return ret;
}

}
