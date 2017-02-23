#pragma once
#include "TKPtrList.h"
#include "SerializeHelper.h"

namespace SerializeHelper
{
/************************************************************************/
/* 数组控制序列化                                                         */
/************************************************************************/

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					tArray				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化vector数组变量
// $_FUNCTION_END *********************************************************
template<typename T>
inline void Serialize(ISerialize *pSerialize, CTKPtrList<T> &tArray, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					tArray				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化vector数组变量
// $_FUNCTION_END *********************************************************
template<typename T>
inline void Serialize(ISerialize *pSerialize, std::vector<T*> &tArray, const char *pstrName);
};
#include "SerializeHelperEx.inl"