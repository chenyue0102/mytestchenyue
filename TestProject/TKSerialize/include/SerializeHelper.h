// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�SerializeHelper.h
// �������ڣ�2016-04-08
// �����ˣ�����
// �ļ�˵�������л������࣬����ʹ�����л��������ͣ��ṹ�����ͣ�vector���鷽ʽһ��
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <vector>
#include <string>
#include "EnumSerialize.h"

#define MAX_ARRAY_LIMITED_COUNT		2147483647		//���л�Array��ʱ����Ҫһ������������������ֵ��ʾ�������


namespace SerializeExport
{
	class CSerializeString;
	struct ISerialize;
}
#ifdef QT_CORE_LIB
class QString;
#endif
using namespace  SerializeExport;
/************************************************************************/
/* ���л��� Serialize                                                */
/************************************************************************/
//���л��궨��
#define SERIALIZE_STRUCT_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, value, #value); 

/************************************************************************/
/* ʹ��ȫ�����л�����ʱ�ĺ� SerializeStruct                                */
/************************************************************************/
//���л��궨�壬ʹ���ⲿ�����л�����ʱ�İ�������
#define SERIALIZE_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, Value.value, #value); 



/************************************************************************/
/* ���л���һЩ����������ʹ��ʹ�����л���ʱ�򣬼�ͳһ��ʽ��                   */
/* pSerializeָ�����ﲻ���пգ��ⲿ�ж�                                     */
/************************************************************************/
namespace SerializeHelper
{

/************************************************************************/
/* �����������л�����                                                      */
/************************************************************************/

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ����������ʾ�ַ�
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, long double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�������Ĭ��ΪGB2312�����ı���ʹ��SetStringCode
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, CSerializeString& Value, const char *pstrName);



/************************************************************************/
/* ��չ�������л�������InnerSerializeWithException�ɹ����ٸ�ֵ              */
/************************************************************************/

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ������ַ�������Ĭ��ΪGB2312�����ı���ʹ��SetStringCode
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, std::string& Value, const char *pstrName);

#ifdef QT_CORE_LIB
// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�����
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, QString& Value, const char *pstrName);
#endif


/************************************************************************/
/* ����������л�                                                         */
/************************************************************************/

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
inline void Serialize(ISerialize &pSerialize, std::vector<T> &tArray, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					tArray				[����/���]	��Ҫ���л��Ĳ���
//					pstrName			[����]		����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�������л�int nParam[8],char szNickName[16]�����ĳ�Ա�������
// $_FUNCTION_END *********************************************************
template<typename T, size_t _Size> 
inline void Serialize(ISerialize &pSerialize, T (&tArray)[_Size], const char *pstrName);


/************************************************************************/
/* �ṹ��������л����ǽ���ʽ���л���������������                              */
/* struct Test                                                          */
/* {                                                                    */
/*    int a;                                                            */
/* };                                                                   */
/* //�ṹ�����л��������Ʊ���ΪSerializeStruct�����ʹ��SERIALIZE_VALUE��     */
/* //�������Ʊ���ΪValue                                                  */
/* bool SerializeStruct(ISerialize &pSerialize, Test &Value)            */
/* {                                                                    */
/*     try                                                              */
/*     {                                                                */
/*         SERIALIZE_VALUE(a);                                          */
/*     }                                                                */
/*     catch (...)                                                      */
/*     {                                                                */
/*         return false;                                                */
/*     }                                                                */
/*     return true;                                                     */
/* }                                                                    */
/************************************************************************/

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
inline void Serialize(ISerialize &pSerialize, T &Value, const char *pstrName);


/************************************************************************/
/* �������Ա������ʽ���л����������£�                                       */
/* struct Test                                                          */
/* {                                                                    */
/*		int a;                                                          */
/*      //��Ա�������л����Ʊ���ΪSerialize�����ʹ��SERIALIZE_STRUCT_VALUE�� */
/*		bool Serialize(ISerialize &pSerialize)                          */
/*      {                                                               */
/*          try                                                         */
/*          {                                                           */
/*              SERIALIZE_STRUCT_VALUE(a);                              */
/*          }                                                           */
/*          catch (...)                                                 */
/*          {                                                           */
/*              return false;                                           */
/*          }                                                           */
/*          return true;                                                */
/*      }                                                               */
/* };                                                                   */
/************************************************************************/


// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�Serialize
// ����������
//					pSerialize			[����]		���л��ӿ�
//					Value				[����/���]	��Ҫ���л��Ĳ���
// �� �� ֵ��
// ����˵�������л��ṹ�������ֻΪ���ݳ�Ա������ʽ���л�����������£��˺���û���ô�
// $_FUNCTION_END *********************************************************
template<typename T>
inline bool SerializeStruct(ISerialize &pSerialize, T &Value);
};

#include "SerializeHelper.inl"