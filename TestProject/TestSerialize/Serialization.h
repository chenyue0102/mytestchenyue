// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�Serialization.h
// �������ڣ�2012-02-28
// �����ˣ��޿���
// �ļ�˵�������л���,�����ݶ�����д�뵽�ڴ�
// $_FILEHEADER_END ***********************************************************

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "Typedef.h"
#include <string>
#include <vector>
#include "ISerialize.h"
using namespace std;



// ���洴������
enum ENUM_BUFFER_CREATE_TYPE
{
	enum_Buffer_Create_Type_Inside,		// �ڲ�����
	enum_Buffer_Create_Type_OutSide,	// �ⲿ����
};

#define MAX_VECTOR_SIZE		(1024 * 1024)

class CSerialization
	: public ISerialize
{
public:
	CSerialization();
	//CSerialization(char* pBuffer, DWORD dwBufferLen);
	~CSerialization();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializationType
	// ����������iSerializationType		[����]	���л�����
	// �� �� ֵ��
	// ����˵�����������л�����
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializationType
	// ����������
	// �� �� ֵ�����л�����
	// ����˵������ȡ���л�����
	// $_FUNCTION_END *********************************************************
	virtual ENUM_SERIALIZATION_TYPE GetSerializationType()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetData
	// ����������
	//					pstrText			[����]		������
	//					ulDataLength		[����]		����������
	// �� �� ֵ��true or false
	// ����˵����������Ҫ���л����Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, unsigned long ulDataLength)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������byValue		[����]	�޷����ַ�
	// �� �� ֵ��
	// ����˵�������л��޷����ַ�
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned char& byValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������bValue		[����]	bool����
	// �� �� ֵ��
	// ����˵�������л�bool����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(bool& bValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������sValue		[����]	�з��Ŷ�����
	// �� �� ֵ��
	// ����˵�������л��з��Ŷ�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������sValue		[����]	�޷��Ŷ�����
	// �� �� ֵ��
	// ����˵�������л��޷��Ŷ�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������iValue		[����]	�з�������
	// �� �� ֵ��
	// ����˵�������л��з�������
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������iValue		[����]	�޷�������
	// �� �� ֵ��
	// ����˵�������л��޷�������
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������lValue		[����]	�з��ų�����
	// �� �� ֵ��
	// ����˵�������л��з��ų�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������lValue		[����]	�޷��ų�����
	// �� �� ֵ��
	// ����˵�������л��޷��ų�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������i64Value		[����]	64λ������
	// �� �� ֵ��
	// ����˵�������л�64λ������
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long long& i64Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long long& Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������fValue		[����]	����������
	// �� �� ֵ��
	// ����˵�������л�����������
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(float& fValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������dValue		[����]	˫��������
	// �� �� ֵ��
	// ����˵�������л�˫��������
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(double& dValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������pValue			[����]	�ַ���
	//			 dwValueLen		[����]	�ַ�������
	//			 dwDataLen		[����]	���ݳ���
	// �� �� ֵ��
	// ����˵�������л��ַ���
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(char* pValue, DWORD dwValueLen, DWORD dwDataLen);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������strValue		[����]	�ַ���
	// �� �� ֵ��
	// ����˵�������л��ַ���
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(string& strValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetData
	// ����������
	// �� �� ֵ������
	// ����˵����ȡ������
	// $_FUNCTION_END *********************************************************
	virtual const char* GetData()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetDataLen
	// ����������
	// �� �� ֵ�����ݳ���
	// ����˵����ȡ�����ݳ���
	// $_FUNCTION_END *********************************************************
	virtual DWORD GetDataLen()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeStruct
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���ṹ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeStruct
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ�Ľṹ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeArray
	// ����������
	//					ulCount				[����/���]	�б�ĳ���
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���б�������/��ȡ�б�ĳ���
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArray(unsigned long &ulCount, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArray
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ���б��Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArray(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeArrayItem
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л��б��еĵ�N��Ԫ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArrayItem(unsigned long, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArrayItem
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬�б��еĵ�N��Ԫ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArrayItem(unsigned long, const char *)override;
private:
	//���ÿ��������븳ֵ
	CSerialization(const CSerialization &rhs);
	const CSerialization& operator=(const CSerialization &rhs);
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
};

#endif