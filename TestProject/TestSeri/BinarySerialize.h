// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�Serialize.h
// �������ڣ�2012-02-28
// �����ˣ��޿���
// �ļ�˵�������л���,�����ݶ�����д�뵽�ڴ�
// $_FILEHEADER_END ***********************************************************

#ifndef Serialize_H
#define Serialize_H

#include "Typedef.h"
#include <string>
#include <vector>
#include "ISerialize.h"

class CBinarySerialize
	: public ISerialize
{
	// ���洴������
	enum ENUM_BUFFER_CREATE_TYPE
	{
		enum_Buffer_Create_Type_Inside,		// �ڲ�����
		enum_Buffer_Create_Type_OutSide,	// �ⲿ����
	};
public:
	CBinarySerialize();
	~CBinarySerialize();
public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeType
	// ����������iSerializeType		[����]	���л�����
	// �� �� ֵ��
	// ����˵�����������л�����
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializeType(EnumSerializeIO iSerializeType)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializeType
	// ����������
	// �� �� ֵ�����л�����
	// ����˵������ȡ���л�����
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeIO GetSerializeType()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializeFormat
	// ����������
	// �� �� ֵ�����л��ĸ�ʽ
	// ����˵������ȡ���л��ĸ�ʽ
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeFormat GetSerializeFormat()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetData
	// ����������
	//					pstrText			[����]		������
	//					ulDataLength		[����]		����������
	// �� �� ֵ��true or false
	// ����˵����������Ҫ���л����Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, unsigned long ulDataLength)override;
public://���л��ֶκ���
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������bValue		[����]	bool����
	// �� �� ֵ��
	// ����˵�������л�bool����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(bool& bValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������cValue		[����]	�ַ�
	// �� �� ֵ��
	// ����˵�������л��޷����ַ�
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(char& cValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������byValue		[����]	�޷����ַ�
	// �� �� ֵ��
	// ����˵�������л��޷����ַ�
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned char& byValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������sValue		[����]	�з��Ŷ�����
	// �� �� ֵ��
	// ����˵�������л��з��Ŷ�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������sValue		[����]	�޷��Ŷ�����
	// �� �� ֵ��
	// ����˵�������л��޷��Ŷ�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������iValue		[����]	�з�������
	// �� �� ֵ��
	// ����˵�������л��з�������
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������iValue		[����]	�޷�������
	// �� �� ֵ��
	// ����˵�������л��޷�������
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������lValue		[����]	�з��ų�����
	// �� �� ֵ��
	// ����˵�������л��з��ų�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������lValue		[����]	�޷��ų�����
	// �� �� ֵ��
	// ����˵�������л��޷��ų�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������i64Value		[����]	64λ������
	// �� �� ֵ��
	// ����˵�������л�64λ������
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long long& i64Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long long& Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������fValue		[����]	����������
	// �� �� ֵ��
	// ����˵�������л�����������
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(float& fValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������dValue		[����]	˫��������
	// �� �� ֵ��
	// ����˵�������л�˫��������
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(double& dValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������dValue		[����]	˫��������
	// �� �� ֵ��
	// ����˵�������л�˫��������
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long double& ldValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������strValue		[����]	�ַ���
	// �� �� ֵ��
	// ����˵�������л��ַ���
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(std::string& strValue, const char *)override;

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
	// �������ƣ�BeginSerializeStruct
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���ṹ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeStruct
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ�Ľṹ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArray
	// ����������
	//					ulCount				[����/���]	�б�ĳ���
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���б�������/��ȡ�б�ĳ���
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArray(unsigned long &ulCount, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArray
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ���б��Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArray(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArrayItem
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л��б��еĵ�N��Ԫ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArrayItem(unsigned long, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArrayItem
	// ����������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬�б��еĵ�N��Ԫ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArrayItem(unsigned long, const char *)override;
private:
	//���ÿ��������븳ֵ
	CBinarySerialize(const CBinarySerialize &rhs);
	const CBinarySerialize& operator=(const CBinarySerialize &rhs);
private:
	// ���л�����
	EnumSerializeIO	m_iSerializeType;

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