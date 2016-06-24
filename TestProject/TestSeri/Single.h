//******************************************************************
//              ���������Ȩ����
// Copyright (C) �˶Ȼ����з��� Corporation.  All Rights Reserved
// �ļ����ƣ�Single.h
// �������ڣ�2014-01-10
// ������  ���޿���
// �޸���  ������
// �ļ�˵��������ģ����			 
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

	//�ٽ���
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

