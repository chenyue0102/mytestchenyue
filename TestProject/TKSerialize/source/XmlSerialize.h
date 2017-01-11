// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�JsonSerialize.h
// �������ڣ�2016-06-28
// �����ˣ�����
// �ļ�˵�������л���,�����ݶ�����д�뵽Xml���ַ�����ʽΪutf8
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <stack>
#include "tinyxml.h"
#include "InterfaceSerialize.h"

namespace SerializeExport
{
	class CSerializeString;
}
using namespace SerializeExport;

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
	// �� �� ֵ��true or false
	// ����˵�����������л���ʽ
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeIO iSerializeType)override;

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
	// �� �� ֵ��
	// ����˵������ȡstd::string�ַ������룬
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeStringCode GetSerializeStringCode()override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetData
	// ����������
	//					pstrText			[����]		���������ַ�����ʽΪutf8
	//					ulDataLength		[����]		����������
	// �� �� ֵ��true or false
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
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���ṹ��
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeStruct(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeStruct
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬��ǰ�Ľṹ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeStruct(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArray
	// ����������
	//					ulCount				[����/���]	�б�ĳ���
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬������Ҫ���л�һ���б�������/��ȡ�б�ĳ���
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArray(unsigned long &ulCount, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArray
	// ����������
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬��ǰ���б��Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArray(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�BeginSerializeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬������Ҫ���л��б��еĵ�N��Ԫ��
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArrayItem(unsigned long ulIndex, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArrayItem
	// ����������
	//					ulIndex				[����]		��ǰҪ���л�Ԫ�����б��е�index
	//					pstrName			[����]		�˽ṹ������֣�nullptr��ʾû������
	// �� �� ֵ��true or false
	// ����˵�����������л�ģ�飬�б��еĵ�N��Ԫ���Ѿ����л����
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArrayItem(unsigned long ulIndex, const char *pstrName)override;
public://���л��ֶκ���
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ����������ʾ�ַ�
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������iValue		[����]	�з�������
	// �� �� ֵ��true or false
	// ����˵�������л��з�������
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int& iValue, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ���
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�EndSerializeArrayItem
	// ����������
	//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�����ʽΪutf8
	//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
	// �� �� ֵ��true or false
	// ����˵�������л�����
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(CSerializeString& Value, const char *pstrName)override;
private:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Log
	// ����������
	//					apFormat			[����]		��ӡ��־
	// �� �� ֵ��
	// ����˵������ӡ��־
	// $_FUNCTION_END *********************************************************
	void Log(const char * apFormat, ...);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetChildCount
	// ����������
	//					pElement			[����]		Ԫ��ָ��
	// �� �� ֵ��Ԫ�����ӽڵ�����
	// ����˵������ȡԪ�����ӽڵ�����
	// $_FUNCTION_END *********************************************************
	int GetChildCount(TiXmlElement *pElement);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�CheckWriteToBuffer
	// ����������
	// �� �� ֵ��
	// ����˵����ȷ�������л��Ľ��д�뵽����֮����
	// $_FUNCTION_END *********************************************************
	void CheckWriteToBuffer();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�ConverToXml
	// ����������
	//					strText				[����]		�����л�������
	// �� �� ֵ�����Է��õ�xml�ַ����е�����
	// ����˵�����������л�������ת���ɿ��Է��õ�xml�ַ����е����֣����m_SerializeStringCode��ת��
	// $_FUNCTION_END *********************************************************
	std::string ConverToXml(const std::string &strText);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�ConvertToLocal
	// ����������
	//					strText				[����]		xml����ȡ������
	// �� �� ֵ�����л�ǰ������
	// ����˵������xml����ȡ������ת�������л�ǰ�����ݣ����m_SerializeStringCode��ת��
	// $_FUNCTION_END *********************************************************
	std::string ConvertToLocal(const std::string &strText);
private:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�ConverToType
	// ����������
	//					pstrValue			[����]		xml�д洢������
	//					Value				[���]		xml�д洢�����ݣ������ָ����ʽ
	// �� �� ֵ��true or false
	// ����˵����xml�д洢�����ݣ������ָ����ʽ
	// $_FUNCTION_END *********************************************************
	bool ConverToType(const char *pstrValue, CSerializeString &Value);
	bool ConverToType(const char *pstrValue, bool &Value);
	bool ConverToType(const char *pstrValue, long long &Value);
	bool ConverToType(const char *pstrValue, unsigned long long &Value);
	bool ConverToType(const char *pstrValue, long double &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�ConverToString
	// ����������
	//					Value				[����]		��Ҫ�洢��xml�е�����
	// �� �� ֵ��xml�п��Դ洢������
	// ����˵������ָ����ʽ�����ݣ������xml�п��Դ洢������
	// $_FUNCTION_END *********************************************************
	std::string ConverToString(CSerializeString &Value);
	std::string ConverToString(bool &Value);
	std::string ConverToString(long long &Value);
	std::string ConverToString(unsigned long long &Value);
	std::string ConverToString(long double &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�InnerSerialize
	// ����������
	//					Value				[����/���]		��Ҫ���л���Ԫ��
	//					pstrName			[����]			Ԫ�ص�����
	// �� �� ֵ��true or false
	// ����˵�������л�ָ����ʽ������
	// $_FUNCTION_END *********************************************************
	template<typename T>
	bool InnerSerialize(T &Value, const char *pstrName);
private:
	// ���л����ͣ�����/���
	EnumSerializeIO	m_iSerializeType;
	// xml�ĵ�����
	TiXmlDocument m_XmlDocument;
	// xml���ڵ�
	TiXmlElement *m_pRootValue;
	// xml��ǰ�ڵ�
	TiXmlElement *m_pCurValue;
	// xml�����ӽڵ�󣬻Ὣ��ǰ�ڵ㱣�浽stack��
	std::stack<TiXmlElement*> m_StackValue;
	//���л����������
	std::string	m_strBuffer;
	//�Ƿ��Ѿ���������뻺�����ˡ�
	bool		m_bHaveWriteToBuffer;
	//std::string�ַ�������
	EnumSerializeStringCode m_SerializeStringCode;
};

