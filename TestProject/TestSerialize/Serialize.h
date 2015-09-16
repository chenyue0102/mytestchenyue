#pragma once
#include "EnumSerialize.h"
#include "ISerialize.h"
#include <sstream>
#include "UnknownImp.h"

class CSerialize
	: public CUnknownImp<ISerialize>
{
public:
	CSerialize(void);
	~CSerialize(void);
public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializeType
	// ����������
	// �� �� ֵ����ǰ���л�����Ӧ�����ͣ�����ö��EnumSerializeType
	// ����˵������ȡ��ǰ���л�����Ӧ������
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeType GetSerializeType();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeType
	// ����������
	//			 SerializeType		[����]	���л�����
	// �� �� ֵ��true or false
	// ����˵�������õ�ǰ���л�����Ӧ������
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeType SerializeType);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeReadBuffer
	// ����������
	//			 pBuffer			[����]	������
	//			 ulBufferLength		[����]	����������
	// �� �� ֵ��true or false
	// ����˵�����������л���ȡ�Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeReadBuffer(const void *pBuffer, unsigned long ulBufferLength);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetWriteBuffer
	// ����������
	// �� �� ֵ����������ַ
	// ����˵������ȡд���л�������
	// $_FUNCTION_END *********************************************************
	virtual const void * GetWriteBuffer();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetWriteBufferLength
	// ����������
	// �� �� ֵ������������
	// ����˵������ȡд���л�����������
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetWriteBufferLength();
public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�bool
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�float
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�double
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 pBuffer			[����/���]	�����л��Ļ�����
	//			 ulBufferLen		[����/���]	�����л��Ļ���������
	// �� �� ֵ��true or false
	// ����˵�������л�������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(void *pBuffer, unsigned long ulBufferLen);
private:
	bool SerializeRead(void *pBuffer, unsigned long ulBufferLen);
	bool SerializeWrite(const void *pBuffer, unsigned long ulBufferLen);
private:
	EnumSerializeType	m_EnumSerializeType;
	
	const void			*m_pReadBuffer;
	unsigned long		m_ulReadBufferLength;
	unsigned long		m_ulReadBufferOffset;

	void				*m_pWriteBuffer;
	unsigned long		m_ulWriteBufferLength;
	unsigned long		m_ulWriteBufferOffset;
};
