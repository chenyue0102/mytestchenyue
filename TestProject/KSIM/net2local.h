#pragma once
#include "KSStructDefine.h"
#include "message/emmessagebody.h"

namespace easemob
{
	class EMGroupSetting;
	class EMGroup;
}

namespace net2local
{
KSIMMessage Conver(easemob::EMMessage &in);
KSIMMessageBody makeBody(easemob::EMMessageBodyPtr &in);
KSIMGroupSetting Conver(const easemob::EMGroupSetting &in);
KSIMGroup Conver(const easemob::EMGroup &in);
};

