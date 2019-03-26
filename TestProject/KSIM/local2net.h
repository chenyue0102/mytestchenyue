#pragma once
#include "KSStructDefine.h"
#include "message/emmessagebody.h"
#include "emgroupsetting.h"

namespace local2net
{
easemob::EMMessageBodyPtr makeMessageBody(const KSIMMessageBody & req);
easemob::EMGroupSetting Conver(const KSIMGroupSetting &req);
};

