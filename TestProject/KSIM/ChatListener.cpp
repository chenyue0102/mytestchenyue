#include "ChatListener.h"
#include <memory>
#include "KSStructDefine.h"
#include "KSStructSerialize.h"
#include "KSEnumDefine.h"
#include "KSIMInstance.h"
#include "net2local.h"

#include "emattributevalue.h"
#include "message/emmessage.h"
#include "message/emtextmessagebody.h"
#include "message/emmessagebody.h"
#include "message/emcmdmessagebody.h"


ChatListener::ChatListener(int nClientId)
	: m_nClientId(nClientId)
{

}

ChatListener::~ChatListener()
{

}

void ChatListener::onReceiveMessages(const easemob::EMMessageList &messages)
{
	for (const easemob::EMMessagePtr &msg : messages)
	{
		if (!msg)
		{
			assert(false);
			continue;
		}
		KSIMMessage data = net2local::Conver(*msg);
		KSIM::g_KSIMInstance.doCallback(m_nClientId, EKSMsgIMMMessage, data);
	}
}