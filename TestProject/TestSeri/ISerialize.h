// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：ISerialize.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化接口定义
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <string>


// 序列化类型
enum EnumSerializeIO
{
	EnumSerializeIONone,	// 默认值
	EnumSerializeIORead,		// 读取数据
	EnumSerializeIOWrite,		// 写入数据
};

// 序列化的格式
enum EnumSerializeFormat
{
	EnumSerializeFormatNone,
	EnumSerializeFormatBinary,	// 二进制，
	EnumSerializeFormatJson,	// Json格式，序列化std::string的时候，Json格式只接受utf8字符串
	EnumSerializeFormatXml,		// Xml格式，序列化std::string的时候，只接受utf8字符串

};

/************************************************************************/
/* 序列化的接口，统一二进制与Json序列化方式                                  */
/************************************************************************/
struct ISerialize
{
public://缓冲区设置函数
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeType
	// 函数参数：
	//					iSerializeType	[输入]		设置序列化方式
	// 返 回 值：
	// 函数说明：设置序列化方式
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializeType(EnumSerializeIO iSerializeType) = 0;

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
	// 函数名称：SetData
	// 函数参数：
	//					pstrText			[输入]		缓冲区
	//					ulDataLength		[输入]		缓冲区长度
	// 返 回 值：true or false
	// 函数说明：设置需要序列化读的缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, unsigned long ulDataLength) = 0;

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
	virtual unsigned long GetDataLen() = 0;
public://序列化结构体或者数组控制函数
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化一个结构体
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeStruct(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，当前的结构体已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeStruct(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArray
	// 函数参数：
	//					ulCount				[输入/输出]	列表的长度
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化一个列表，并设置/获取列表的长度
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArray(unsigned long &ulCount, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArray
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，当前的列表已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArray(const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化列表中的第N个元素
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArrayItem(unsigned long ulIndex, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，列表中的第N个元素已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArrayItem(unsigned long ulIndex, const char *pstrName) = 0;
public://序列化字段函数
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(bool& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数，这个表示字符
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(char& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned char& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(short& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned short& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(int& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned int& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long long& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(float& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(double& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long double& Value, const char *pstrName) = 0;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(std::string& Value, const char *pstrName) = 0;
};



