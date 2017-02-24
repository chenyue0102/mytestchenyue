#include "DealMsgHelper.h"
#include <assert.h>

namespace DealMsgHelper
{

/************************************************************************/
/* CDealMsgHelper                                                       */
/************************************************************************/
inline CDealMsgHelper::CDealMsgHelper()
	: m_notifyCallbackFun()
	, m_queryCallbackFun()
{

}

inline CDealMsgHelper::~CDealMsgHelper()
{
	for each(auto &pair in m_notifyCallbackFun)
	{
		delete pair.second;
	}
	m_notifyCallbackFun.clear();

	for each(auto &pair in m_queryCallbackFun)
	{
		delete pair.second;
	}
	m_queryCallbackFun.clear();
}

inline bool CDealMsgHelper::InvokeNotify(unsigned long uMsg, const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat)
{
	bool bRes = false;

	do
	{
		auto itor = m_notifyCallbackFun.find(uMsg);
		if (itor == m_notifyCallbackFun.end())
		{
			assert(false);
			break;
		}
		auto pTemp = itor->second;
		if (nullptr == pTemp)
		{
			assert(false);
			break;
		}
		if (!pTemp->Notify(pBuffer, ulBytes, SerializeFormat))
		{
			assert(false);
			break;
		}
		bRes = true;
	} while (false);

	return bRes;
}

inline bool CDealMsgHelper::InvokeQuery(unsigned long uMsg, const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat,
	std::string &strData, unsigned long *pResult)
{
	bool bRes = false;

	do
	{
		auto itor = m_queryCallbackFun.find(uMsg);
		if (itor == m_queryCallbackFun.end())
		{
			assert(false);
			break;
		}
		auto pTemp = itor->second;
		if (nullptr == pTemp)
		{
			assert(false);
			break;
		}
		if (!pTemp->Query(pBuffer, ulBytes, SerializeFormat, strData, pResult))
		{
			assert(false);
			break;
		}
		bRes = true;
	} while (false);

	return bRes;
}

template<typename ClassType, typename ParamType>
bool CDealMsgHelper::RegMsg(unsigned long ulMsgID, ClassType *pObject, void (ClassType::*callFun)(const ParamType &))
{
	bool bRes = false;

	do
	{
		if (nullptr == pObject)
		{
			assert(false);
			break;
		}
		if (m_notifyCallbackFun.find(ulMsgID) != m_notifyCallbackFun.end())
		{
			assert(false);
			break;
		}
		CInvokeNotifyBase *pInvokeFun = new CInvokeNotifyFun<typename ClassType, typename ParamType>(pObject, callFun);
		auto res = m_notifyCallbackFun.insert(std::make_pair(ulMsgID, pInvokeFun));
		assert(res.second);
		bRes = true;
	} while (false);

	return bRes;
}

template<typename ClassType>
bool CDealMsgHelper::RegMsg(unsigned long ulMsgID, ClassType *pObject, void (ClassType::*callFun)())
{
	bool bRes = false;

	do
	{
		if (nullptr == pObject)
		{
			assert(false);
			break;
		}
		if (m_notifyCallbackFun.find(ulMsgID) != m_notifyCallbackFun.end())
		{
			assert(false);
			break;
		}
		CInvokeNotifyBase *pInvokeFun = new CInvokeNotifyEmptyFun<typename ClassType>(pObject, callFun);
		auto res = m_notifyCallbackFun.insert(std::make_pair(ulMsgID, pInvokeFun));
		assert(res.second);
		bRes = true;
	} while (false);

	return bRes;
}

template<typename ClassType, typename InParamType, typename OutParamType>
bool CDealMsgHelper::RegMsg(unsigned long ulMsgID, ClassType *pObject, unsigned long (ClassType::*callFun)(const InParamType&, OutParamType &))
{
	bool bRes = false;

	do
	{
		if (nullptr == pObject)
		{
			assert(false);
			break;
		}
		if (m_queryCallbackFun.find(ulMsgID) != m_queryCallbackFun.end())
		{
			assert(false);
			break;
		}
		CInvokeQueryBase *pInvokeFun = new CInvokeQueryFun<typename ClassType, typename InParamType, typename OutParamType>(pObject, callFun);
		auto res = m_queryCallbackFun.insert(std::make_pair(ulMsgID, pInvokeFun));
		assert(res.second);
		bRes = true;
	} while (false);

	return bRes;
}

template<typename ClassType, typename InOutParamType>
bool CDealMsgHelper::RegMsg(unsigned long ulMsgID, ClassType *pObject, unsigned long (ClassType::*callFun)(InOutParamType &))
{
	bool bRes = false;

	do
	{
		if (nullptr == pObject)
		{
			assert(false);
			break;
		}
		if (m_queryCallbackFun.find(ulMsgID) != m_queryCallbackFun.end())
		{
			assert(false);
			break;
		}
		CInvokeQueryBase *pInvokeFun = new CInvokeQueryInOutFun<typename ClassType, typename InOutParamType>(pObject, callFun);
		auto res = m_queryCallbackFun.insert(std::make_pair(ulMsgID, pInvokeFun));
		assert(res.second);
		bRes = true;
	} while (false);

	return bRes;
}
}