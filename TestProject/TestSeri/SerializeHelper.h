// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：SerializeHelper.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化帮助类，可以使得序列化基本类型，结构体类型，vector数组方式一样
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <vector>
#include "ISerialize.h"


/************************************************************************/
/* 序列化宏                                                              */
/************************************************************************/
//序列化除了字符数组以外的宏定义
#define SERIALIZE_VALUE(value) \
                Serialize(pSerialize, value, #value); \

//序列化字符串数组宏定义
#define SERIALIZE_CHAR(value) \
                Serialize(pSerialize, value, _countof(value), #value); \

//序列化除了字符数组以外的宏定义
#define SERIALIZE_STRUCT_VALUE(value) \
                Serialize(pSerialize, Value.value, #value); \


/*
序列化结构体的时候，使用成员变量序列化函数，否则使用外部的序列化函数。示例如下
使用成员变量序列化函数
struct Tlv
{
	DWORD dwID;
	std::string strValue;
	BOOL Serialization(ISerialize *pSerialize)
	{
		try
		{
			Serialize(pSerialize, ID, "ID");
			Serialize(pSerialize, strValue, "strValue");
		}
		catch (...)
		{
			return FALSE;
		}
		return TRUE;
	}
};
使用外部的序列化函数
struct Tlv
{
	DWORD dwID;
	std::string strValue;
}
bool SerializeStruct(ISerialize *pSerialize, Tlv &Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(ID);
		SERIALIZE_STRUCT_VALUE(strValue);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}
*/
#define USER_CLASS_MEMBER_SERIALIZE

/************************************************************************/
/* 序列化的一些帮助函数，使得使用序列化的时候，简化统一方式，                   */
/* pSerialize指针这里不会判空，外部判断                                 */
/************************************************************************/
namespace SerializeHelper
{
void test();

//调用void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName);的时候
//Value中字符串的字符编码，序列化Json的时候，如果Value是GB2312，帮助类会转换为utf8，然后在传递给Json序列化类
//默认是EnumStringCodeNone。EnumStringCodeNone与EnumStringCodeGB2312逻辑相等
enum EnumStringCode
{
	EnumStringCodeNone,
	EnumStringCodeGB2312,
	EnumStringCodeUtf8,
};

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					StringCode			[输入]		序列化std::string的时候，字符串编码
// 返 回 值：
// 函数说明：设置序列化std::string的时候
// $_FUNCTION_END *********************************************************
void SetStringCode(EnumStringCode StringCode);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName);

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
void Serialize(ISerialize *pSerialize, char *Value, unsigned long ulValueBufferSize, const char *pstrName);


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
void Serialize(ISerialize *pSerialize, T &Value, const char *pstrName)
{
	//T类型必须是结构体或者类
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	try
	{
		//如果Json中没有这个结构体，则序列化函数会抛出异常
		pSerialize->BeginSerlizeStruct(pstrName);
	}
	catch (int)
	{
		//没有结构体，认为是正常
		return;
	}
	
#ifdef USER_CLASS_MEMBER_SERIALIZE
	if (!Value.Serialization(pSerialize))
		throw(-1);
#else
	SerializeStruct(pSerialize, Value);
#endif

	pSerialize->EndSerlizeStruct(pstrName);
}

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
void Serialize(ISerialize *pSerialize, std::vector<T> &tArray, const char *pstrName)
{
	unsigned long ulCount = tArray.size();
	try
	{
		//如果Json中没有这个结构体，则序列化函数会抛出异常
		pSerialize->BeginSerlizeArray(ulCount, pstrName);
	}
	catch (int)
	{
		//没有结构体，认为是正常
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

