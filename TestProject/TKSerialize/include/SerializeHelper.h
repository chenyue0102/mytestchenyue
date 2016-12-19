// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：SerializeHelper.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化帮助类，可以使得序列化基本类型，结构体类型，vector数组方式一样
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
/* 序列化宏 Serialize                                                */
/************************************************************************/
//序列化除了字符数组以外的宏定义
#define SERIALIZE_STRUCT_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, value, #value); 

//序列化字符串数组宏定义
#define SERIALIZE_STRUCT_CHAR_ARRAY(value) \
                SerializeHelper::SerializeCharArray(pSerialize, value, _countof(value), #value); 

//序列化数组
#define SERIALIZE_STRUCT_ARRAY(value) \
				SerializeHelper::SerializeArray(pSerialize, value, _countof(value), #value); 

/************************************************************************/
/* 使用全局序列化函数时的宏 SerializeStruct                                */
/************************************************************************/
//序列化除了字符数组以外的宏定义，使用外部的序列化函数时的帮助函数
#define SERIALIZE_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, Value.value, #value); 

//序列化字符串数组宏定义
#define SERIALIZE_CHAR_ARRAY(value) \
                SerializeHelper::SerializeCharArray(pSerialize, Value.value, _countof(Value.value), #value); 

//序列化数组
#define SERIALIZE_ARRAY(value) \
				SerializeHelper::SerializeArray(pSerialize, Value.value, _countof(Value.value), #value); 


/************************************************************************/
/* 序列化的一些帮助函数，使得使用序列化的时候，简化统一方式，                   */
/* pSerialize指针这里不会判空，外部判断                                     */
/************************************************************************/
namespace SerializeHelper
{
inline void test();

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，这个表示字符
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, long double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，字符串编码默认为GB2312。更改编码使用SetStringCode
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, CSerializeString& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，字符串编码默认为GB2312。更改编码使用SetStringCode
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，必须以'\0'结束，中间不能够包含'\0'
//					ulValueBufferSize	[输入/输出]	_countof(Value)大小，序列化函数会序列化
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void SerializeCharArray(ISerialize *pSerialize, char *Value, unsigned long ulValueBufferSize, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数数组，
//					ulValueBufferSize	[输入/输出]	_countof(Value)大小，序列化函数会序列化
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量数组
// $_FUNCTION_END *********************************************************
template<typename T>
void SerializeArray(ISerialize *pSerialize, T Value[], unsigned long ulValueCount, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
// 返 回 值：
// 函数说明：序列化结构体变量
// $_FUNCTION_END *********************************************************
template<typename T>
bool SerializeStruct(ISerialize *pSerialize, T &Value);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化结构体变量
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialize, T &Value, const char *pstrName);

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
void Serialize(ISerialize *pSerialize, std::vector<T> &tArray, const char *pstrName);

};

#include "SerializeHelper.inl"