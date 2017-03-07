#pragma once
#include <string>
#include <vector>
#include <codecvt>
#include <assert.h>
#include <Windows.h>
#include "InterfaceSerialize.h"
#include "TKSerializeExport.h"
#include "SerializeHelperEx.h"
#include "tkptrlist.h"
#ifdef QT_CORE_LIB
#include <QString>
#endif

namespace SerializeExport
{
	struct ISerialize;
}
using namespace SerializeExport;

inline std::wstring UTF8ToWChar(const std::string &strUtf8)
{
	std::wstring_convert<std::codecvt_utf8 <wchar_t >, wchar_t> utf8_wstr_cvt;
	std::wstring strw = utf8_wstr_cvt.from_bytes(strUtf8);
	return strw;
}

template<typename T>
bool operator==(const CTKPtrList<T> &left, const CTKPtrList<T> &right)
{
	if (left.GetCount() != right.GetCount())
	{
		return false;
	}
	for (int a = 0; a < left.GetCount(); a++)
	{
		if (!(*left.GetAt(a) == *right.GetAt(a)))
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool operator==(const std::vector<T> &left, const std::vector<T> &right)
{
	if (left.size() != right.size())
	{
		return false;
	}
	for (size_t a = 0; a < left.size(); a++)
	{
		if (!(left[a] == right[a]))
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool operator==(const std::vector<T*> &left, const std::vector<T*> &right)
{
	if (left.size() != right.size())
	{
		return false;
	}
	for (size_t a = 0; a < left.size(); a++)
	{
		if (!((*left[a]) == (*right[a])))
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool CompareArray(const T leftArray[], const T rightArray[], size_t stCount)
{
	for (size_t nIndex = 0; nIndex < stCount; ++nIndex)
	{
		if (!(leftArray[nIndex] == rightArray[nIndex]))
		{
			return false;
		}
	}
	return true;
}

template<typename T>
void DoTest(ISerialize & pSerializeWrite, ISerialize & pSerializeRead)
{
	T AllTypeWrite;
	AllTypeWrite.init();
	pSerializeWrite.SetSerializeType(EnumSerializeIOWrite);
	AllTypeWrite.Serialize(pSerializeWrite);

	std::string strBuffer(pSerializeWrite.GetData(), pSerializeWrite.GetDataLen());
#ifdef _DEBUG
	std::wstring strWText;
	if (pSerializeWrite.GetSerializeFormat() == EnumSerializeFormatJson
		|| pSerializeWrite.GetSerializeFormat() == EnumSerializeFormatXml)
	{
		strWText = UTF8ToWChar(strBuffer);
	}
#endif

	pSerializeRead.SetSerializeType(EnumSerializeIORead);
	pSerializeRead.SetData(strBuffer.data(), strBuffer.size());
	T AllTypeRead;
	AllTypeRead.Serialize(pSerializeRead);

	assert(AllTypeWrite == AllTypeRead);
}

template<typename T>
void DoTest2(ISerialize & pSerializeWrite, ISerialize & pSerializeRead)
{
	T AllTypeWrite;
	AllTypeWrite.init();
	pSerializeWrite.SetSerializeType(EnumSerializeIOWrite);
	if (!SerializeStruct(pSerializeWrite, AllTypeWrite))
	{
		assert(false);
	}

	std::string strBuffer(pSerializeWrite.GetData(), pSerializeWrite.GetDataLen());
#ifdef _DEBUG
	std::wstring strWText;
	if (pSerializeWrite.GetSerializeFormat() == EnumSerializeFormatJson)
	{
		strWText = UTF8ToWChar(strBuffer);
	}
#endif

	pSerializeRead.SetSerializeType(EnumSerializeIORead);
	pSerializeRead.SetData(strBuffer.data(), strBuffer.size());
	T AllTypeRead;
	if (!SerializeStruct(pSerializeRead, AllTypeRead))
	{
		assert(false);
	}

	assert(AllTypeWrite == AllTypeRead);
}

void DoTestMiss(ISerialize & pSerializeWrite, ISerialize & pSerializeRead);

struct TestAllType
{
	bool b;
	char c;
	unsigned char uc;
	short s;
	unsigned short us;
	int i;
	unsigned int ui;
	long l;
	unsigned long ul;
	long long ll;
	unsigned long long ull;
	float f;
	double d;
	long double ld;
	std::string strUtf8;
	std::string strGB2312;
	std::string strBinary;		//存储二进制数据
	char	szText[32];
	int		Keys[4];
#ifdef QT_CORE_LIB
	QString strQString;
#endif

	TestAllType()
	{
		b = false;
		c = '\0';
		uc = 0;
		s = 0;
		us = 0;
		i = 0;
		ui = 0;
		l = 0;
		l = 0;
		ll = 0;
		ull = 0;
		f = 0.0f;
		d = 0.0;
		ld = 0.0;
		//ss;
		//strBinary;		//存储二进制数据
		memset(szText, 0, sizeof(szText));
		memset(Keys, 0, sizeof(Keys));
		//strQString
	}
	void init();
	BOOL Serialize(ISerialize &pSerialize);
	bool operator==(const TestAllType &other)const;
};

bool SerializeStruct(ISerialize &pSerialize, TestAllType &Value);

struct TestStruct
{
	int id;
	std::string strValue;

	TestStruct()
	{
		id = 0;
	}
	void init();
	BOOL Serialize(ISerialize &pSerialize);
	bool operator==(const TestStruct &other)const;
};

bool SerializeStruct(ISerialize &pSerialize, TestStruct &Value);

struct TestArray
{
	int idarray;
	TestStruct ts;
	std::vector<int> vt;
	std::vector<std::vector<std::string>> vvs;
	std::vector<TestStruct> vts;
	std::vector<std::vector<TestStruct>> vvts;
	TestStruct tsArray[3];
	std::vector<int> vtArray[3];

	TestArray()
	{
		idarray = 0;
	}
	void init();
	BOOL Serialize(ISerialize &pSerialize);
	bool operator==(const TestArray &other)const;
};

bool SerializeStruct(ISerialize &pSerialize, TestArray &Value);

struct TestContainer
{
	int idcontainer;
	TestStruct ts;
	TestArray ta;

	TestContainer()
	{
		idcontainer = 0;
	}
	void init();
	BOOL Serialize(ISerialize &pSerialize);
	bool operator==(const TestContainer &other)const;
};

bool SerializeStruct(ISerialize &pSerialize, TestContainer &Value);

struct TestMiss
{
	int nID;
	CTKPtrList<std::string> vtKey;
	std::vector<std::string*> vtMiss;
	std::string strValue;

	TestMiss()
	{
		nID = 0;
	}
	void init();
	BOOL Serialize(ISerialize &pSerialize);
	bool operator==(const TestMiss &other)const
	{
		return (
			nID == other.nID
			&& vtKey == other.vtKey
			&& vtMiss == other.vtMiss
			&& strValue == other.strValue
			);
	}
};

bool SerializeStruct(ISerialize &pSerialize, TestMiss &Value);

inline void Test(EnumSerializeFormat SerializeFormat)
{
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest<TestAllType>(*pSerializeWrite, *pSerializeRead);
	}
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest<TestContainer>(*pSerializeWrite, *pSerializeRead);
	}
}

inline void Test2(EnumSerializeFormat SerializeFormat)
{
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest2<TestAllType>(*pSerializeWrite, *pSerializeRead);
	}
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest2<TestContainer>(*pSerializeWrite, *pSerializeRead);
	}
}

inline void Test3(EnumSerializeFormat SerializeFormat)
{
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
	DoTestMiss(*pSerializeWrite, *pSerializeRead);
}