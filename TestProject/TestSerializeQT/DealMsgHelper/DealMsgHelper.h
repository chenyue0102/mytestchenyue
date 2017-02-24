#pragma once
#include <map>
#include "InvokeNotify.h"
#include "EnumSerialize.h"

namespace DealMsgHelper
{
class CDealMsgHelper
{
public:
	inline CDealMsgHelper();
	inline ~CDealMsgHelper();
public:
	inline bool InvokeNotify(
		unsigned long uMsg, 
		const void *pBuffer, 
		unsigned long ulBytes, 
		SerializeExport::EnumSerializeFormat SerializeFormat);

	inline bool InvokeQuery(
		unsigned long uMsg, 
		const void *pBuffer, 
		unsigned long ulBytes, 
		SerializeExport::EnumSerializeFormat SerializeFormat,
		std::string &strData, 
		unsigned long *pResult);
public:
	//带参数的函数
	template<typename ClassType, typename ParamType>
	bool RegMsg(unsigned long ulMsgID, ClassType *pObject, void (ClassType::*callFun)(const ParamType &));

	//没有参数的函数
	template<typename ClassType>
	bool RegMsg(unsigned long ulMsgID, ClassType *pObject, void (ClassType::*callFun)());

	//输入，输出获取
	template<typename ClassType, typename InParamType, typename OutParamType>
	bool RegMsg(unsigned long ulMsgID, ClassType *pObject, unsigned long (ClassType::*callFun)(const InParamType&, OutParamType &));

	//输出获取
	template<typename ClassType, typename InOutParamType>
	bool RegMsg(unsigned long ulMsgID, ClassType *pObject, unsigned long (ClassType::*callFun)(InOutParamType &));
protected:
	std::map<unsigned long, CInvokeNotifyBase*> m_notifyCallbackFun;
	std::map<unsigned long, CInvokeQueryBase*> m_queryCallbackFun;
};
};
#include "DealMsgHelper.inl"