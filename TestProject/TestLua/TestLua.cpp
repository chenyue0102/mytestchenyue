// TestLua.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "LuaUtil.h"
#include "boost/lexical_cast.hpp"
#include <luabind/adopt_policy.hpp>
#include <Windows.h>
#include <string>

using namespace luabind;
void outputstring(const char *pstrText)
{
	printf(pstrText);
}

class CTest
{
public: 
	CTest():m_nValue(0)
	{
		printf("CTest constructor\n");
	}
	virtual ~CTest()
	{
		printf("CTest destructor\n");
	}
	void TestOutput(const char *pstr)
	{
		printf(pstr);
		printf("%d", m_nValue);
	}
	int	m_nValue;
};

extern "C" int luabind_outputstring(lua_State *l)
{
	luabind::module(l)
		[
			luabind::def("outputstring", &outputstring)
		];
	return 0;
}

int getstring(int strValue)
{
	strValue = 99999;
	//strValue = "getstring";
	return 0;
}


void CallClassPointer(CTest *p, const char *pstr)
{
	return p->TestOutput(pstr);
}

template<typename T>
class CMyVector : public std::vector<T>
{
public:
	CMyVector()
	{
		printf("CMyVector\n");
	}
	virtual ~CMyVector()
	{
		printf("~CMyVector\n");
	}
	void Test()
	{
		printf("size=%u\n", size());
	}
	void push_back(const T &value)
	{
		const T *p = &value;
		return __super::push_back(value);
	}
	typedef void (CMyVector::*PushBackFunType)(const T &Value);
};

template<typename T>
void TestEnumVector(const CMyVector<T> &v)
{
	printf("TestEnumVector size=%u\n", v.size());
}

template<typename T>
void TestEnumVectorPointer(const CMyVector<T> *v)
{
	printf("TestEnumVector size=%u\n", v->size());
}

struct TestTLV
{
	DWORD	dwID;			// ����ID
	DWORD	dwType;			// ��������
	std::string 	strValue;		// ����ֵ
	
	TestTLV(const TestTLV &other)	//��������
	{
		printf("TestTLV\n");
		dwID = other.dwID;
		dwType = other.dwType;
		strValue = other.strValue;
	}
	TestTLV()//���캯��
	{
		printf("TestTLV\n");
	}
	~TestTLV()
	{
		printf("~TestTLV\n");
	}
	void TestTLV::SetDword(DWORD dwPropertyID, DWORD dwPropertyValue)
	{
		strValue.clear();
		dwID = dwPropertyID;
		dwType = 1;
		strValue.append((char*)&dwPropertyValue, sizeof(DWORD));
	}

	void TestTLV::SetString(DWORD dwPropertyID, const std::string &PropertyValue)
	{
		strValue.clear();
		dwID = dwPropertyID;
		dwType = 2;
		DWORD dwLen = (DWORD)strlen(PropertyValue.c_str()) + 1;
		strValue.append(PropertyValue.c_str(), dwLen);
	}

	bool operator==(const TestTLV &other)const
	{
		return false;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestLuaFun.lua");

	CLuaVM luaVM;
	
	if( 0 != luaL_dofile(luaVM, szLuaFileName))
	{
		return 1;
	}

	int nfirst = 1, nsecond = 2;
	int nResult = luabind::call_function<int>(luaVM, "testadd", nfirst, nsecond);
	std::string str = luabind::call_function<std::string>(luaVM, "teststring");

	luabind::object obj = luabind::call_function<luabind::object>(luaVM, "testable");
	std::string strValue;
	int nKey = 0;
	for(luabind::iterator i(obj); i != luabind::iterator(); ++i)
	{
		strValue = boost::lexical_cast<std::string>(*i);
		nKey = boost::lexical_cast<int>(i.key());
	}
	luabind_outputstring(luaVM);
	const char *pstrText = "kingmax";
	luabind::call_function<int>(luaVM, "testoutput", pstrText);

	luabind::module(luaVM)
		[
			luabind::def("getstring", &getstring)
		];

	//std::string strValue2;
	std::string strValue2;
	//luabind::call_function<int>(luaVM, "testquote", strValue2);

	module(luaVM)
		[
			class_<CTest>("CTest")
			.def(constructor<>())
			.def("ClassTestOutput", &CTest::TestOutput)
		];
	luabind::call_function<int>(luaVM, "LuaTestOutput");

	

	luabind::module(luaVM)
		[
			luabind::def("ClassPointerTestOutput", &CTest::TestOutput)
		];
	
	
	extern CTest* CreateText();
	luabind::module(luaVM)
		[
			luabind::def("CreateText", &CreateText, luabind::adopt(result))
		];
	extern void TestClassPointer(CTest *p);
	extern CTest& GetRef();
	/*luabind::module(luaVM)
		[
			luabind::def("TestClassPointer", &TestClassPointer),
			class_<CTest>("CTest")
			.def("GetRef", &GetRef, luabind::dependency(result,_1))
		];
	luabind::call_function<int>(luaVM, "LuaTestCreateText");*/

	luabind::module(luaVM)
	[
		class_<TestTLV>("TestTLV")
		.def(constructor<>())
		.def("SetDword", &TestTLV::SetDword)
		.def("SetString", &TestTLV::SetString)
	];

	luabind::module(luaVM)
	[
		luabind::def("TestEnumVector", &TestEnumVector<TestTLV>),
		luabind::def("TestEnumVectorPointer", &TestEnumVectorPointer<TestTLV>),
		class_<CMyVector<TestTLV> >("CMyVector")
		.def(constructor<>())
		.def("push_back",/* (CMyVector<TestTLV>::PushBackFunType)*/&CMyVector<TestTLV>::push_back)
		.def("Test", &CMyVector<TestTLV>::Test)
	];

	
	//luabind::call_function<void>(luaVM, "LuaTestVector");

	CMyVector<TestTLV> *pTemp = new CMyVector<TestTLV>;
	
	luabind::call_function<void>(luaVM, "LuaTestVectorParam", pTemp);
	int nSize = pTemp->size();
	printf("nsize=%d", nSize);
	pTemp->clear();
	delete pTemp;
	return 0;
}

CTest* CreateText()
{
	return new CTest;
}

void TestClassPointer(CTest *p)
{
	p->TestOutput("kef");
}

CTest& GetRef()
{
	static CTest c;
	return c;
}