#pragma once
#include "TKPtrList.h"
#include "SerializeHelper.h"

namespace SerializeHelper
{
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
inline void Serialize(ISerialize *pSerialize, CTKPtrList<T> &tArray, const char *pstrName);

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
inline void Serialize(ISerialize *pSerialize, std::vector<T*> &tArray, const char *pstrName);
};
#include "SerializeHelperEx.inl"