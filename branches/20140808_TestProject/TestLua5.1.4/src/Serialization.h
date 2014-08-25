// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：Serialization.h
// 创建日期：2012-02-28
// 创建人：罗俊杰
// 文件说明：序列化类,将数据读出或写入到内存
// $_FILEHEADER_END ***********************************************************

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <string>
using namespace std;

// 序列化类型
enum ENUM_SERIALIZATION_TYPE
{
	enum_Serialization_Type_Default,	// 默认值
	enum_Serialization_Type_Read,		// 读取数据
	enum_Serialization_Type_Write,		// 写入数据
};

// 缓存创建类型
enum ENUM_BUFFER_CREATE_TYPE
{
	enum_Buffer_Create_Type_Inside,		// 内部创建
	enum_Buffer_Create_Type_OutSide,	// 外部创建
};

class CSerialization
{
public:
	CSerialization();
	CSerialization(char* pBuffer, DWORD dwBufferLen);
	CSerialization(std::string &strBuffer);
	~CSerialization();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializationType
	// 函数参数：iSerializationType		[输入]	序列化类型
	// 返 回 值：
	// 函数说明：设置序列化类型
	// $_FUNCTION_END *********************************************************
	void SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializationType
	// 函数参数：
	// 返 回 值：序列化类型
	// 函数说明：获取序列化类型
	// $_FUNCTION_END *********************************************************
	ENUM_SERIALIZATION_TYPE GetSerializationType();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：byValue		[输入]	无符号字符
	// 返 回 值：
	// 函数说明：序列化无符号字符
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned char& byValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：bValue		[输入]	bool类型
	// 返 回 值：
	// 函数说明：序列化bool类型
	// $_FUNCTION_END *********************************************************
	void Serialization(bool& bValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：sValue		[输入]	有符号短整型
	// 返 回 值：
	// 函数说明：序列化有符号短整型
	// $_FUNCTION_END *********************************************************
	void Serialization(short& sValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：sValue		[输入]	无符号短整型
	// 返 回 值：
	// 函数说明：序列化无符号短整型
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned short& sValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：iValue		[输入]	有符号整型
	// 返 回 值：
	// 函数说明：序列化有符号整型
	// $_FUNCTION_END *********************************************************
	void Serialization(int& iValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：iValue		[输入]	无符号整型
	// 返 回 值：
	// 函数说明：序列化无符号整型
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned int& iValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：lValue		[输入]	有符号长整型
	// 返 回 值：
	// 函数说明：序列化有符号长整型
	// $_FUNCTION_END *********************************************************
	void Serialization(long& lValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：lValue		[输入]	无符号长整型
	// 返 回 值：
	// 函数说明：序列化无符号长整型
	// $_FUNCTION_END *********************************************************
	void Serialization(unsigned long& lValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：i64Value		[输入]	64位长整型
	// 返 回 值：
	// 函数说明：序列化64位长整型
	// $_FUNCTION_END *********************************************************
	void Serialization(long long& i64Value);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：fValue		[输入]	单精度类型
	// 返 回 值：
	// 函数说明：序列化单精度类型
	// $_FUNCTION_END *********************************************************
	void Serialization(float& fValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：dValue		[输入]	双精度类型
	// 返 回 值：
	// 函数说明：序列化双精度类型
	// $_FUNCTION_END *********************************************************
	void Serialization(double& dValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：pValue			[输入]	字符串
	//			 dwValueLen		[输入]	字符串长度
	//			 dwDataLen		[输入]	数据长度
	// 返 回 值：
	// 函数说明：序列化字符串
	// $_FUNCTION_END *********************************************************
	void Serialization(char* pValue, DWORD dwValueLen, DWORD dwDataLen);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialization
	// 函数参数：strValue		[输入]	字符串
	// 返 回 值：
	// 函数说明：序列化字符串
	// $_FUNCTION_END *********************************************************
	void Serialization(string& strValue);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetData
	// 函数参数：
	// 返 回 值：数据
	// 函数说明：取得数据
	// $_FUNCTION_END *********************************************************
	char* GetData();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetDataLen
	// 函数参数：
	// 返 回 值：数据长度
	// 函数说明：取得数据长度
	// $_FUNCTION_END *********************************************************
	DWORD GetDataLen();

	void ToBuffer(std::string &strBuffer);
private:
	// 序列化类型
	ENUM_SERIALIZATION_TYPE	m_iSerializationType;

	// 缓存创建类型
	ENUM_BUFFER_CREATE_TYPE	m_iBufferCreateType;

	// 缓存
	char*			m_pBuffer;

	// 缓存长度
	DWORD			m_dwBufferLen;

	// 数据长度
	DWORD			m_dwDataLen;
	std::string			m_strBuffer;
};

#endif