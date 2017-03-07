#include "InvokeNotify.h"
#include <assert.h>
#include <memory>
#include "SerializeHelper.h"
#include "TKSerializeExport.h"

namespace DealMsgHelper
{
//序列化解包的模板函数
template<typename ParamType>
inline bool UnpackValue(const void *pBuffer, unsigned long ulBytes, ParamType &t, SerializeExport::EnumSerializeFormat SerializeFormat)
{
	bool bRes = false;

	do
	{
		if (nullptr == pBuffer || 0 == ulBytes)
		{
			assert(false);
			break;
		}
		if (EnumSerializeFormatNone == SerializeFormat)
		{
			assert(false);
			break;
		}
		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerializeRead(SerializeExport::CreateSerializeInterface(SerializeFormat), 
							&SerializeExport::DestroySerializeInterface);
		if (!pSerializeRead)
		{
			assert(false);
			break;
		}
		pSerializeRead->SetSerializeType(EnumSerializeIORead);
		pSerializeRead->SetData(reinterpret_cast<const char*>(pBuffer), ulBytes);
		if (!SerializeStruct(*pSerializeRead, t))
		{
			assert(false);
			break;
		}

		bRes = true;
	} while (false);
	return bRes;
}

template<typename ParamType>
inline bool PackValue(const ParamType &t, std::string &strOutData, SerializeExport::EnumSerializeFormat SerializeFormat)
{
	bool bRes = false;

	do
	{
		if (EnumSerializeFormatNone == SerializeFormat)
		{
			assert(false);
			break;
		}
		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerializeWrite(SerializeExport::CreateSerializeInterface(SerializeFormat), 
			&SerializeExport::DestroySerializeInterface);
		if (!pSerializeWrite)
		{
			assert(false);
			break;
		}
		pSerializeWrite->SetSerializeType(EnumSerializeIOWrite);
		ParamType &temp = const_cast<ParamType&>(t);
		if (!SerializeStruct(*pSerializeWrite, temp))
		{
			assert(false);
			break;
		}
		strOutData.append(pSerializeWrite->GetData(), pSerializeWrite->GetDataLen());

		bRes = true;
	} while (false);
	return bRes;
}

//将缓冲区解包成指定结构体的模板类
template<typename ClassType, typename ParamType>
inline DealMsgHelper::CInvokeNotifyFun<ClassType, ParamType>::CInvokeNotifyFun(ClassType *pObject, INVOKEFUN fun)
	: m_pObject(pObject)
	, m_callFun(fun)
{
	assert(nullptr != m_callFun);
	assert(nullptr != m_pObject);
}

template<typename ClassType, typename ParamType>
inline bool DealMsgHelper::CInvokeNotifyFun<ClassType, ParamType>::Notify(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat)
{
	bool bRes = false;
	do
	{
		ParamType pt = ParamType();
		if (!UnpackValue(pBuffer, ulBytes, pt, SerializeFormat))
		{
			assert(false);
			break;
		}
		if (nullptr == m_pObject || nullptr == m_callFun)
		{
			assert(false);
			break;
		}
		(m_pObject->*m_callFun)(pt);
		bRes = true;
	} while (false);
	return bRes;
}

template<typename ClassType>
inline CInvokeNotifyEmptyFun<ClassType>::CInvokeNotifyEmptyFun(ClassType *pObject, INVOKEFUN fun)
	: m_pObject(pObject)
	, m_callFun(fun)
{
	assert(nullptr != m_callFun);
	assert(nullptr != m_pObject);
}

template<typename ClassType>
inline bool CInvokeNotifyEmptyFun<ClassType>::Notify(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat)
{
	assert(nullptr == pBuffer && 0 == ulBytes);
	if (nullptr != m_pObject && nullptr != m_callFun)
	{
		(m_pObject->*m_callFun)();
		return true;
	}
	else
	{
		assert(false);
		return false;
	}
}

template<typename ClassType, typename InParamType, typename OutParamType>
inline CInvokeQueryFun<ClassType, InParamType, OutParamType>::CInvokeQueryFun(ClassType *pObject, INVOKEFUN fun)
	: m_pObject(pObject)
	, m_callFun(fun)
{
	assert(nullptr != m_callFun);
	assert(nullptr != m_pObject);
}

template<typename ClassType, typename InParamType, typename OutParamType>
inline bool CInvokeQueryFun<ClassType, InParamType, OutParamType>::Query(
	const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
	std::string &strResultData, unsigned long *pResult)
{
	bool bRes = false;
	do
	{
		if (nullptr == pBuffer || 0 == ulBytes)
		{
			assert(false);
			break;
		}

		InParamType in = InParamType();
		if (!UnpackValue(pBuffer, ulBytes, in, SerializeFormat))
		{
			assert(false);
			break;
		}
		if (nullptr == m_pObject || nullptr == m_callFun)
		{
			assert(false);
			break;
		}
		OutParamType out = OutParamType();
		unsigned long ulRet = (m_pObject->*m_callFun)(in, out);
		if (nullptr != pResult)
		{
			*pResult = ulRet;
		}
		if (!PackValue(out, strResultData, SerializeFormat))
		{
			assert(false);
			break;
		}
		bRes = true;
	} while (false);
	return bRes;
}

template<typename ClassType, typename InOutParamType>
inline CInvokeQueryInOutFun<ClassType, InOutParamType>::CInvokeQueryInOutFun(ClassType *pObject, INVOKEFUN fun)
	: m_pObject(pObject)
	, m_callFun(fun)
{
	assert(nullptr != m_callFun);
	assert(nullptr != m_pObject);
}

template<typename ClassType, typename InOutParamType>
inline bool CInvokeQueryInOutFun<ClassType, InOutParamType>::Query(const void *pBuffer, unsigned long ulBytes, SerializeExport::EnumSerializeFormat SerializeFormat, 
	std::string &strResultData, unsigned long *pResult)
{
	bool bRes = false;
	do 
	{
		if (nullptr == m_pObject || nullptr == m_callFun)
		{
			assert(false);
			break;
		}
		InOutParamType out = InOutParamType();
		//如果pBuffer与ulBytes为空，则认为没有参数的获取
		if (nullptr != pBuffer && 0 != ulBytes)
		{
			if (!UnpackValue(pBuffer, ulBytes, out, SerializeFormat))
			{
				assert(false);
				break;
			}
		}
		unsigned long ulRet = (m_pObject->*m_callFun)(out);
		if (nullptr != pResult)
		{
			*pResult = ulRet;
		}
		if (!PackValue(out, strResultData, SerializeFormat))
		{
			assert(false);
			break;
		}
		bRes = true;
	} while (false);
	return bRes;
}
}