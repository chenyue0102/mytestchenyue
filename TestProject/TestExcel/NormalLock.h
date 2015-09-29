// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�NormalLock.h
// �������ڣ�2012-01-31
// �����ˣ��޿���
// �ļ�˵������ͨ������(windows�����ٽ���,linux���ǻ�����)
// $_FILEHEADER_END ***********************************************************

#ifndef NORMAL_LOCK_H
#define NORMAL_LOCK_H

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

class CNormalLock
{
public:
    CNormalLock();
    ~CNormalLock();

public:
    // $_FUNCTION_BEGIN *******************************************************
    // �������ƣ�Lock
    // ����������
    // �� �� ֵ��
    // ����˵��������
    // $_FUNCTION_END *********************************************************
    void Lock();

    // $_FUNCTION_BEGIN *******************************************************
    // �������ƣ�UnLock
    // ����������
    // �� �� ֵ��
    // ����˵��������
    // $_FUNCTION_END *********************************************************
    void UnLock();

private:
#ifdef WIN32
    // �ٽ���
    CRITICAL_SECTION    m_oCriticalSection;
#else
    // ��ʼ���������Ƿ�ɹ�
    bool                m_bMutex;
    
    // ������
    pthread_mutex_t        m_oMutex;
    
    // ��ʼ�������������Ƿ�ɹ�
    bool                m_bMutexAttr;
    
    // ����������
    pthread_mutexattr_t    m_oMutexAttr;
#endif
};

class CAutoLock
{
public:
    CAutoLock(CNormalLock& aNormalLock);
    ~CAutoLock();

private:
    // ��ͨ������
    CNormalLock& m_oNormalLock;
};

#endif