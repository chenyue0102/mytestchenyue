#pragma once
#include <functional>
#include "TKSerialize.h"
#include <map>

struct CInvokeNotifyBase
{
	virtual ~CInvokeNotifyBase()
	{

	};
	virtual void Notify(const void *pBuffer, unsigned long ulBytes) = 0;
};

template<typename ParamType>
struct CInvokeNotifyFun : public CInvokeNotifyBase
{
	CInvokeNotifyFun(std::function<void(const typename ParamType &)> fun)
		: m_callFun(fun)
	{

	}
	virtual void Notify(const void *pBuffer, unsigned long ulBytes)
	{
		do
		{
			std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
				pSerialize(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
			if (!pSerialize)
			{
				assert(false);
				break;
			}
			pSerialize->SetSerializeType(EnumSerializeIORead);
			pSerialize->SetData((const char*)pBuffer, ulBytes);
			ParamType t = ParamType();
			if (!SerializeStruct(pSerialize.get(), t))
			{
				assert(false);
				break;
			}
			m_callFun(t);
		} while (false);
	}
	std::function<void(const ParamType &)> m_callFun;
};

struct CInvokeQueryBase
{
	virtual ~CInvokeQueryBase()
	{

	};
	virtual void Query(const void *pBuffer, unsigned long ulBytes, std::string &strData, unsigned long *pResult) = 0;
};

template<typename InParamType, typename OutParamType>
struct CInvokeQueryFun : public CInvokeQueryBase
{
	CInvokeQueryFun(std::function<unsigned long(const typename InParamType &, typename OutParamType &)> fun)
		: m_callFun(fun)
	{

	}
	virtual void Query(const void *pBuffer, unsigned long ulBytes, std::string &strData, unsigned long *pResult)
	{
		do
		{
			std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
				pSerialize(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
			if (!pSerialize)
			{
				assert(false);
				break;
			}
			pSerialize->SetSerializeType(EnumSerializeIORead);
			pSerialize->SetData((const char*)pBuffer, ulBytes);
			InParamType in = InParamType();
			if (!SerializeStruct(pSerialize.get(), in))
			{
				assert(false);
				break;
			}
			OutParamType out = OutParamType();
			unsigned long ulRet = m_callFun(in, out);
			if (nullptr != pResult)
			{
				*pResult = ulRet;
			}
			std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
				pSerializeOut(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
			if (!pSerializeOut)
			{
				assert(false);
				break;
			}
			pSerializeOut->SetSerializeType(EnumSerializeIOWrite);
			if (!SerializeStruct(pSerializeOut.get(), out))
			{
				assert(false);
				break;
			}
			assert(strData.empty());
			strData.append(pSerializeOut->GetData(), pSerializeOut->GetDataLen());
		} while (false);
	}
	std::function<unsigned long(const InParamType &, OutParamType &)> m_callFun;
};


template<typename T>
class CInvokeHelper
{
public:
	CInvokeHelper(T *p)
		: m_pObject(p)
		, m_notifyCallbackFun()
		, m_queryCallbackFun()
	{
		assert(nullptr != m_pObject);
	}
	~CInvokeHelper()
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
public:
	bool InvokeNotify(unsigned long uMsg, const void *pBuffer, unsigned long ulBytes)
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
			pTemp->Notify(pBuffer, ulBytes);
			bRes = true;
		} while (false);

		return bRes;
	}

	template<typename ParmType>
	bool RegisterNotifyMsg(unsigned long ulMsgID, void (T::*callFun)(const ParmType &))
	{
		bool bRes = false;

		do
		{
			if (nullptr == m_pObject)
			{
				assert(false);
				break;
			}
			if (m_notifyCallbackFun.find(ulMsgID) != m_notifyCallbackFun.end())
			{
				assert(false);
				break;
			}
			T *pObject = m_pObject;
			std::function<void(const ParmType &)> warpFun =
				[pObject, callFun](const ParmType &pt)->void
			{
				return (pObject->*callFun)(pt);
			};
			CInvokeNotifyBase *pInvokeFun = new CInvokeNotifyFun<typename ParmType>(warpFun);
			auto res = m_notifyCallbackFun.insert(std::make_pair(ulMsgID, pInvokeFun));
			assert(res.second);
			bRes = true;
		} while (false);

		return bRes;
	}

	bool UnRegisterNotifyMsg(unsigned long ulMsgID)
	{
		auto itor = m_notifyCallbackFun.find(ulMsgID);
		if (itor != m_notifyCallbackFun.end())
		{
			CInvokeNotifyBase *pNotifyBase = itor->second;
			delete pNotifyBase;
			m_notifyCallbackFun.erase(itor);
			return true;
		}
		else
		{
			assert(false);
			return false;
		}
	}
public:
	bool InvokeQuery(unsigned long uMsg, const void *pBuffer, unsigned long ulBytes,
		std::string &strResultData, unsigned long *pInvokeResultCode)
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
			pTemp->Query(pBuffer, ulBytes, strResultData, pInvokeResultCode);
			bRes = true;
		} while (false);

		return bRes;
	}

	template<typename InParamType, typename OutParamType>
	bool RegisterQueryMsg(unsigned long ulMsgID, unsigned long (T::*callFun)(const InParamType &, OutParamType&))
	{
		bool bRes = false;

		do 
		{
			if (nullptr == m_pObject)
			{
				assert(false);
				break;
			}
			if (m_queryCallbackFun.find(ulMsgID) != m_queryCallbackFun.end())
			{
				assert(false);
				break;
			}
			T *pObject = m_pObject;
			std::function<unsigned long(const InParamType &, OutParamType&)> warpFun =
				[pObject, callFun](const InParamType &in, OutParamType &out)->unsigned long
			{
				return (pObject->*callFun)(in, out);
			};
			CInvokeQueryBase *pInvokeFun = new CInvokeQueryFun<typename InParamType, typename OutParamType>(warpFun);
			m_queryCallbackFun.insert(std::make_pair(ulMsgID, pInvokeFun));
			bRes = true;
		} while (false);

		return bRes;
	}

	bool UnRegisterQueryMsg(unsigned long ulMsgID)
	{
		auto itor = m_queryCallbackFun.find(ulMsgID);
		if (itor != m_queryCallbackFun.end())
		{
			CInvokeQueryBase *pNotifyBase = itor->second;
			delete pNotifyBase;
			m_queryCallbackFun.erase(itor);
			return true;
		}
		else
		{
			assert(false);
			return false;
		}
	}
private:
	T  *m_pObject;
	std::map<unsigned long, CInvokeNotifyBase*> m_notifyCallbackFun;
	std::map<unsigned long, CInvokeQueryBase*> m_queryCallbackFun;
};

