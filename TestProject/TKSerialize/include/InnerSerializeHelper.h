// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�InnerSerializeHelper.h
// �������ڣ�2017-02-23
// �����ˣ�����
// �ļ�˵�������л��ڲ�ʹ�õĺ���
// $_FILEHEADER_END ***********************************************************
#pragma once
#include "EnumSerialize.h"

namespace SerializeHelper
{
/************************************************************************/
/* ���������л���������׳��쳣����������������л���                          */
/* Json��xml֧��ĳЩ�ֶγ���󣬼������л�                                   */
/************************************************************************/
inline void ThrowException(ISerialize *pSerialize);

/************************************************************************/
/* �����������л��ӿ�ģ�壬�������쳣������ͳһ�˳�                            */
/************************************************************************/
template<typename T>
inline bool InnerSerializeWithException(ISerialize *pSerialize, T& Value, const char *pstrName);

/************************************************************************/
/* ����������л�д���ṩ�����������飬����ʹ�ô˺�������vector,list,set       */
/************************************************************************/
template<typename T, typename _InIt>
inline void InnerSerializeArrayWrite(ISerialize *pSerialize, _InIt _First, suint32 ulValueCount, const char *pstrName);

/************************************************************************/
/* ����������л������ṩ�����������飬����ʹ�ô˺�������vector,list,set       */
/************************************************************************/
template<typename T, typename _InIt>
inline void InnerSerializeArrayRead(ISerialize *pSerialize, _InIt _First, suint32 ulLimitedCount, const char *pstrName);

//ԭ�������������л��������������л�
template<typename T>
inline void InnerSerializeArray(ISerialize *pSerialize, T tArray[], suint32 ulCount, const char *pstrName);

//�ṩһ��char�����ȫ�������汾,char���鵱���ַ������л�����Ӧ��������
template<>
inline void InnerSerializeArray<char>(ISerialize *pSerialize, char tArray[], suint32 ulCount, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�InnerSerializeAnyVectorType
// ����������
//					pSerialize			[����]		���л��ӿ�
//					tArray				[����/���]	��Ҫ���л�������
//					pstrName			[����/���]	����������,nullptr��ʾ�˲���û������
// �� �� ֵ��
// ����˵�����ṩһ��ͨ�õ�vector���л�����
// $_FUNCTION_END *********************************************************
template<typename VECTOR_TYPE>
inline void InnerSerializeAnyVectorType(ISerialize *pSerialize, VECTOR_TYPE &tArray, const char *pstrName);

template<typename VECTOR_TYPE>
inline suint32 InnerGetAnyVectorTypeSize(VECTOR_TYPE &tArray);

template<typename VECTOR_TYPE>
inline bool InnerSerializeAnyVectorTypeItem(ISerialize *pSerialize, VECTOR_TYPE &tArray, suint32 unIndex);
};
#include "InnerSerializeHelper.inl"