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
/* 序列化宏 Serialize                                                */
/************************************************************************/
//序列化除了字符数组以外的宏定义
#define SERIALIZE_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, value, #value); 

//序列化字符串数组宏定义
#define SERIALIZE_CHAR(value) \
                SerializeHelper::Serialize(pSerialize, value, _countof(value), #value); 

//序列化数组
#define SERIALIZE_ARRAY(value) \
				SerializeHelper::Serialize(pSerialize, value, _countof(value), #value); 

/************************************************************************/
/* 使用全局序列化函数时的宏 SerializeStruct                                */
/************************************************************************/
//序列化除了字符数组以外的宏定义，使用外部的序列化函数时的帮助函数
#define SERIALIZE_STRUCT_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, Value.value, #value); 

//序列化字符串数组宏定义
#define SERIALIZE_STRUCT_CHAR(value) \
                SerializeHelper::Serialize(pSerialize, Value.value, _countof(Value.value), #value); 

//序列化数组
#define SERIALIZE_STRUCT_ARRAY(value) \
				SerializeHelper::Serialize(pSerialize, Value.value, _countof(Value.value), #value); 


/************************************************************************/
/* 序列化的一些帮助函数，使得使用序列化的时候，简化统一方式，                   */
/* pSerialize指针这里不会判空，外部判断                                     */
/************************************************************************/
class CSerializeString;
namespace SerializeHelper
{
void test();

//调用void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName);的时候
//Value中字符串的字符编码，序列化Json的时候，如果Value是GB2312，帮助类会转换为utf8，然后在传递给Json序列化类
//默认是EnumStringCodeNone。EnumStringCodeNone与EnumStringCodeGB2312逻辑相等
enum EnumStringCode
{
	EnumStringCodeNone,		//默认，与EnumStringCodeGB2312逻辑相等
	EnumStringCodeGB2312,	//GB2312，
	EnumStringCodeUtf8,		//utf8
	EnumStringCodeBinary,	//std::string中存储的是二进制数据
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
void Serialize(ISerialize *pSerialize, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，这个表示字符
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, char& Value, const char *pstrName);

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
void Serialize(ISerialize *pSerialize, long double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，字符串编码默认为GB2312。更改编码使用SetStringCode
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
void Serialize(ISerialize *pSerialize, CSerializeString& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，字符串编码默认为GB2312。更改编码使用SetStringCode
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
//					Value				[输入/输出]	需要序列化的参数数组，
//					ulValueBufferSize	[输入/输出]	_countof(Value)大小，序列化函数会序列化
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量数组
// $_FUNCTION_END *********************************************************
template<typename T>
void Serialize(ISerialize *pSerialize, T Value[], unsigned long ulValueCount, const char *pstrName)
{
	//T 类型
	static_assert(!std::is_pointer<T>::value, "Serialize T must be not pointer");
	unsigned long ulCount = ulValueCount;
	try
	{
		//如果Json中没有这个结构体，则序列化函数会抛出异常
		pSerialize->BeginSerializeArray(ulCount, pstrName);
	}
	catch (int)
	{
		// Json，Xml没有结构体，认为是正常。
		return;
	}

	assert(ulValueCount == ulCount);
	for (unsigned long ulIndex = 0; ulIndex < ulCount && ulIndex < ulValueCount; ulIndex++)
	{
		pSerialize->BeginSerializeArrayItem(ulIndex, pstrName);
		Serialize(pSerialize, Value[ulIndex], nullptr);
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}
	pSerialize->EndSerializeArray(pstrName);
}

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
// 返 回 值：
// 函数说明：序列化结构体变量
// $_FUNCTION_END *********************************************************
template<typename T>
inline bool SerializeStruct(ISerialize *pSerialize, T &Value)
{
	//T类型必须是结构体或者类
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	return Value.Serialize(pSerialize);
}

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
		pSerialize->BeginSerializeStruct(pstrName);
	}
	catch (int)
	{
		//没有结构体，认为是正常
		return;
	}
	
	if (!SerializeStruct(pSerialize, Value))
	{
		throw - 1;
	}

	pSerialize->EndSerializeStruct(pstrName);
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
		pSerialize->BeginSerializeArray(ulCount, pstrName);
	}
	catch (int)
	{
		// Json，Xml没有结构体，认为是正常。
		return;
	}
	
	for (unsigned long ulIndex = 0; ulIndex < ulCount; ulIndex++)
	{
		pSerialize->BeginSerializeArrayItem(ulIndex, pstrName);
		if (EnumSerializeIORead == pSerialize->GetSerializeType())
		{
			T t;
			Serialize(pSerialize, t, nullptr);
			tArray.push_back(t);
		}
		else
		{
			Serialize(pSerialize, tArray[ulIndex], nullptr);
		}
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}
	pSerialize->EndSerializeArray(pstrName);
}

};

