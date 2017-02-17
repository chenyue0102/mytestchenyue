#pragma once
#include <string>
#include "EnumSerialize.h"

namespace DealMsgHelper
{
//���л������ģ�庯��
template<typename ParamType>
inline bool UnpackValue(const void *pBuffer, unsigned long ulBytes, ParamType &t, SerializeExport::EnumSerializeFormat SerializeFormat);

template<typename ParamType>
inline bool PackValue(const ParamType &t, std::string &strOutData, SerializeExport::EnumSerializeFormat SerializeFormat);

//����֪ͨ��Ϣ�Ļ���
struct CInvokeNotifyBase
{
	virtual ~CInvokeNotifyBase()
	{

	};
	virtual bool Notify(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat) = 0;
};

//�������������ָ���ṹ���ģ���࣬�ص����������� void(T::*INVOKEFUN)(const ParamType&);���� 
template<typename ClassType, typename ParamType>
struct CInvokeNotifyFun : public CInvokeNotifyBase
{
	typedef void(ClassType::*INVOKEFUN)(const ParamType&);
	inline CInvokeNotifyFun(ClassType *pObject, INVOKEFUN fun);
	virtual bool Notify(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat)override;
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};

//�޲���֪ͨ�������ص�����������void(ClassType::*INVOKEFUN)();����
template<typename ClassType>
struct CInvokeNotifyEmptyFun : public CInvokeNotifyBase
{
	typedef void(ClassType::*INVOKEFUN)();
	inline CInvokeNotifyEmptyFun(ClassType *pObject, INVOKEFUN fun);
	inline bool Notify(const void *, unsigned long, SerializeExport::EnumSerializeFormat);
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};

//�����ѯ��Ϣ�Ļ���
struct CInvokeQueryBase
{
	virtual ~CInvokeQueryBase()
	{

	};
	virtual bool Query(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
		std::string &strResultData, unsigned long *pResultErrorCode) = 0;
};

//��ѯģ���࣬������������Ϊunsigned long (ClassType::*INVOKEFUN)(const InParamType&, OutParamType &);
template<typename ClassType, typename InParamType, typename OutParamType>
struct CInvokeQueryFun : public CInvokeQueryBase
{
	typedef unsigned long(ClassType::*INVOKEFUN)(const InParamType&, OutParamType &);
	inline CInvokeQueryFun(ClassType *pObject, INVOKEFUN fun);
	inline bool Query(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
		std::string &strResultData, unsigned long *pResult);
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};

//��ѯģ���࣬����������unsigned long (ClassType::*INVOKEFUN)(InOutParamType &);
template<typename ClassType, typename InOutParamType>
struct CInvokeQueryInOutFun : public CInvokeQueryBase
{
	typedef unsigned long(ClassType::*INVOKEFUN)(InOutParamType &);
	inline CInvokeQueryInOutFun(ClassType *pObject, INVOKEFUN fun);
	inline bool Query(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
		std::string &strResultData, unsigned long *pResult);
	ClassType *m_pObject;
	INVOKEFUN m_callFun;
};
};
#include "InvokeNotify.inl"