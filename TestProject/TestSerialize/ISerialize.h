#pragma once
#include <string>
#include "EnumSerialize.h"
#include <unknwn.h>

#ifndef interface
#define interface struct
#endif


interface ISerializeStream : public IUnknown
{
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializeType
	// ����������
	// �� �� ֵ����ǰ���л�����Ӧ�����ͣ�����ö��EnumSerializeType
	// ����˵������ȡ��ǰ���л�����Ӧ������
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeType GetSerializeType() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeType
	// ����������
	//			 SerializeType		[����]	���л�����
	// �� �� ֵ��true or false
	// ����˵�������õ�ǰ���л�����Ӧ������
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeType SerializeType) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeReadBuffer
	// ����������
	//			 pBuffer			[����]	������
	//			 ulBufferLength		[����]	����������
	// �� �� ֵ��true or false
	// ����˵�����������л���ȡ�Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeReadBuffer(const void *pBuffer, unsigned long ulBufferLength) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetWriteBuffer
	// ����������
	// �� �� ֵ����������ַ
	// ����˵������ȡд���л�������
	// $_FUNCTION_END *********************************************************
	virtual const void * GetWriteBuffer() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetWriteBufferLength
	// ����������
	// �� �� ֵ������������
	// ����˵������ȡд���л�����������
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetWriteBufferLength() = 0;
};

interface ISerialize : public ISerializeStream
{
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�bool
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�float
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�double
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 pBuffer			[����/���]	�����л��Ļ�����
	//			 ulBufferLen		[����/���]	�����л��Ļ���������
	// �� �� ֵ��true or false
	// ����˵�������л�������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(void *pBuffer, unsigned long ulBufferLen) = 0;
};