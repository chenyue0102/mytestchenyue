// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�JsonSerialize.h
// �������ڣ�2016-04-08
// �����ˣ�����
// �ļ�˵�������л���,�����ݶ�����д�뵽Json��Json�У��ַ�����ʽΪutf8
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <memory>
#include <stack>
#include "InterfaceSerialize.h"
#include "json.h"

namespace SerializeExport
{
	class CSerializeString;
}
using namespace SerializeExport;
/************************************************************************/
/* ���л���Json��ʽ��                                                     */
/************************************************************************/
class CJsonSerialize
	: public SerializeExport::ISerialize
{
public:
	CJsonSerialize();
	virtual ~CJsonSerialize();
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
	// �� �� ֵ��
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
	void CheckWriteToBuffer();
	void Log(const char* apFormat, ...);
	//���ַ���ת��Ϊutf8��ʽ
	std::string ConvertToJson(const std::string &strText);
	std::string ConvertToLocal(const std::string &strText);
private:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�ConverToType
	// ����������
	//					JsonValue			[����]		Json����
	//					Value				[���]		Json���󣬷����ָ����ʽ
	//					pstrName			[����]		�������ƣ���ӡ����Logʹ��
	// �� �� ֵ��true or false
	// ����˵����Json���󣬷����ָ����ʽ
	// $_FUNCTION_END *********************************************************
	bool ConverToType(Json::Value &JsonValue, CSerializeString &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, bool &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, int &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, unsigned int &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, long long &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, unsigned long long &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, double &Value, const char *pstrName);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�ConverToString
	// ����������
	//					Value				[����]		��Ҫ�洢��Json�е�����
	// �� �� ֵ��Json����
	// ����˵������ָ����ʽ�����ݣ�����ΪJson����
	// $_FUNCTION_END *********************************************************
	Json::Value ConverToJsonValue(CSerializeString &Value);
	Json::Value ConverToJsonValue(bool &Value);
	Json::Value ConverToJsonValue(int &Value);
	Json::Value ConverToJsonValue(unsigned int &Value);
	Json::Value ConverToJsonValue(long long &Value);
	Json::Value ConverToJsonValue(unsigned long long &Value);
	Json::Value ConverToJsonValue(double &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�InnerSerialize
	// ����������
	//					Value				[����/���]		��Ҫ���л���Ԫ��
	//					pstrName			[����]			Ԫ�ص�����
	// �� �� ֵ��
	// ����˵�������л�ָ����ʽ������
	// $_FUNCTION_END *********************************************************
	template<typename T>
	bool InnerSerialize(T &Value, const char *pstrName);
private:
	// ���л�����
	EnumSerializeIO	m_iSerializeType;
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
	//std::string�ַ�������
	EnumSerializeStringCode m_SerializeStringCode;
};
