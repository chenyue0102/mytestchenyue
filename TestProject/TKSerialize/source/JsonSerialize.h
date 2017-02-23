// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：JsonSerialize.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化类,将数据读出或写入到Json，Json中，字符串格式为utf8
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <memory>
#include <stack>
#include "InterfaceSerialize.h"
#include "json.h"

namespace SerializeExport
{
	class CSerializeString;
}
using namespace SerializeExport;
/************************************************************************/
/* 序列化到Json格式类                                                     */
/************************************************************************/
class CJsonSerialize
	: public SerializeExport::ISerialize
{
public:
	CJsonSerialize();
	virtual ~CJsonSerialize();
public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeType
	// 函数参数：
	//					iSerializeType	[输入]		设置序列化方式
	// 返 回 值：true or false
	// 函数说明：设置序列化方式
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeIO iSerializeType)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeType
	// 函数参数：
	// 返 回 值：序列化方式
	// 函数说明：获取序列化方式
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeIO GetSerializeType()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeFormat
	// 函数参数：
	// 返 回 值：序列化的格式
	// 函数说明：获取序列化的格式
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeFormat GetSerializeFormat()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeStringCode
	// 函数参数：
	//					SerializeStringCode	[输入]		设置std::string字符串编码，默认是EnumSerializeStringCodeNone
	// 返 回 值：true or false
	// 函数说明：设置std::string字符串编码，
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeStringCode(EnumSerializeStringCode SerializeStringCode)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeStringCode
	// 函数参数：
	// 返 回 值：
	// 函数说明：获取std::string字符串编码，
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeStringCode GetSerializeStringCode()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetData
	// 函数参数：
	//					pstrText			[输入]		缓冲区，字符串格式为utf8
	//					ulDataLength		[输入]		缓冲区长度
	// 返 回 值：true or false
	// 函数说明：设置需要序列化读的缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, suint32 ulDataLength)override;

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
	virtual suint32 GetDataLen()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，接下来要序列化一个结构体
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeStruct(const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeStruct
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，当前的结构体已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeStruct(const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArray
	// 函数参数：
	//					ulCount				[输入/输出]	列表的长度
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，接下来要序列化一个列表，并设置/获取列表的长度
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArray(suint32 &ulCount, const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArray
	// 函数参数：
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，当前的列表已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArray(const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，接下来要序列化列表中的第N个元素
	// $_FUNCTION_END *********************************************************
	virtual bool BeginSerializeArrayItem(suint32 ulIndex, const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，列表中的第N个元素已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArrayItem(suint32 ulIndex, const char *pstrName)override;
public://序列化字段函数
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool& Value, const char *pstrName)override;
	
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数，这个表示字符
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：iValue		[输入]	有符号整型
	// 返 回 值：true or false
	// 函数说明：序列化有符号整型
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int& iValue, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long double& Value, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数，字符串格式为utf8
	//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
	// 返 回 值：true or false
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(CSerializeString& Value, const char *pstrName)override;
private:
	void CheckWriteToBuffer();
	void Log(const char* apFormat, ...);
	//将字符串转换为utf8格式
	std::string ConvertToJson(const std::string &strText);
	std::string ConvertToLocal(const std::string &strText);
private:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ConverToType
	// 函数参数：
	//					JsonValue			[输入]		Json对象
	//					Value				[输出]		Json对象，翻译成指定格式
	//					pstrName			[输入]		对象名称，打印错误Log使用
	// 返 回 值：true or false
	// 函数说明：Json对象，翻译成指定格式
	// $_FUNCTION_END *********************************************************
	bool ConverToType(Json::Value &JsonValue, CSerializeString &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, bool &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, int &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, unsigned int &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, long long &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, unsigned long long &Value, const char *pstrName);
	bool ConverToType(Json::Value &JsonValue, double &Value, const char *pstrName);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ConverToString
	// 函数参数：
	//					Value				[输入]		需要存储到Json中的数据
	// 返 回 值：Json对象
	// 函数说明：将指定格式的数据，翻译为Json对象
	// $_FUNCTION_END *********************************************************
	Json::Value ConverToJsonValue(CSerializeString &Value);
	Json::Value ConverToJsonValue(bool &Value);
	Json::Value ConverToJsonValue(int &Value);
	Json::Value ConverToJsonValue(unsigned int &Value);
	Json::Value ConverToJsonValue(long long &Value);
	Json::Value ConverToJsonValue(unsigned long long &Value);
	Json::Value ConverToJsonValue(double &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：InnerSerialize
	// 函数参数：
	//					Value				[输入/输出]		需要序列化的元素
	//					pstrName			[输入]			元素的名称
	// 返 回 值：
	// 函数说明：序列化指定格式的数据
	// $_FUNCTION_END *********************************************************
	template<typename T>
	bool InnerSerialize(T &Value, const char *pstrName);
private:
	// 序列化类型
	EnumSerializeIO	m_iSerializeType;
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
	//std::string字符串编码
	EnumSerializeStringCode m_SerializeStringCode;
};
