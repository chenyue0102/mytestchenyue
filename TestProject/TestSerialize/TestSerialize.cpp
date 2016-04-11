// TestSerialize.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ISerialize.h"
#include "SerializeImp.h"
#include "Serialize.h"
#include <atlcomcli.h>

struct TestInner
{
	std::string strText;

	bool Serialize(ISerialize *pSerialize)
	{
		try
		{
			SerializeImp(pSerialize, strText, "strText");
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
};

struct Test
{
	bool bValue;
	std::vector<unsigned long> Keys;
	std::string strValue;
	TestInner inner;

	bool Serialize(ISerialize *pSerialize)
	{
		try
		{
			SerializeImp(pSerialize, bValue, "bValue");
			SerializeImp(pSerialize, Keys, "Keys");
			SerializeImp(pSerialize, strValue, "strValue");
			SerializeImp(pSerialize, inner, "inner");
		}
		catch(...)
		{
			return false;
		}
		return true;
	}
};
class CTestSer : public CUnknownImp<ISerialize>
{
public:
	CTestSer();
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetSerializeType
	// 函数参数：
	// 返 回 值：当前序列化所对应的类型，参照枚举EnumSerializeType
	// 函数说明：获取当前序列化所对应的类型
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeType GetSerializeType()
	{
		return EnumSerializeTypeWrite;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeType
	// 函数参数：
	//			 SerializeType		[输入]	序列化类型
	// 返 回 值：true or false
	// 函数说明：设置当前序列化所对应的类型
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeType SerializeType)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetSerializeReadBuffer
	// 函数参数：
	//			 pBuffer			[输入]	缓冲区
	//			 ulBufferLength		[输入]	缓冲区长度
	// 返 回 值：true or false
	// 函数说明：设置序列化读取的缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeReadBuffer(const void *pBuffer, unsigned long ulBufferLength)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetWriteBuffer
	// 函数参数：
	// 返 回 值：缓冲区地址
	// 函数说明：获取写序列化缓冲区
	// $_FUNCTION_END *********************************************************
	virtual const void * GetWriteBuffer()
	{
		return nullptr;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GetWriteBufferLength
	// 函数参数：
	// 返 回 值：缓冲区长度
	// 函数说明：获取写序列化缓冲区长度
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetWriteBufferLength()
	{
		return 0;
	}
public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化bool
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化unsigned long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化float
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 Value				[输入/输出]	被序列化的值
	// 返 回 值：true or false
	// 函数说明：序列化double
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Serialize
	// 函数参数：
	//			 pBuffer			[输入/输出]	被序列化的缓冲区
	//			 ulBufferLen		[输入]	被序列化的缓冲区长度
	// 返 回 值：true or false
	// 函数说明：序列化缓冲区
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(void *pBuffer, unsigned long ulBufferLen, const char *psrName)
	{
		return true;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CTestSer c;

	/*Test t;
	t.Keys.push_back(1);
	t.Keys.push_back(2);
	t.strValue = "abc123";
	t.inner.strText = "1";
	CComPtr<ISerialize> pSerialize(new CSerialize);
	pSerialize->SetSerializeType(EnumSerializeTypeWrite);
	t.Serialize(pSerialize);

	Test t2;
	CComPtr<ISerialize> pSerializeRead(new CSerialize);
	pSerializeRead->SetSerializeType(EnumSerializeTypeRead);
	pSerializeRead->SetSerializeReadBuffer(pSerialize->GetWriteBuffer(), pSerialize->GetWriteBufferLength());
	t2.Serialize(pSerializeRead);*/
	return 0;
}

