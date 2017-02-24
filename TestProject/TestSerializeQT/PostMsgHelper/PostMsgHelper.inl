#include "PostMsgHelper.h"
#include <assert.h>
#include "InvokeNotify.h"

#include "DealMsgHelper.h"

namespace PostMsgHelper
{
inline bool InnerPostMsg(unsigned long uMsgID, const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, void *pInterface)
{
	//模拟把数据发出去
	DealMsgHelper::CDealMsgHelper *pDealMsg = reinterpret_cast<DealMsgHelper::CDealMsgHelper*>(pInterface);
	return pDealMsg->InvokeNotify(uMsgID, pBuffer, ulBytes, SerializeFormat);
}

inline bool InnerSendMsg(unsigned long uMsgID, const void *pBuffer, unsigned long ulBytes,
	SerializeExport::EnumSerializeFormat SerializeFormat, std::string &strResult, unsigned long *pResult, 
	void *pInterface)
{
	//模拟把数据发出去
	DealMsgHelper::CDealMsgHelper *pDealMsg = reinterpret_cast<DealMsgHelper::CDealMsgHelper*>(pInterface);
	return pDealMsg->InvokeQuery(uMsgID, pBuffer, ulBytes, SerializeFormat, strResult, pResult);
}

template<typename ParamType>
inline bool PostNotifyMsg(unsigned long uMsgID, const ParamType &t, 
	SerializeExport::EnumSerializeFormat SerializeFormat, void *pInterface)
{
	bool bRes = false;

	do 
	{
		std::string strData;
		if (!DealMsgHelper::PackValue(t, strData, SerializeFormat))
		{
			assert(false);
			break;
		}
		if (!InnerPostMsg(uMsgID, strData.data(), strData.size(), SerializeFormat, pInterface))
		{
			assert(false);
			break;
		}

		bRes = true;
	} while (false);
	return bRes;
}

bool PostNotifyMsg(unsigned long uMsgID, void *pInterface)
{
	bool bRes = false;

	do 
	{
		if (!InnerPostMsg(uMsgID, nullptr, 0, EnumSerializeFormatNone, pInterface))
		{
			assert(false);
			break;
		}

		bRes = true;
	} while (false);
	return bRes;
}

template<typename InParamType, typename OutParamType>
inline bool SendQueryMsg(unsigned long uMsgID, const InParamType &in, OutParamType &out, unsigned long *pResult,
	SerializeExport::EnumSerializeFormat SerializeFormat, void *pInterface)
{
	bool bRes = false;

	do 
	{
		std::string strData;
		if (!DealMsgHelper::PackValue(in, strData, SerializeFormat))
		{
			assert(false);
			break;
		}
		std::string strResult;
		if (!InnerSendMsg(uMsgID, strData.data(), strData.size(), SerializeFormat, strResult, pResult, pInterface))
		{
			assert(false);
			break;
		}
		if (!DealMsgHelper::UnpackValue(strResult.data(), strResult.size(), out, SerializeFormat))
		{
			assert(false);
			break;
		}

		bRes = true;
	} while (false);
	return bRes;
}

template<typename InOutParamType>
inline bool SendQueryMsg(unsigned long uMsgID, InOutParamType &inout, unsigned long *pResult, 
	SerializeExport::EnumSerializeFormat SerializeFormat, void *pInterface)
{
	bool bRes = false;

	do 
	{
		std::string strData;
		if (!DealMsgHelper::PackValue(inout, strData, SerializeFormat))
		{
			assert(false);
			break;
		}
		std::string strResult;
		if (!InnerSendMsg(uMsgID, strData.data(), strData.size(), SerializeFormat, strResult, pResult, pInterface))
		{
			assert(false);
			break;
		}
		//是否清空现有数据？
		inout = InOutParamType();
		if (!DealMsgHelper::UnpackValue(strResult.data(), strResult.size(), inout, SerializeFormat))
		{
			assert(false);
			break;
		}

		bRes = true;
	} while (false);
	return bRes;
}
}