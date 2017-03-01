// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：UnknownImp.h
// 创建日期：2015-09-10
// 创建人：陈月
// 文件说明：封装了Com的计数器类
// $_FILEHEADER_END ***********************************************************
#pragma once

template<typename T>
class CUnknownImp : public T
{
public:
	CUnknownImp():m_cRef(0)
	{
		
	}
	virtual ~CUnknownImp()
	{
		
	}
	//查询接口，不支持，
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject)
	{
		return E_NOTIMPL;
	}
	virtual ULONG STDMETHODCALLTYPE AddRef( void)
	{
		return InterlockedIncrement(&m_cRef);
	}
	virtual ULONG STDMETHODCALLTYPE Release( void)
	{
		ULONG nRet = InterlockedDecrement(&m_cRef);
		if (0 == nRet)
			delete this;

		return nRet;
	}
protected:
	volatile long	m_cRef;
};