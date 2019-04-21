#pragma once
#include <atomic>
#include <UnKnwn.h>

template<typename T>
class UnknownImp : public T
{
public:
	UnknownImp()
		: m_lRef(0)
	{

	}
	virtual ~UnknownImp()
	{

	}
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)override
	{
		return E_NOTIMPL;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef(void)override
	{
		return ++m_lRef;
	}

	virtual ULONG STDMETHODCALLTYPE Release(void)override
	{
		ULONG ret = --m_lRef;
		if (0 == ret)
		{
			delete this;
		}
		return ret;
	}
private:
	std::atomic_ulong m_lRef;
};