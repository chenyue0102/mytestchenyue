// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�Serialization.h
// �������ڣ�2012-02-28
// �����ˣ��޿���
// �ļ�˵�������л���,�����ݶ�����д�뵽�ڴ�
// $_FILEHEADER_END ***********************************************************

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <string>
using namespace std;

// ���л�����
enum ENUM_SERIALIZATION_TYPE
{
	enum_Serialization_Type_Default,	// Ĭ��ֵ
	enum_Serialization_Type_Read,		// ��ȡ����
	enum_Serialization_Type_Write,		// д������
};

// ���洴������
enum ENUM_BUFFER_CREATE_TYPE
{
	enum_Buffer_Create_Type_Inside,		// �ڲ�����
	enum_Buffer_Create_Type_OutSide,	// �ⲿ����
};

class CSerialization
{
public:
	CSerialization();
	CSerialization(char* pBuffer, DWORD dwBufferLen);
	CSerialization(std::string &strBuffer);
	~CSerialization();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializationType
	// ����������iSerializationType		[����]	���л�����
	// �� �� ֵ��
	// ����˵�����������л�����
	// $_FUNCTION_END *********************************************************
	void SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializationType
	// ����������
	// �� �� ֵ�����л�����
	// ����˵������ȡ���л�����
	// $_FUNCTION_END *********************************************************
	ENUM_SERIALIZATION_TYPE GetSerializationType();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������byValue		[����]	�޷����ַ�
	// �� �� ֵ��
	// ����˵�������л��޷����ַ�
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned char& byValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������bValue		[����]	bool����
	// �� �� ֵ��
	// ����˵�������л�bool����
	// $_FUNCTION_END *********************************************************
	void Serialization(bool& bValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������sValue		[����]	�з��Ŷ�����
	// �� �� ֵ��
	// ����˵�������л��з��Ŷ�����
	// $_FUNCTION_END *********************************************************
	void Serialization(short& sValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������sValue		[����]	�޷��Ŷ�����
	// �� �� ֵ��
	// ����˵�������л��޷��Ŷ�����
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned short& sValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������iValue		[����]	�з�������
	// �� �� ֵ��
	// ����˵�������л��з�������
	// $_FUNCTION_END *********************************************************
	void Serialization(int& iValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������iValue		[����]	�޷�������
	// �� �� ֵ��
	// ����˵�������л��޷�������
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned int& iValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������lValue		[����]	�з��ų�����
	// �� �� ֵ��
	// ����˵�������л��з��ų�����
	// $_FUNCTION_END *********************************************************
	void Serialization(long& lValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������lValue		[����]	�޷��ų�����
	// �� �� ֵ��
	// ����˵�������л��޷��ų�����
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned long& lValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������i64Value		[����]	64λ������
	// �� �� ֵ��
	// ����˵�������л�64λ������
	// $_FUNCTION_END *********************************************************
	void Serialization(long long& i64Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������fValue		[����]	����������
	// �� �� ֵ��
	// ����˵�������л�����������
	// $_FUNCTION_END *********************************************************
	void Serialization(float& fValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������dValue		[����]	˫��������
	// �� �� ֵ��
	// ����˵�������л�˫��������
	// $_FUNCTION_END *********************************************************
	void Serialization(double& dValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������pValue			[����]	�ַ���
	//			 dwValueLen		[����]	�ַ�������
	//			 dwDataLen		[����]	���ݳ���
	// �� �� ֵ��
	// ����˵�������л��ַ���
	// $_FUNCTION_END *********************************************************
	void Serialization(char* pValue, DWORD dwValueLen, DWORD dwDataLen);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������strValue		[����]	�ַ���
	// �� �� ֵ��
	// ����˵�������л��ַ���
	// $_FUNCTION_END *********************************************************
	void Serialization(string& strValue);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetData
	// ����������
	// �� �� ֵ������
	// ����˵����ȡ������
	// $_FUNCTION_END *********************************************************
	char* GetData();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetDataLen
	// ����������
	// �� �� ֵ�����ݳ���
	// ����˵����ȡ�����ݳ���
	// $_FUNCTION_END *********************************************************
	DWORD GetDataLen();

	void ToBuffer(std::string &strBuffer);
private:
	// ���л�����
	ENUM_SERIALIZATION_TYPE	m_iSerializationType;

	// ���洴������
	ENUM_BUFFER_CREATE_TYPE	m_iBufferCreateType;

	// ����
	char*			m_pBuffer;

	// ���泤��
	DWORD			m_dwBufferLen;

	// ���ݳ���
	DWORD			m_dwDataLen;
	std::string			m_strBuffer;
};

#endif