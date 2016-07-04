// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：Serialize.h
// 创建日期：2012-02-28
// 创建人：罗俊杰
// 文件说明：序列化类,将数据读出或写入到内存
// $_FILEHEADER_END ***********************************************************

#ifndef Serialize_H
#define Serialize_H

#include "Typedef.h"
#include <string>
#include <vector>
#include "ISerialize.h"

class CBinarySerialize
	: public ISerialize
{
	// 缓存创建类型
	enum ENUM_BUFFER_CREATE_TYPE
	{
		enum_Buffer_Create_Type_Inside,		// 内部创建
		enum_Buffer_Create_Type_OutSide,	// 外部创建
	};
public:
	CBinarySerialize();
	~CBinarySerialize();
public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeType
	// 函数参数：iSerializeType		[输入]	序列化类型
	// 返 回 值：
	// 函数说明：设置序列化类型
	// $_FUNCTION_END *********************************************************
	virtual void SetSerializeType(EnumSerializeIO iSerializeType)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeType
	// 函数参数：
	// 返 回 值：序列化类型
	// 函数说明：获取序列化类型
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
	// 函数名称：SetData
	// 函数参数：
	//					pstrText			[输入]		缓冲区
	//					ulDataLength		[输入]		缓冲区长度
	// 返 回 值：true or false
	// 函数说明：设置需要序列化读的缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool SetData(const char *pstrText, unsigned long ulDataLength)override;
public://序列化字段函数
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：bValue		[输入]	bool类型
	// 返 回 值：
	// 函数说明：序列化bool类型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(bool& bValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：cValue		[输入]	字符
	// 返 回 值：
	// 函数说明：序列化无符号字符
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(char& cValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：byValue		[输入]	无符号字符
	// 返 回 值：
	// 函数说明：序列化无符号字符
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned char& byValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：sValue		[输入]	有符号短整型
	// 返 回 值：
	// 函数说明：序列化有符号短整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：sValue		[输入]	无符号短整型
	// 返 回 值：
	// 函数说明：序列化无符号短整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned short& sValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：iValue		[输入]	有符号整型
	// 返 回 值：
	// 函数说明：序列化有符号整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：iValue		[输入]	无符号整型
	// 返 回 值：
	// 函数说明：序列化无符号整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned int& iValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：lValue		[输入]	有符号长整型
	// 返 回 值：
	// 函数说明：序列化有符号长整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：lValue		[输入]	无符号长整型
	// 返 回 值：
	// 函数说明：序列化无符号长整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long& lValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：i64Value		[输入]	64位长整型
	// 返 回 值：
	// 函数说明：序列化64位长整型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long long& i64Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//					Value				[输入/输出]	需要序列化的参数
	// 返 回 值：
	// 函数说明：序列化变量
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(unsigned long long& Value, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：fValue		[输入]	单精度类型
	// 返 回 值：
	// 函数说明：序列化单精度类型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(float& fValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：dValue		[输入]	双精度类型
	// 返 回 值：
	// 函数说明：序列化双精度类型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(double& dValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：dValue		[输入]	双精度类型
	// 返 回 值：
	// 函数说明：序列化双精度类型
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(long double& ldValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：strValue		[输入]	字符串
	// 返 回 值：
	// 函数说明：序列化字符串
	// $_FUNCTION_END *********************************************************
	virtual void Serialize(std::string& strValue, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetData
	// 函数参数：
	// 返 回 值：数据
	// 函数说明：取得数据
	// $_FUNCTION_END *********************************************************
	virtual const char* GetData()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetDataLen
	// 函数参数：
	// 返 回 值：数据长度
	// 函数说明：取得数据长度
	// $_FUNCTION_END *********************************************************
	virtual DWORD GetDataLen()override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeStruct
	// 函数参数：
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化一个结构体
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeStruct
	// 函数参数：
	// 返 回 值：
	// 函数说明：告诉序列化模块，当前的结构体已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeStruct(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArray
	// 函数参数：
	//					ulCount				[输入/输出]	列表的长度
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化一个列表，并设置/获取列表的长度
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArray(unsigned long &ulCount, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArray
	// 函数参数：
	// 返 回 值：
	// 函数说明：告诉序列化模块，当前的列表已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArray(const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：BeginSerializeArrayItem
	// 函数参数：
	// 返 回 值：
	// 函数说明：告诉序列化模块，接下来要序列化列表中的第N个元素
	// $_FUNCTION_END *********************************************************
	virtual void BeginSerializeArrayItem(unsigned long, const char *)override;

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：EndSerializeArrayItem
	// 函数参数：
	// 返 回 值：
	// 函数说明：告诉序列化模块，列表中的第N个元素已经序列化完成
	// $_FUNCTION_END *********************************************************
	virtual void EndSerializeArrayItem(unsigned long, const char *)override;
private:
	//禁用拷贝构造与赋值
	CBinarySerialize(const CBinarySerialize &rhs);
	const CBinarySerialize& operator=(const CBinarySerialize &rhs);
private:
	// 序列化类型
	EnumSerializeIO	m_iSerializeType;

	// 缓存创建类型
	ENUM_BUFFER_CREATE_TYPE	m_iBufferCreateType;

	// 缓存
	char*			m_pBuffer;

	// 缓存长度
	DWORD			m_dwBufferLen;

	// 数据长度
	DWORD			m_dwDataLen;
};

#endif