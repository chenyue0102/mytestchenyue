//******************************************************************
//              竞技世界版权所有
// Copyright (C) 八度互联研发部 Corporation.  All Rights Reserved
// 文件名称：Single.h
// 创建日期：2014-01-10
// 创建人  ：罗俊杰
// 修改人  ：刘崇
// 文件说明：单件模板类			 
//*******************************************************************
#pragma once

#include "NormalLock.h"

template< typename T >
class CSingle
{
public:
	static T& Instance();
    static void DestroySingleton();

private:
	static void MakeInstance();
	

	static T* m_pInstance;

private:
	CSingle();
	CSingle(const CSingle&);

	//临界区
	static CNormalLock  m_oCriSection;
};

template<class T> CNormalLock CSingle<T>::m_oCriSection;
template<class T> T* CSingle<T>::m_pInstance = 0;

template <class T> 
T& CSingle<T>::Instance()
{
	if ( !m_pInstance)
	{
		MakeInstance();
	}

	return *m_pInstance;
}

template <class T>
inline void CSingle<T>::MakeInstance()
{
	CAutoLock loGuard(m_oCriSection);

	if(!m_pInstance)
	{
		m_pInstance = new T;
		::atexit(DestroySingleton);
	}
}

template <class T>
void CSingle<T>::DestroySingleton()
{
    if (0 != m_pInstance)
    {
        CAutoLock loGuard(m_oCriSection);
        if (0 != m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = 0;
        }
    }   
}

