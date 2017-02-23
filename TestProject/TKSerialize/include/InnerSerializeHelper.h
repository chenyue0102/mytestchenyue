// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：InnerSerializeHelper.h
// 创建日期：2017-02-23
// 创建人：陈月
// 文件说明：序列化内部使用的函数
// $_FILEHEADER_END ***********************************************************
#pragma once
#include "EnumSerialize.h"

namespace SerializeHelper
{
/************************************************************************/
/* 二进制序列化，出错后抛出异常，不在允许继续序列化，                          */
/* Json与xml支持某些字段出错后，继续序列化                                   */
/************************************************************************/
inline void ThrowException(ISerialize *pSerialize);

/************************************************************************/
/* 真正调用序列化接口模板，增加了异常，方便统一退出                            */
/************************************************************************/
template<typename T>
inline bool InnerSerializeWithException(ISerialize *pSerialize, T& Value, const char *pstrName);

/************************************************************************/
/* 数组控制序列化写，提供迭代器的数组，可以使用此函数，如vector,list,set       */
/************************************************************************/
template<typename T, typename _InIt>
inline void InnerSerializeArrayWrite(ISerialize *pSerialize, _InIt _First, suint32 ulValueCount, const char *pstrName);

/************************************************************************/
/* 数组控制序列化读，提供迭代器的数组，可以使用此函数，如vector,list,set       */
/************************************************************************/
template<typename T, typename _InIt>
inline void InnerSerializeArrayRead(ISerialize *pSerialize, _InIt _First, suint32 ulLimitedCount, const char *pstrName);

//原生数组类型序列化，按照数组序列化
template<typename T>
inline void InnerSerializeArray(ISerialize *pSerialize, T tArray[], suint32 ulCount, const char *pstrName);

//提供一个char数组的全特例化版本,char数组当成字符串序列化，不应当成数组
template<>
inline void InnerSerializeArray<char>(ISerialize *pSerialize, char tArray[], suint32 ulCount, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：InnerSerializeAnyVectorType
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					tArray				[输入/输出]	需要序列化的数组
//					pstrName			[输入/输出]	参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：提供一个通用的vector序列化函数
// $_FUNCTION_END *********************************************************
template<typename VECTOR_TYPE>
inline void InnerSerializeAnyVectorType(ISerialize *pSerialize, VECTOR_TYPE &tArray, const char *pstrName);

template<typename VECTOR_TYPE>
inline suint32 InnerGetAnyVectorTypeSize(VECTOR_TYPE &tArray);

template<typename VECTOR_TYPE>
inline bool InnerSerializeAnyVectorTypeItem(ISerialize *pSerialize, VECTOR_TYPE &tArray, suint32 unIndex);
};
#include "InnerSerializeHelper.inl"