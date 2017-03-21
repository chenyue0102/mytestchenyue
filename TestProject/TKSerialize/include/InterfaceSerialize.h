// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：ISerialize.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化接口定义
// $_FILEHEADER_END ***********************************************************
#pragma once
#include "EnumSerialize.h"


namespace SerializeExport
{
class CSerializeString;
/************************************************************************/
/* 序列化的接口，统一二进制与Json序列化方式                                  */
/************************************************************************/
struct ISerialize
{
	/************************************************************************/
	/*     缓冲区设置函数                                                     */
	/************************************************************************/
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeType
	// 函数参数：
	//					iSerializeType	[输入]		设置序列化方式
	// 返 回 值：true or false
	// 函数说明：设置序列化方式
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeIO iSerializeType) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeType
	// 函数参数：
	// 返 回 值：序列化方式
	// 函数说明：获取序列化方式
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeIO GetSerializeType() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeFormat
	// 函数参数：
	// 返 回 值：序列化的格式
	// 函数说明：获取序列化的格式
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeFormat GetSerializeFormat() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeStringCode
	// 函数参数：
	//					SerializeStringCode	[输入]		设置std::string字符串编码，默认是EnumSerializeStringCodeNone
	// 返 回 值：true or false
	// 函数说明：设置std::string字符串编码，
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeStringCode(EnumSerializeStringCode SerializeStringCode) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeStringCode
	// 函数参数：
	// 返 回 值：
	// 函数说明：获取std::string字符串编码，
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeStringCode GetSerializeStringCode() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetData
	// 函数参数：
	//					pstrText			[输入]		缓冲区
	//					ulDataLength		[输入]		缓冲区长度
	// 返 回 值：true or false
	// 函数说明：设置需要序列化读的缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, suint32 ulDataLength) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetData
	// 函数参数：
	// 返 回 值：序列化缓冲区
	// 函数说明：获取序列化缓冲区
	// $_FUNCTION_END *********************************************************
	virtual const char* GetData() = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetDataLen
	// 函数参数：
	// 返 回 值：序列化缓冲区长度
	// 函数说明：获取序列化缓冲区长度
	// $_FUNCTION_END *********************************************************
	virtual suint32 GetDataLen() = 0;
	
	/************************************************************************/
	/*    序列化结构体或者数组控制函数                                          */
	/************************************************************************/
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，接下来要序列化一个结构体
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeStruct(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，当前的结构体已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeStruct(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArray
	// 函数参数：
	//					ulCount				[输入/输出]	列表的长度
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，接下来要序列化一个列表，并设置/获取列表的长度
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArray(suint32 &ulCount, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArray
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，当前的列表已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArray(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，接下来要序列化列表中的第N个元素
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArrayItem(suint32 ulIndex, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，列表中的第N个元素已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArrayItem(suint32 ulIndex, const char *pstrName) = 0;

	/************************************************************************/
	/*  序列化字段函数                                                        */
	/************************************************************************/
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数，这个表示字符
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long double& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化字符串变量，CSerializeString支持跨dll边界，std::string不能够跨dll边界
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(CSerializeString& Value, const char *pstrName) = 0;
};

//为了兼容海豚现有序列化二进制格式，扩展了接口，增加了一个固定长度的字符串序列化，序列化不打入长度。
//只限海豚使用
//这个接口，只支持二进制序列化。Json不支持
struct IAssistorSerialize : public ISerialize
{
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：AssistorSerialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					ulDataLength		[输入]		缓冲区长度
	// 返 回 值：true or false
	// 函数说明：从缓冲区中，读取/写入ulDataLength长度
	// $_FUNCTION_END *********************************************************
	virtual bool AssistorSerialize(char *Value, suint32 ulDataLength) = 0;
};
}


