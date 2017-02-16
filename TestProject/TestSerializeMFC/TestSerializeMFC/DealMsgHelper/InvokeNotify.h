#pragma once
#include <string>
#include "EnumSerialize.h"

namespace DealMsgHelper
{
//序列化解包的模板函数
template<typename ParamType>
inline bool UnpackValue(const void *pBuffer, unsigned long ulBytes, ParamType &t, SerializeExport::EnumSerializeFormat SerializeFormat);

template<typename ParamType>
inline bool PackValue(const ParamType &t, std::string &strOutData, SerializeExport::EnumSerializeFormat SerializeFormat);

//处理通知消息的基类
struct CInvokeNotifyBase
{
	virtual ~CInvokeNotifyBase()
	{

	};
	virtual void Notify(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat) = 0;
};

//将缓冲区解包成指定结构体的模板类，回掉函数必须是 void(T::*INVOKEFUN)(const ParamType&);类型 
template<typename ClassType, typename ParamType>
struct CInvokeNotifyFun : public CInvokeNotifyBase
{
	typedef void(ClassType::*INVOKEFUN)(const ParamType&);
	inline CInvokeNotifyFun(ClassType *pObject, INVOKEFUN fun);
	virtual void Notify(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat)override;
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};

//无参数通知函数，回掉函数必须是void(ClassType::*INVOKEFUN)();类型
template<typename ClassType>
struct CInvokeNotifyEmptyFun : public CInvokeNotifyBase
{
	typedef void(ClassType::*INVOKEFUN)();
	inline CInvokeNotifyEmptyFun(ClassType *pObject, INVOKEFUN fun);
	inline void Notify(const void *, unsigned long, SerializeExport::EnumSerializeFormat);
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};

//处理查询消息的基类
struct CInvokeQueryBase
{
	virtual ~CInvokeQueryBase()
	{

	};
	virtual void Query(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
		std::string &strResultData, unsigned long *pResultErrorCode) = 0;
};

//查询模板类，函数参数必须为unsigned long (ClassType::*INVOKEFUN)(const InParamType&, OutParamType &);
template<typename ClassType, typename InParamType, typename OutParamType>
struct CInvokeQueryFun : public CInvokeQueryBase
{
	typedef unsigned long(ClassType::*INVOKEFUN)(const InParamType&, OutParamType &);
	inline CInvokeQueryFun(ClassType *pObject, INVOKEFUN fun);
	inline void Query(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
		std::string &strResultData, unsigned long *pResult);
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};

//查询模板类，参数必须是unsigned long (ClassType::*INVOKEFUN)(OutParamType &);
template<typename ClassType, typename OutParamType>
struct CInvokeQueryEmptyFun : public CInvokeQueryBase
{
	typedef unsigned long(ClassType::*INVOKEFUN)(OutParamType &);
	inline CInvokeQueryEmptyFun(ClassType *pObject, INVOKEFUN fun);
	inline void Query(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
		std::string &strResultData, unsigned long *pResult);
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};
};
#include "InvokeNotify.inl"