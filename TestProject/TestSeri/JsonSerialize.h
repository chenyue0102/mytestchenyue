// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：JsonSerialize.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化类,将数据读出或写入到Json，Json中，字符串格式为utf8
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <memory>
#include <stack>
#include "ISerialize.h"
#include "json.h"

/************************************************************************/
/* 序列化到Json格式类                                                     */
/************************************************************************/
class CJsonSerialize
	: public ISerialize
{
public:
	CJsonSerialize();
	virtual ~CJsonSerialize();
public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializationType
	// 函数参数：
	//					iSerializationType	[输入]		设置序列化方式
	// 返 回 值：
	// 函数说明：设置序列化方式
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializationType
	// 函数参数：
	// 返 回 值：序列化方式
	// 函数说明：获取序列化方式
	// $_FUNCTION_END *********************************************************
	virtual ENUM_SERIALIZATION_TYPE GetSerializationType()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeFormat
	// 函数参数：
	// 返 回 值：序列化的格式
	// 函数说明：获取序列化的格式
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeFormat GetSerializeFormat()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetData
	// 函数参数：
	//					pstrText			[输入]		缓冲区，字符串格式为utf8
	//					ulDataLength		[输入]		缓冲区长度
	// 返 回 值：bool
	// 函数说明：设置需要序列化读的缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, unsigned long ulDataLength)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetData
	// 函数参数：
	// 返 回 值：序列化缓冲区，字符串格式为utf8
	// 函数说明：获取序列化缓冲区
	// $_FUNCTION_END *********************************************************
	virtual const char* GetData()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetDataLen
	// 函数参数：
	// 返 回 值：序列化缓冲区长度
	// 函数说明：获取序列化缓冲区长度
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetDataLen()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerlizeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化一个结构体
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeStruct(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerlizeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，当前的结构体已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeStruct(const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerlizeArray
	// 函数参数：
	//					ulCount				[输入/输出]	列表的长度
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化一个列表，并设置/获取列表的长度
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArray(unsigned long &ulCount, const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerlizeArray
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，当前的列表已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArray(const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerlizeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化列表中的第N个元素
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerlizeArrayItem(unsigned long ulIndex, const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerlizeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：
	// 函数说明：告诉序列化模块，列表中的第N个元素已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerlizeArrayItem(unsigned long ulIndex, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(bool& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：iValue		[输入]	有符号整型
	// 返 回 值：
	// 函数说明：序列化有符号整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(int& iValue, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned int& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(unsigned long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(float& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerlizeArrayItem
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数，字符串格式为utf8
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialization(std::string& Value, const char *pstrName)override;
private:
	void CheckWriteToBuffer();
	void Log(const char* apFormat, ...);
private:
	// 序列化类型
	ENUM_SERIALIZATION_TYPE	m_iSerializationType;
	//Json根节点
	std::shared_ptr<Json::Value> m_pRootValue;
	//Json当前的节点
	std::shared_ptr<Json::Value> m_pCurValue;
	//递归已经入栈的节点
	std::stack<std::shared_ptr<Json::Value>> m_StackValue;
	//序列化结果缓冲区
	std::string	m_strBuffer;
	//是否已经将结果打入缓冲区了。
	bool		m_bHaveWriteToBuffer;
};