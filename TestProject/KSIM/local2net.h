#pragma once
#include "KSStructDefine.h"
#include "message/emmessagebody.h"

namespace local2net
{
easemob::EMMessageBodyPtr makeMessageBody(const KSIMMessageBody & req);
};

