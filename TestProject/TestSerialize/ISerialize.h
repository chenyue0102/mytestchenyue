#pragma once
#include <string>
#include "EnumSerialize.h"
#include <unknwn.h>

#ifndef interface
#define interface struct
#endif


interface ISerializeStream : public IUnknown
{
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeType
	// 函数参数：
	// 返 回 值：当前序列化所对应的类型，参照枚举EnumSerializeType
	// 函数说明：获取当前序列化所对应的类型
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeType GetSerializeType() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeType
	// 函数参数：
	//			 SerializeType		[输入]	序列化类型
	// 返 回 值：true or false
	// 函数说明：设置当前序列化所对应的类型
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeType SerializeType) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeReadBuffer
	// 函数参数：
	//			 pBuffer			[输入]	缓冲区
	//			 ulBufferLength		[输入]	缓冲区长度
	// 返 回 值：true or false
	// 函数说明：设置序列化读取的缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeReadBuffer(const void *pBuffer, unsigned long ulBufferLength) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetWriteBuffer
	// 函数参数：
	// 返 回 值：缓冲区地址
	// 函数说明：获取写序列化缓冲区
	// $_FUNCTION_END *********************************************************
	virtual const void * GetWriteBuffer() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetWriteBufferLength
	// 函数参数：
	// 返 回 值：缓冲区长度
	// 函数说明：获取写序列化缓冲区长度
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetWriteBufferLength() = 0;
};

interface ISerialize : public ISerializeStream
{
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化bool
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化float
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化double
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double &Value) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 pBuffer			[输入/输出]	被序列化的缓冲区
	//			 ulBufferLen		[输入/输出]	被序列化的缓冲区长度
	// 返 回 值：true or false
	// 函数说明：序列化缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(void *pBuffer, unsigned long ulBufferLen) = 0;
};