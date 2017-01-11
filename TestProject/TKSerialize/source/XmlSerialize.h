// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：JsonSerialize.h
// 创建日期：2016-06-28
// 创建人：陈月
// 文件说明：序列化类,将数据读出或写入到Xml，字符串格式为utf8
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <stack>
#include "tinyxml.h"
#include "InterfaceSerialize.h"

namespace SerializeExport
{
	class CSerializeString;
}
using namespace SerializeExport;

class CXmlSerialize
	: public ISerialize
{
public:
	CXmlSerialize();
	~CXmlSerialize();
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
	virtual bool BeginSerializeArray(unsigned long &ulCount, const char *pstrName)override;

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
	virtual bool BeginSerializeArrayItem(unsigned long ulIndex, const char *pstrName)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	//					ulIndex				[输入]		当前要序列化元素在列表中的index
	//					pstrName			[输入]		此结构体的名字，nullptr表示没有名字
	// 返 回 值：true or false
	// 函数说明：告诉序列化模块，列表中的第N个元素已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual bool EndSerializeArrayItem(unsigned long ulIndex, const char *pstrName)override;
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
	// 返 回 值：true or false
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
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Log
	// 函数参数：
	//					apFormat			[输入]		打印日志
	// 返 回 值：
	// 函数说明：打印日志
	// $_FUNCTION_END *********************************************************
	void Log(const char * apFormat, ...);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetChildCount
	// 函数参数：
	//					pElement			[输入]		元素指针
	// 返 回 值：元素中子节点数量
	// 函数说明：获取元素中子节点数量
	// $_FUNCTION_END *********************************************************
	int GetChildCount(TiXmlElement *pElement);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：CheckWriteToBuffer
	// 函数参数：
	// 返 回 值：
	// 函数说明：确保将序列化的结果写入到缓存之中了
	// $_FUNCTION_END *********************************************************
	void CheckWriteToBuffer();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ConverToXml
	// 函数参数：
	//					strText				[输入]		待序列化的数据
	// 返 回 值：可以放置到xml字符串中的文字
	// 函数说明：将待序列化的数据转换成可以放置到xml字符串中的文字，结合m_SerializeStringCode做转换
	// $_FUNCTION_END *********************************************************
	std::string ConverToXml(const std::string &strText);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ConvertToLocal
	// 函数参数：
	//					strText				[输入]		xml中提取的文字
	// 返 回 值：序列化前的数据
	// 函数说明：将xml中提取的文字转换成序列化前的数据，结合m_SerializeStringCode做转换
	// $_FUNCTION_END *********************************************************
	std::string ConvertToLocal(const std::string &strText);
private:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ConverToType
	// 函数参数：
	//					pstrValue			[输入]		xml中存储的文字
	//					Value				[输出]		xml中存储的内容，翻译成指定格式
	// 返 回 值：true or false
	// 函数说明：xml中存储的内容，翻译成指定格式
	// $_FUNCTION_END *********************************************************
	bool ConverToType(const char *pstrValue, CSerializeString &Value);
	bool ConverToType(const char *pstrValue, bool &Value);
	bool ConverToType(const char *pstrValue, long long &Value);
	bool ConverToType(const char *pstrValue, unsigned long long &Value);
	bool ConverToType(const char *pstrValue, long double &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ConverToString
	// 函数参数：
	//					Value				[输入]		需要存储到xml中的数据
	// 返 回 值：xml中可以存储的内容
	// 函数说明：将指定格式的数据，翻译成xml中可以存储的内容
	// $_FUNCTION_END *********************************************************
	std::string ConverToString(CSerializeString &Value);
	std::string ConverToString(bool &Value);
	std::string ConverToString(long long &Value);
	std::string ConverToString(unsigned long long &Value);
	std::string ConverToString(long double &Value);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：InnerSerialize
	// 函数参数：
	//					Value				[输入/输出]		需要序列化的元素
	//					pstrName			[输入]			元素的名称
	// 返 回 值：true or false
	// 函数说明：序列化指定格式的数据
	// $_FUNCTION_END *********************************************************
	template<typename T>
	bool InnerSerialize(T &Value, const char *pstrName);
private:
	// 序列化类型，输入/输出
	EnumSerializeIO	m_iSerializeType;
	// xml文档对象
	TiXmlDocument m_XmlDocument;
	// xml根节点
	TiXmlElement *m_pRootValue;
	// xml当前节点
	TiXmlElement *m_pCurValue;
	// xml进入子节点后，会将当前节点保存到stack中
	std::stack<TiXmlElement*> m_StackValue;
	//序列化结果缓冲区
	std::string	m_strBuffer;
	//是否已经将结果打入缓冲区了。
	bool		m_bHaveWriteToBuffer;
	//std::string字符串编码
	EnumSerializeStringCode m_SerializeStringCode;
};

