#include "PostMsgHelper.h"
#include <assert.h>
#include "InvokeNotify.h"

#include "DealMsgHelper.h"

namespace PostMsgHelper
{
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
		//利用pInterface将数据发送出去
		DealMsgHelper::CDealMsgHelper *pDealMsg = reinterpret_cast<DealMsgHelper::CDealMsgHelper*>(pInterface);
		if (!pDealMsg->InvokeNotify(uMsgID, strData.data(), strData.size(), SerializeFormat))
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
		//利用pInterface将数据发送出去
		DealMsgHelper::CDealMsgHelper *pDealMsg = reinterpret_cast<DealMsgHelper::CDealMsgHelper*>(pInterface);
		if (!pDealMsg->InvokeNotify(uMsgID, nullptr, 0, EnumSerializeFormatNone))
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
		//利用pInterface将数据发送出去
		DealMsgHelper::CDealMsgHelper *pDealMsg = reinterpret_cast<DealMsgHelper::CDealMsgHelper*>(pInterface);
		if (!pDealMsg->InvokeQuery(uMsgID, strData.data(), strData.size(), SerializeFormat, strResult, pResult))
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
		//利用pInterface将数据发送出去
		DealMsgHelper::CDealMsgHelper *pDealMsg = reinterpret_cast<DealMsgHelper::CDealMsgHelper*>(pInterface);
		if (!pDealMsg->InvokeQuery(uMsgID, strData.data(), strData.size(), SerializeFormat, strResult, pResult))
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