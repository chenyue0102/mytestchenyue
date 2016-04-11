// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�SerializeHelper.h
// �������ڣ�2016-04-08
// �����ˣ�����
// �ļ�˵�������л������࣬����ʹ�����л��������ͣ��ṹ�����ͣ�vector���鷽ʽһ��
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <vector>
#include "ISerialize.h"

#ifdef CONVER_STRING_CODE
class CUTF8_GBK_Convert;
#endif
/************************************************************************/
/* ���л���                                                              */
/************************************************************************/
//���л������ַ���������ĺ궨��
#define SERIALIZE_VALUE(value) \
                Serialize(pSerialize, value, #value); \

//���л��ַ�������궨��
#define SERIALIZE_CHAR(value) \
                Serialize(pSerialize, value, _countof(value), #value); \


/************************************************************************/
/* ���л���һЩ����������ʹ��ʹ�����л���ʱ�򣬼�ͳһ��ʽ��                   */
/* pSerializationָ�����ﲻ���пգ��ⲿ�ж�                                 */
/************************************************************************/
namespace SerializeHelper
{
void test();

#ifdef CONVER_STRING_CODE
void SetConverStringCode(CUTF8_GBK_Convert &Conver);
#endif

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, std::string& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ�����������'\0'�������м䲻�ܹ�����'\0'
//					ulValueBufferSize	[����/���]	_countof(Value)��С�����л����������л�
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, char *Value, unsigned long ulValueBufferSize, const char *pstrName);


// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л��ṹ�����
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialization, T &Value, const char *pstrName)
{
	//T���ͱ����ǽṹ�������
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	try
	{
		//���Json��û������ṹ�壬�����л��������׳��쳣
		pSerialization->BeginSerlizeStruct(pstrName);
	}
	catch (int)
	{
		//û�нṹ�壬��Ϊ������
		return;
	}
	
	if (!Value.Serialization(pSerialization))
		throw(-1);
	pSerialization->EndSerlizeStruct(pstrName);
}

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialization		[����]		���л��ӿ�
//					tArray				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�vector�������
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialization, std::vector<T> &tArray, const char *pstrName)
{
	unsigned long ulCount = tArray.size();
	try
	{
		//���Json��û������ṹ�壬�����л��������׳��쳣
		pSerialization->BeginSerlizeArray(ulCount, pstrName);
	}
	catch (int)
	{
		//û�нṹ�壬��Ϊ������
		return;
	}
	
	for (unsigned long ulIndex = 0; ulIndex < ulCount; ulIndex++)
	{
		pSerialization->BeginSerlizeArrayItem(ulIndex, pstrName);
		if (enum_Serialization_Type_Read == pSerialization->GetSerializationType())
		{
			T t;
			Serialize(pSerialization, t, nullptr);
			tArray.push_back(t);
		}
		else
		{
			Serialize(pSerialization, tArray[ulIndex], nullptr);
		}
		pSerialization->EndSerlizeArrayItem(ulIndex, pstrName);
	}
	pSerialization->EndSerlizeArray(pstrName);
}

};

