// TestSerialize.cpp : �������̨Ӧ�ó������ڵ㡣
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
	// �������ƣ�GetSerializeType
	// ����������
	// �� �� ֵ����ǰ���л�����Ӧ�����ͣ�����ö��EnumSerializeType
	// ����˵������ȡ��ǰ���л�����Ӧ������
	// $_FUNCTION_END *********************************************************
	virtual EnumSerializeType GetSerializeType()
	{
		return EnumSerializeTypeWrite;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeType
	// ����������
	//			 SerializeType		[����]	���л�����
	// �� �� ֵ��true or false
	// ����˵�������õ�ǰ���л�����Ӧ������
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeType(EnumSerializeType SerializeType)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetSerializeReadBuffer
	// ����������
	//			 pBuffer			[����]	������
	//			 ulBufferLength		[����]	����������
	// �� �� ֵ��true or false
	// ����˵�����������л���ȡ�Ļ�����
	// $_FUNCTION_END *********************************************************
	virtual bool SetSerializeReadBuffer(const void *pBuffer, unsigned long ulBufferLength)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetWriteBuffer
	// ����������
	// �� �� ֵ����������ַ
	// ����˵������ȡд���л�������
	// $_FUNCTION_END *********************************************************
	virtual const void * GetWriteBuffer()
	{
		return nullptr;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GetWriteBufferLength
	// ����������
	// �� �� ֵ������������
	// ����˵������ȡд���л�����������
	// $_FUNCTION_END *********************************************************
	virtual unsigned long GetWriteBufferLength()
	{
		return 0;
	}
public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�bool
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(bool &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(char &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned char
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned char &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(short &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned short
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned short &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(int &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned int
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned int &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(long long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�unsigned long long
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(unsigned long long &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�float
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(float &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 Value				[����/���]	�����л���ֵ
	// �� �� ֵ��true or false
	// ����˵�������л�double
	// $_FUNCTION_END *********************************************************
	virtual bool Serialize(double &Value, const char *psrName)
	{
		return true;
	}

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Serialize
	// ����������
	//			 pBuffer			[����/���]	�����л��Ļ�����
	//			 ulBufferLen		[����]	�����л��Ļ���������
	// �� �� ֵ��true or false
	// ����˵�������л�������
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

