// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�Serialize.h
// �������ڣ�2012-02-28
// �����ˣ��޿���
// �ļ�˵�������л���,�����ݶ�����д�뵽�ڴ�
// $_FILEHEADER_END ***********************************************************

#ifndef Serialize_H
#define Serialize_H

#include <string>
#include <vector>
#include "InterfaceSerialize.h"

namespace SerializeExport
{
	class CSerializeString;
}

using namespace SerializeExport;
class CBinarySerialize
	: public SerializeExport::IAssistorSerialize
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
	// �� �� ֵ��true or false
	// ����˵�����������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeIO iSerializeType)override;

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
	// �������ƣ�SetSerializeStringCode
	// ����������
	//					SerializeStringCode	[����]		����std::string�ַ������룬Ĭ����EnumSerializeStringCodeNone
	// �� �� ֵ��true or false
	// ����˵��������std::string�ַ������룬
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeStringCode(EnumSerializeStringCode SerializeStringCode)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializeStringCode
	// ����������
	// �� �� ֵ����ǰ�ַ�������
	// ����˵������ȡstd::string�ַ������룬
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeStringCode GetSerializeStringCode()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetData
	// ����������
	//					pstrText			[����]		������
	//					ulDataLength		[����]		����������
	// �� �� ֵ��true or false
	// ����˵����������Ҫ���л����Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, suint32 ulDataLength)override;
public://���л��ֶκ���
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������bValue		[����]	bool����
	// �� �� ֵ��true or false
	// ����˵�������л�bool����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool& bValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������cValue		[����]	�ַ�
	// �� �� ֵ��true or false
	// ����˵�������л��޷����ַ�
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char& cValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������byValue		[����]	�޷����ַ�
	// �� �� ֵ��true or false
	// ����˵�������л��޷����ַ�
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char& byValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������sValue		[����]	�з��Ŷ�����
	// �� �� ֵ��true or false
	// ����˵�������л��з��Ŷ�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������sValue		[����]	�޷��Ŷ�����
	// �� �� ֵ��true or false
	// ����˵�������л��޷��Ŷ�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������iValue		[����]	�з�������
	// �� �� ֵ��true or false
	// ����˵�������л��з�������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������iValue		[����]	�޷�������
	// �� �� ֵ��true or false
	// ����˵�������л��޷�������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������lValue		[����]	�з��ų�����
	// �� �� ֵ��true or false
	// ����˵�������л��з��ų�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������lValue		[����]	�޷��ų�����
	// �� �� ֵ��true or false
	// ����˵�������л��޷��ų�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������i64Value		[����]	64λ������
	// �� �� ֵ��true or false
	// ����˵�������л�64λ������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long& i64Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long& Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������fValue		[����]	����������
	// �� �� ֵ��true or false
	// ����˵�������л�����������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float& fValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������dValue		[����]	˫��������
	// �� �� ֵ��true or false
	// ����˵�������л�˫��������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double& dValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������dValue		[����]	˫��������
	// �� �� ֵ��true or false
	// ����˵�������л�˫��������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long double& ldValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������strValue		[����]	�ַ���
	// �� �� ֵ��true or false
	// ����˵�������л��ַ���
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(CSerializeString& strValue, const char *)override;

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
	virtual suint32 GetDataLen()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeStruct
	// ����������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���ṹ��
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeStruct
	// ����������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬��ǰ�Ľṹ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArray
	// ����������
	//					ulCount				[����/���]	�б�ĳ���
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���б�������/��ȡ�б�ĳ���
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArray(suint32 &ulCount, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArray
	// ����������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬��ǰ���б��Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArray(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArrayItem
	// ����������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬������Ҫ���л��б��еĵ�N��Ԫ��
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArrayItem(suint32, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArrayItem
	// ����������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬�б��еĵ�N��Ԫ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArrayItem(suint32, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�AssistorSerialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					ulDataLength		[����]		����������
	// �� �� ֵ��true or false
	// ����˵�����ӻ������У���ȡ/д��ulDataLength����
	// $_FUNCTION_END *********************************************************
	virtual bool AssistorSerialize(char *Value, suint32 ulDataLength);
private:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�InnerSerialize
	// ����������
	//					Value				[����/���]		��Ҫ���л���Ԫ��
	// �� �� ֵ��true or false
	// ����˵�������л�ָ����ʽ������
	// $_FUNCTION_END *********************************************************
	template<typename T>
	bool InnerSerialize(T &Value);
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
	suint32			m_dwBufferLen;

	// ���ݳ���
	suint32			m_dwDataLen;

	//std::string�ַ�������
	EnumSerializeStringCode m_SerializeStringCode;
};

#endif