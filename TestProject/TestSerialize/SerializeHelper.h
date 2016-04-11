// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：SerializeHelper.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化帮助类，可以使得序列化基本类型，结构体类型，vector数组方式一样
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <vector>
#include "ISerialize.h"

#ifdef CONVER_STRING_CODE
class CUTF8_GBK_Convert;
#endif
/************************************************************************/
/* 序列化宏                                                              */
/************************************************************************/
//序列化除了字符数组以外的宏定义
#define SERIALIZE_VALUE(value) \
                Serialize(pSerialize, value, #value); \

//序列化字符串数组宏定义
#define SERIALIZE_CHAR(value) \
                Serialize(pSerialize, value, _countof(value), #value); \


/************************************************************************/
/* 序列化的一些帮助函数，使得使用序列化的时候，简化统一方式，                   */
/* pSerialization指针这里不会判空，外部判断                                 */
/************************************************************************/
namespace SerializeHelper
{
void test();

#ifdef CONVER_STRING_CODE
void SetConverStringCode(CUTF8_GBK_Convert &Conver);
#endif

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, std::string& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，必须以'\0'结束，中间不能够包含'\0'
//					ulValueBufferSize	[输入/输出]	_countof(Value)大小，序列化函数会序列化
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialization, char *Value, unsigned long ulValueBufferSize, const char *pstrName);


// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化结构体变量
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialization, T &Value, const char *pstrName)
{
	//T类型必须是结构体或者类
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	try
	{
		//如果Json中没有这个结构体，则序列化函数会抛出异常
		pSerialization->BeginSerlizeStruct(pstrName);
	}
	catch (int)
	{
		//没有结构体，认为是正常
		return;
	}
	
	if (!Value.Serialization(pSerialization))
		throw(-1);
	pSerialization->EndSerlizeStruct(pstrName);
}

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialization		[输入]		序列化接口
//					tArray				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化vector数组变量
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialization, std::vector<T> &tArray, const char *pstrName)
{
	unsigned long ulCount = tArray.size();
	try
	{
		//如果Json中没有这个结构体，则序列化函数会抛出异常
		pSerialization->BeginSerlizeArray(ulCount, pstrName);
	}
	catch (int)
	{
		//没有结构体，认为是正常
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

