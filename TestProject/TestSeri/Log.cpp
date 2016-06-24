#include <sys/timeb.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#ifdef    ANDROID    // Androidƽ̨
#include <android/log.h>
#endif
#include "Log.h"

// Log(unsigned int aiLogLevel, const char* apFormat, ...)��apFormat�Ļ�����󳤶�
#define DEF_FORMAT_MAX_LEN    3072
////////////////////////////////////////////////////////////
// CLog
CLog::CLog()
{
    m_iLogLevel = enum_Log_Level0;
    memset(m_szLogFileName, 0, sizeof(m_szLogFileName));
    m_iLogOption = enum_Log_Option_Timestamp | enum_Log_Option_PrintToConsole;

    memset(m_szLogBuff, 0 , sizeof(m_szLogBuff));
    m_iLogBuffLen = 0;
}

CLog::~CLog()
{
}

// ȡ��CLog����
CLog& CLog::GetInstance()
{
    static CLog oLog;
    return oLog;
}

// ������־�ȼ�
void CLog::SetLogLevel(unsigned int aiLogLevel)
{
    m_iLogLevel = aiLogLevel;
}

// ������־�ļ���
void CLog::SetLogFileName(char* apLogFileName, unsigned int aiLogFileNameLen)
{
    if (apLogFileName == NULL || aiLogFileNameLen == 0)
    {
        return;
    }

    // ���ȹ���
    if (aiLogFileNameLen >= DEF_LOG_FILENAME_LEN)
    {
        return;
    }

    memcpy(m_szLogFileName, apLogFileName, aiLogFileNameLen);
}

// ������־ѡ��
void CLog::SetLogOption(unsigned int aiLogOption)
{
    m_iLogOption = aiLogOption;
}

// ��¼��־
void CLog::Log(unsigned int aiLogLevel, const char* apFormat, ...)
{
    // ����������ַ���
    if (apFormat == NULL)
    {
        return;
    }

    // ���Ƕ��̵߳�����������Ҫ����
    CAutoLock oAutoLock(m_oLock);

    // ���ʱ���
    AddTimestamp();
    
    // �Ƿ��ӡ���ļ���
    bool bPrintToFile = false;

    // �����־����
    AddLogLevel(aiLogLevel, bPrintToFile);
    
    // ����ļ������к�
    AddFileNameAndLine();
    
    // �����־��¼
    va_list argptr;
    va_start(argptr, apFormat);
    AddLog(apFormat, argptr);
    va_end(argptr);
    
    // ��ӡ������̨/�ļ�
    PrintOut(bPrintToFile);
    
    memset(m_szLogBuff, 0, sizeof(m_szLogBuff));
    m_iLogBuffLen = 0;
}

// ���ʱ���
void CLog::AddTimestamp()
{
    if (m_iLogOption & enum_Log_Option_Timestamp) // ��ӡʱ���
    {
        struct timeb oTime;
        ftime(&oTime);

        struct tm* pLocalTime = localtime(&oTime.time);
        if (pLocalTime != NULL)
        {
            // ������д�뻺��
            char* pTemp = m_szLogBuff + m_iLogBuffLen;
            m_iLogBuffLen += sprintf(pTemp, "%02d:%02d:%02d:%03d ", pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec, oTime.millitm);
        }
    }
}

// �����־����
void CLog::AddLogLevel(unsigned int aiLogLevel, bool& abPrintToFile)
{
    if (m_iLogOption & enum_Log_Option_LogLevel)    // ��ӡ��־����
    {
        // ������д�뻺��
        char* pTemp = m_szLogBuff + m_iLogBuffLen;
        m_iLogBuffLen += sprintf(pTemp, "LogLevel:%u ", aiLogLevel);
    }

    if (m_iLogLevel < aiLogLevel)
    {
        abPrintToFile = true;
    }
}

// ����ļ������к�
void CLog::AddFileNameAndLine()
{
    if (m_iLogOption & enum_Log_Option_FilenameAndLine)    // ��ӡ�ļ������к�
    {
        // ������д�뻺��
        char* pTemp = m_szLogBuff + m_iLogBuffLen;
        m_iLogBuffLen += sprintf(pTemp, "%s(%d) ", __FILE__, __LINE__);
    }
}

// �����־��¼
void CLog::AddLog(const char* apFormat, va_list& argptr)
{
#ifndef WIN32
    // ��%I64d�滻��%lld
    const char* pPtr1 = apFormat;
    char szFormat[DEF_FORMAT_MAX_LEN] = {0};
    
    const char* pPtr2 = strstr(pPtr1, "%I64d");
    if (pPtr2 != NULL)
    {
        int iCopyLen = 0;
        while (pPtr2 != NULL)
        {
            memcpy(szFormat + iCopyLen, pPtr1, pPtr2 - pPtr1);
            iCopyLen += (pPtr2 - pPtr1);

            strcpy(szFormat + iCopyLen, "%lld");
            iCopyLen += strlen("%lld");

            pPtr1 = pPtr2 + strlen("%I64d");
            pPtr2 = strstr(pPtr1, "%I64d");
        }
        strcpy(szFormat + iCopyLen, pPtr1);
        pPtr1 = szFormat;
    }
    
    // ��szFormat׷�ӵ�m_szLogBuff��
    char* pTemp = m_szLogBuff + m_iLogBuffLen;
    m_iLogBuffLen += vsprintf(pTemp, pPtr1, argptr);
#else
    // ��szFormat׷�ӵ�m_szLogBuff��
    char* pTemp = m_szLogBuff + m_iLogBuffLen;
    m_iLogBuffLen += vsprintf(pTemp, apFormat, argptr);    
#endif
}

// ��ӡ������̨/�ļ�
void CLog::PrintOut(bool abPrintToFile)
{
    if (m_iLogOption & enum_Log_Option_PrintToConsole)    // ��ӡ������̨
    {
#ifdef    ANDROID    // Androidƽ̨
        __android_log_print(ANDROID_LOG_INFO, "Android Platform", "%s/n", m_szLogBuff);
#else
        printf("%s\n", m_szLogBuff);
#endif
    }
    
    if (m_iLogOption & enum_Log_Option_PrintToFile)    // ��ӡ���ļ�
    {
        if (abPrintToFile && strlen(m_szLogFileName) > 0)    // ���ļ���,�����пɴ�ӡ��־,���ӡ���ļ�
        {
            FILE* pFile = NULL;
            pFile = fopen(m_szLogFileName, "a");
            if (pFile != NULL)
            {
                fprintf(pFile, "%s\n", m_szLogBuff);
                fclose(pFile);
            }
        }
    }
}