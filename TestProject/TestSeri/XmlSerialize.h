// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�JsonSerialize.h
// �������ڣ�2016-06-28
// �����ˣ�����
// �ļ�˵�������л���,�����ݶ�����д�뵽Xml���ַ�����ʽΪutf8
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <stack>
#include "tinyxml.h"
#include "ISerialize.h"

class CXmlSerialize
	: public ISerialize
{
public:
	CXmlSerialize();
	~CXmlSerialize();
public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeType
	// ����������
	//					iSerializeType	[����]		�������л���ʽ
	// �� �� ֵ��
	// ����˵�����������л���ʽ
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializeType(EnumSerializeIO iSerializeType)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetSerializeType
	// ����������
	// �� �� ֵ�����л���ʽ
	// ����˵������ȡ���л���ʽ
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
	// �������ƣ�BeginSerializeStruct
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���ṹ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeStruct(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeStruct
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ�Ľṹ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeStruct(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArray
	// ����������
	//					ulCount				[����/���]	�б�ĳ���
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���б�������/��ȡ�б�ĳ���
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArray(unsigned long &ulCount, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArray
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬��ǰ���б��Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArray(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬������Ҫ���л��б��еĵ�N��Ԫ��
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArrayItem(unsigned long ulIndex, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��
	// ����˵�����������л�ģ�飬�б��еĵ�N��Ԫ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArrayItem(unsigned long ulIndex, const char *pstrName)override;
public://���л��ֶκ���
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(bool& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ����������ʾ�ַ�
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������iValue		[����]	�з�������
	// �� �� ֵ��
	// ����˵�������л��з�������
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(int& iValue, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned int& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(float& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArrayItem
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�����ʽΪutf8
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(std::string& Value, const char *pstrName)override;
private:
	void Log(const char * apFormat, ...);
	int GetChildCount(TiXmlElement *pElement);
	void CheckWriteToBuffer();
private:
	// ���л�����
	EnumSerializeIO	m_iSerializeType;
	TiXmlDocument m_XmlDocument;
	TiXmlElement *m_pRootValue;
	TiXmlElement *m_pCurValue;
	std::stack<TiXmlElement*> m_StackValue;
	//���л����������
	std::string	m_strBuffer;
	//�Ƿ��Ѿ���������뻺�����ˡ�
	bool		m_bHaveWriteToBuffer;
};

