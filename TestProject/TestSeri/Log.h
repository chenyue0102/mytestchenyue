// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�Log.h
// �������ڣ�2012-07-06
// �����ˣ��޿���
// �ļ�˵������־��
// $_FILEHEADER_END ***********************************************************

#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include "NormalLock.h"

// ��־�ļ�������
#define DEF_LOG_FILENAME_LEN    512

// ��־��¼�Ļ��泤��
#define DEF_LOG_BUFF_LEN        4096

// ��־����,�ӵ͵��߷�Ϊ0����5��,0�����,5�����,��־Ĭ��Ϊ0��
enum ENUM_LOG_LEVEL
{
    enum_Log_Level0,    // 0��
    enum_Log_Level1,    // 1��
    enum_Log_Level2,    // 2��
    enum_Log_Level3,    // 3��
    enum_Log_Level4,    // 4��
    enum_Log_Level5,    // 5��
};

// ��־ѡ��
enum ENUM_LOG_OPTION
{
    enum_Log_Option_Timestamp = 1,            // ��ӡʱ���
    enum_Log_Option_LogLevel = 2,            // ��ӡ��־����
    enum_Log_Option_FilenameAndLine = 4,    // ��ӡ�ļ������к�
    enum_Log_Option_PrintToFile = 8,        // ��ӡ���ļ�
    enum_Log_Option_PrintToConsole = 16,    // ��ӡ������̨
};

class CLog
{
public:
    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�GetInstance
    // ����������
    // �� �� ֵ��CLog����
    // ����˵����ȡ��CLog����
    // $_FUNCTION_END ****************************************************
    static CLog& GetInstance();

    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�SetLogLevel
    // ����������aiLogLevel            [����]    ��־�ȼ�
    // �� �� ֵ��
    // ����˵����������־�ȼ�
    // $_FUNCTION_END ****************************************************
    void SetLogLevel(unsigned int aiLogLevel);

    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�SetLogFileName
    // ����������apLogFileName        [����]    ��־�ļ���
    //             aiLogFileNameLen    [����]    ��־�ļ�������
    // �� �� ֵ��
    // ����˵����������־�ļ���
    // $_FUNCTION_END ****************************************************
    void SetLogFileName(char* apLogFileName, unsigned int aiLogFileNameLen);

    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�SetLogOption
    // ����������aiLogOption        [����]    ��־ѡ��
    // �� �� ֵ��
    // ����˵����������־ѡ��
    // $_FUNCTION_END ****************************************************
    void SetLogOption(unsigned int aiLogOption);

    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�Log
    // ����������aiLogLevel            [����]    ÿ����־��¼����־�ȼ�,��������־�ȼ�����SetLogLevel���õĵȼ�,������ӡ���ļ���,�����Դ�ӡ������̨
    //             apFormat            [����]    ��־��¼�ĸ�ʽ���ַ���
    //             ...                [����]    ��־��¼��ʽ������
    // �� �� ֵ��
    // ����˵������¼��־
    // $_FUNCTION_END ****************************************************
    void Log(unsigned int aiLogLevel, const char* apFormat, ...);

private:
    CLog();
    CLog(const CLog& aLog);
    ~CLog();
    CLog& operator ==(const CLog& aLog);
    
private:
    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�AddTimestamp
    // ����������
    // �� �� ֵ��
    // ����˵�������ʱ���
    // $_FUNCTION_END ****************************************************
    void AddTimestamp();
    
    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�AddLogLevel
    // ����������aiLogLevel            [����]    ÿ����־��¼����־�ȼ�
    //            abPrintToFile        [����]    �Ƿ��ӡ���ļ�
    // �� �� ֵ��
    // ����˵���������־����
    // $_FUNCTION_END ****************************************************
    void AddLogLevel(unsigned int aiLogLevel, bool& abPrintToFile);
    
    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�AddFileNameAndLine
    // ����������
    // �� �� ֵ��
    // ����˵��������ļ������к�
    // $_FUNCTION_END ****************************************************
    void AddFileNameAndLine();
    
    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�AddLog
    // ����������apFormat            [����]    ��־��¼�ĸ�ʽ���ַ���
    //             argptr                [����]    ��־��¼��ʽ������
    // �� �� ֵ��
    // ����˵���������־��¼
    // $_FUNCTION_END ****************************************************
    void AddLog(const char* apFormat, va_list& argptr);
    
    // $_FUNCTION_BEGIN **************************************************
    // �������ƣ�PrintOut
    // ����������abPrintToFile        [����]    �Ƿ��ӡ���ļ�
    // �� �� ֵ��
    // ����˵������ӡ������̨/�ļ�
    // $_FUNCTION_END ****************************************************
    void PrintOut(bool abPrintToFile);

private:
    // ��־�ȼ�
    unsigned int    m_iLogLevel;

    // ��־�ļ���
    char            m_szLogFileName[DEF_LOG_FILENAME_LEN];

    // ��־ѡ��(��ӦENUM_LOG_OPTION,��ͨ�����������Ӷ��ѡ��)
    unsigned int    m_iLogOption;

    // һ����־��¼�Ļ���
    char            m_szLogBuff[DEF_LOG_BUFF_LEN];

    // һ����־��¼�����ʵ�ʳ���
    unsigned int    m_iLogBuffLen;

    // ��
    CNormalLock        m_oLock;
};

#endif