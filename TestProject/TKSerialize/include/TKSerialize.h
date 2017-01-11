#pragma once
#include "TKSerializeExport.h"
#include "EnumSerialize.h"
#include "InterfaceSerialize.h"

namespace SerializeExport
{
// $_FUNCTION_BEGIN *******************************************************
// 函数名称：CreateSerializeInterface
// 函数参数：
//					SerializeFormat	[输入]		序列化方式
// 返 回 值：序列化接口
// 函数说明：获取某种序列化接口
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API ISerialize* CreateSerializeInterface(EnumSerializeFormat SerializeFormat);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：DestroySerializeInterface
// 函数参数：
//					pInterface		[输入]		序列化接口
// 返 回 值：true or false
// 函数说明：释放序列化接口
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API bool DestroySerializeInterface(ISerialize *pInterface);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：SetDefaultStringCode
// 函数参数：
//					DefaultStringCode	[输入]	默认字符串编码
// 返 回 值：true or false
// 函数说明：设置默认std::string char[]中，存储的字符串编码格式
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API bool SetDefaultStringCode(EnumSerializeStringCode DefaultStringCode);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：GetDefaultStringCode
// 函数参数：
// 返 回 值：字符串编码
// 函数说明：获取默认std::string char[]中，存储的字符串编码格式
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API EnumSerializeStringCode GetDefaultStringCode();
}
