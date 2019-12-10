#pragma once
#include <atomic>
#include "MyWindows.h"

template<typename T>
class CMyUnknownImpEx : public T
{
public:
	CMyUnknownImpEx()
	{}
	virtual ~CMyUnknownImpEx()
	{}
public:
	STDMETHOD(QueryInterface) (REFIID iid, void **outObject)override
	{
		if (iid == IID_IUnknown
			&& nullptr != outObject)
		{
			*outObject = static_cast<IUnknown*>(this);
			return S_OK;
		}
		else
		{
			return E_NOINTERFACE;
		}
	}
	STDMETHOD_(ULONG, AddRef)() override
	{
		return ++m_ref;
	}
	STDMETHOD_(ULONG, Release)() override
	{
		ULONG ret = --m_ref;
		if (0 == ret)
		{
			delete this;
		}
		return ret;
	}
protected:
	std::atomic<ULONG> m_ref;
};
