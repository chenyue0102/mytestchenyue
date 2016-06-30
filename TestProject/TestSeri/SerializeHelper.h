// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�SerializeHelper.h
// �������ڣ�2016-04-08
// �����ˣ�����
// �ļ�˵�������л������࣬����ʹ�����л��������ͣ��ṹ�����ͣ�vector���鷽ʽһ��
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <vector>
#include <windows.h>
#include "ISerialize.h"


/************************************************************************/
/* ���л���                                                              */
/************************************************************************/
//���л������ַ���������ĺ궨��
#define SERIALIZE_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, value, #value); \

//���л��ַ�������궨��
#define SERIALIZE_CHAR(value) \
                SerializeHelper::Serialize(pSerialize, value, _countof(value), #value); \

//���л������ַ���������ĺ궨�壬ʹ���ⲿ�����л�����ʱ�İ�������
#define SERIALIZE_STRUCT_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, Value.value, #value); \


/************************************************************************/
/* ���л���һЩ����������ʹ��ʹ�����л���ʱ�򣬼�ͳһ��ʽ��           */
/* pSerializeָ�����ﲻ���пգ��ⲿ�ж�                                 */
/************************************************************************/
namespace SerializeHelper
{
void test();

//����void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName);��ʱ��
//Value���ַ������ַ����룬���л�Json��ʱ�����Value��GB2312���������ת��Ϊutf8��Ȼ���ڴ��ݸ�Json���л���
//Ĭ����EnumStringCodeNone��EnumStringCodeNone��EnumStringCodeGB2312�߼����
enum EnumStringCode
{
	EnumStringCodeNone,
	EnumStringCodeGB2312,
	EnumStringCodeUtf8,
};

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					StringCode			[����]		���л�std::string��ʱ���ַ�������
// �� �� ֵ��
// ����˵�����������л�std::string��ʱ��
// $_FUNCTION_END *********************************************************
void SetStringCode(EnumStringCode StringCode);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ����������ʾ�ַ�
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, long double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�������Ĭ��ΪGB2312�����ı���ʹ��SetStringCode
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName);

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
void Serialize(ISerialize *pSerialize, char *Value, unsigned long ulValueBufferSize, const char *pstrName);


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
inline BOOL SerializeStruct(ISerialize *pSerialize, T &Value)
{
	//T���ͱ����ǽṹ�������
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	return Value.Serialization(pSerialize);
}

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
void Serialize(ISerialize *pSerialize, T &Value, const char *pstrName)
{
	//T���ͱ����ǽṹ�������
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	try
	{
		//���Json��û������ṹ�壬�����л��������׳��쳣
		pSerialize->BeginSerlizeStruct(pstrName);
	}
	catch (int)
	{
		//û�нṹ�壬��Ϊ������
		return;
	}
	
	if (!SerializeStruct(pSerialize, Value))
	{
		throw - 1;
	}

	pSerialize->EndSerlizeStruct(pstrName);
}

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
void Serialize(ISerialize *pSerialize, std::vector<T> &tArray, const char *pstrName)
{
	unsigned long ulCount = tArray.size();
	try
	{
		//���Json��û������ṹ�壬�����л��������׳��쳣
		pSerialize->BeginSerlizeArray(ulCount, pstrName);
	}
	catch (int)
	{
		// Json��Xmlû�нṹ�壬��Ϊ��������
		return;
	}
	
	for (unsigned long ulIndex = 0; ulIndex < ulCount; ulIndex++)
	{
		pSerialize->BeginSerlizeArrayItem(ulIndex, pstrName);
		if (enum_Serialization_Type_Read == pSerialize->GetSerializationType())
		{
			T t;
			Serialize(pSerialize, t, nullptr);
			tArray.push_back(t);
		}
		else
		{
			Serialize(pSerialize, tArray[ulIndex], nullptr);
		}
		pSerialize->EndSerlizeArrayItem(ulIndex, pstrName);
	}
	pSerialize->EndSerlizeArray(pstrName);
}

};

