// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�SerializeHelper.h
// �������ڣ�2016-04-08
// �����ˣ�����
// �ļ�˵�������л������࣬����ʹ�����л��������ͣ��ṹ�����ͣ�vector���鷽ʽһ��
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <vector>
#include "EnumSerialize.h"

namespace SerializeExport
{
	class CSerializeString;
	struct ISerialize;
}
using namespace  SerializeExport;
/************************************************************************/
/* ���л��� Serialize                                                */
/************************************************************************/
//���л������ַ���������ĺ궨��
#define SERIALIZE_STRUCT_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, value, #value); 

//���л��ַ�������궨��
#define SERIALIZE_STRUCT_CHAR_ARRAY(value) \
                SerializeHelper::SerializeCharArray(pSerialize, value, _countof(value), #value); 

//���л�����
#define SERIALIZE_STRUCT_ARRAY(value) \
				SerializeHelper::SerializeArray(pSerialize, value, _countof(value), #value); 

/************************************************************************/
/* ʹ��ȫ�����л�����ʱ�ĺ� SerializeStruct                                */
/************************************************************************/
//���л������ַ���������ĺ궨�壬ʹ���ⲿ�����л�����ʱ�İ�������
#define SERIALIZE_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, Value.value, #value); 

//���л��ַ�������궨��
#define SERIALIZE_CHAR_ARRAY(value) \
                SerializeHelper::SerializeCharArray(pSerialize, Value.value, _countof(Value.value), #value); 

//���л�����
#define SERIALIZE_ARRAY(value) \
				SerializeHelper::SerializeArray(pSerialize, Value.value, _countof(Value.value), #value); 


/************************************************************************/
/* ���л���һЩ����������ʹ��ʹ�����л���ʱ�򣬼�ͳһ��ʽ��                   */
/* pSerializeָ�����ﲻ���пգ��ⲿ�ж�                                     */
/************************************************************************/
namespace SerializeHelper
{
inline void test();

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ����������ʾ�ַ�
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, long double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�������Ĭ��ΪGB2312�����ı���ʹ��SetStringCode
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, CSerializeString& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�������Ĭ��ΪGB2312�����ı���ʹ��SetStringCode
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ�����������'\0'�������м䲻�ܹ�����'\0'
//					ulValueBufferSize	[����/���]	_countof(Value)��С�����л����������л�
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void SerializeCharArray(ISerialize *pSerialize, char *Value, unsigned long ulValueBufferSize, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ������飬
//					ulValueBufferSize	[����/���]	_countof(Value)��С�����л����������л�
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л���������
// $_FUNCTION_END *********************************************************
template<typename T>
void SerializeArray(ISerialize *pSerialize, T Value[], unsigned long ulValueCount, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
// �� �� ֵ��
// ����˵�������л��ṹ�����
// $_FUNCTION_END *********************************************************
template<typename T>
bool SerializeStruct(ISerialize *pSerialize, T &Value);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л��ṹ�����
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialize, T &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					tArray				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�vector�������
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialize, std::vector<T> &tArray, const char *pstrName);

};

#include "SerializeHelper.inl"