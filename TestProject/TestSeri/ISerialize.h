// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�ISerialize.h
// �������ڣ�2016-04-08
// �����ˣ�����
// �ļ�˵�������л��ӿڶ���
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <string>


#ifndef interface
#define interface struct
#endif
// ���л�����
enum ENUM_SERIALIZATION_TYPE
{
	enum_Serialization_Type_Default,	// Ĭ��ֵ
	enum_Serialization_Type_Read,		// ��ȡ����
	enum_Serialization_Type_Write,		// д������
};

/************************************************************************/
/* ���л��Ľӿڣ�ͳһ��������Json���л���ʽ                                  */
/************************************************************************/
interface ISerialize
{
public://���������ú���
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializationType
	// ����������
	//					iSerializationType	[����]		�������л���ʽ
	// �� �� ֵ��
	// ����˵�����������л���ʽ
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializationType
	// ����������
	// �� �� ֵ�����л���ʽ
	// ����˵������ȡ���л���ʽ
	// $_FUNCTION_END *********************************************************
	virtual ENUM_SERIALIZATION_TYPE GetSerializationType() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetData
	// ����������
	//					pstrText			[����]		������
	//					ulDataLength		[����]		����������
	// �� �� ֵ��true or false
	// ����˵����������Ҫ���л����Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, unsigned long ulDataLength) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetData
	// ����������
	// �� �� ֵ�����л�������
	// ����˵������ȡ���л�������
	// $_FUNCTION_END *********************************************************
	virtual const char* GetData() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetDataLen
	// ����������
	// �� �� ֵ�����л�����������
	// ����˵������ȡ���л�����������
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetDataLen() = 0;
public://���л��ṹ�����������ƺ���
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeStruct
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���ṹ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeStruct(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeStruct
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ�Ľṹ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeStruct(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeArray
	// ����������
	//					ulCount				[����/���]	�б�ĳ���
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���б�������/��ȡ�б�ĳ���
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArray(unsigned long &ulCount, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArray
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ���б��Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArray(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л��б��еĵ�N��Ԫ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArrayItem(unsigned long ulIndex, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬�б��еĵ�N��Ԫ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArrayItem(unsigned long ulIndex, const char *pstrName) = 0;
public://���л��ֶκ���
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned char& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(bool& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(short& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned short& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(int& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned int& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(float& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(double& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArrayItem
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(std::string& Value, const char *pstrName) = 0;
};



