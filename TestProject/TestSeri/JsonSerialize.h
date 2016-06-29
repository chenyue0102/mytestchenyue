// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�JsonSerialize.h
// �������ڣ�2016-04-08
// �����ˣ�����
// �ļ�˵�������л���,�����ݶ�����д�뵽Json��Json�У��ַ�����ʽΪutf8
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <memory>
#include <stack>
#include "ISerialize.h"
#include "json.h"

/************************************************************************/
/* ���л���Json��ʽ��                                                     */
/************************************************************************/
class CJsonSerialize
	: public ISerialize
{
public:
	CJsonSerialize();
	virtual ~CJsonSerialize();
public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializationType
	// ����������
	//					iSerializationType	[����]		�������л���ʽ
	// �� �� ֵ��
	// ����˵�����������л���ʽ
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializationType
	// ����������
	// �� �� ֵ�����л���ʽ
	// ����˵������ȡ���л���ʽ
	// $_FUNCTION_END *********************************************************
	virtual ENUM_SERIALIZATION_TYPE GetSerializationType()override;

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
	//					pstrText			[����]		���������ַ�����ʽΪutf8
	//					ulDataLength		[����]		����������
	// �� �� ֵ��bool
	// ����˵����������Ҫ���л����Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, unsigned long ulDataLength)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetData
	// ����������
	// �� �� ֵ�����л����������ַ�����ʽΪutf8
	// ����˵������ȡ���л�������
	// $_FUNCTION_END *********************************************************
	virtual const char* GetData()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetDataLen
	// ����������
	// �� �� ֵ�����л�����������
	// ����˵������ȡ���л�����������
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetDataLen()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeStruct
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���ṹ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeStruct(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeStruct
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ�Ľṹ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeStruct(const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeArray
	// ����������
	//					ulCount				[����/���]	�б�ĳ���
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���б�������/��ȡ�б�ĳ���
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArray(unsigned long &ulCount, const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArray
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ���б��Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArray(const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerlizeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л��б��еĵ�N��Ԫ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArrayItem(unsigned long ulIndex, const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬�б��еĵ�N��Ԫ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArrayItem(unsigned long ulIndex, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(bool& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������iValue		[����]	�з�������
	// �� �� ֵ��
	// ����˵�������л��з�������
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(int& iValue, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned int& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(float& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialization
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerlizeArrayItem
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�����ʽΪutf8
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(std::string& Value, const char *pstrName)override;
private:
	void CheckWriteToBuffer();
	void Log(const char* apFormat, ...);
private:
	// ���л�����
	ENUM_SERIALIZATION_TYPE	m_iSerializationType;
	//Json���ڵ�
	std::shared_ptr<Json::Value> m_pRootValue;
	//Json��ǰ�Ľڵ�
	std::shared_ptr<Json::Value> m_pCurValue;
	//�ݹ��Ѿ���ջ�Ľڵ�
	std::stack<std::shared_ptr<Json::Value>> m_StackValue;
	//���л����������
	std::string	m_strBuffer;
	//�Ƿ��Ѿ���������뻺�����ˡ�
	bool		m_bHaveWriteToBuffer;
};