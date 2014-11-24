// TestLua.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LuaUtil.h"
#include "boost/lexical_cast.hpp"
#include <luabind/adopt_policy.hpp>
#include <string>
#include "luabind/operator.hpp"
#include <map>
#include "IText.h"
#include "luabind/error.hpp"
#include "teststl.h"

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
	iterator erase(const_iterator _Where)
	{
		return __super::erase(_Where);
	}
	iterator insert(const_iterator _Where, const T& _Val)
	{
		return __super::insert(_Where, _Val);
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

void InitTlvValue(TestTLV &value)
{
	const TestTLV *p = &value;
	value.SetString(98765, "InitTlvValue");
}

BOOL GetTlvValue(const CMyVector<TestTLV> &Array, DWORD dwID, TestTLV &value)
{
	BOOL bRes = FALSE;
	for (CMyVector<TestTLV>::const_iterator itor = Array.begin(); itor != Array.end(); ++itor)
	{
		if (itor->dwID == dwID)
		{
			value = *itor;
			bRes = TRUE;
			break;
		}
	}
	return bRes;
}

void LuaErrorCallbackFun(lua_State* e)
{
	const char *pstrError = lua_tostring(e, -1);
	printf(pstrError);
}

int _tmain(int argc, _TCHAR* argv[])
{
	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestLuaFun.lua");

	{
		CLuaVM luaVM;

		luabind::set_error_callback(&LuaErrorCallbackFun);
		extern void RegisterTestSharePointer(lua_State *luaVM);
		RegisterTestSharePointer(luaVM);
		
		if( 0 != luaL_dofile(luaVM, szLuaFileName))
		{
			return 1;
		}
		
		int nfirst = 1, nsecond = 2;
		//int nResult = luabind::call_function<int>(luaVM, "testadd", nfirst, nsecond);
		//std::string str = luabind::call_function<std::string>(luaVM, "teststring");

		/*luabind::object obj = luabind::call_function<luabind::object>(luaVM, "testable");
		std::string strValue;
		int nKey = 0;
		for(luabind::iterator i(obj); i != luabind::iterator(); ++i)
		{
		strValue = boost::lexical_cast<std::string>(*i);
		nKey = boost::lexical_cast<int>(i.key());
		}*/
		luabind_outputstring(luaVM);
		const char *pstrText = "kingmax";
		//luabind::call_function<int>(luaVM, "testoutput", pstrText);

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
		//luabind::call_function<int>(luaVM, "LuaTestOutput");



		luabind::module(luaVM)
			[
				luabind::def("ClassPointerTestOutput", &CTest::TestOutput)
			];


		extern CTest* CreateText();
		luabind::module(luaVM)
			[
				luabind::def("CreateText", &CreateText, luabind::adopt(result))			//lua会释放此指针
			];
		extern void TestClassPointer(CTest *p);
		extern CTest& GetRef();
		luabind::module(luaVM)
			[
				luabind::def("TestClassPointer", &TestClassPointer)
				/*class_<CTest>("CTest")
				.def("GetRef", &GetRef, luabind::dependency(result,_1))*/
			];
		//luabind::call_function<int>(luaVM, "LuaTestCreateText");
		//lua_gc(luaVM, LUA_GCSETPAUSE, 100);
		//lua_gc(luaVM, LUA_GCSETSTEPMUL, 100);
		luabind::module(luaVM)
			[
				class_<TestTLV>("TestTLV")
				.def(constructor<>())
				.def("SetDword", &TestTLV::SetDword)
				.def("SetString", &TestTLV::SetString)
				.def("Test", &TestTLV::Test)
				.def(self == other<TestTLV>())		//TestTLV变量在lua中可以执行比较操作
			];
		luabind::module(luaVM)
			[
				luabind::def("InitTlvValue", &InitTlvValue),
				luabind::def("GetTlvValue", &GetTlvValue)
			];

		luabind::module(luaVM)
			[
				class_<CMyVector<TestTLV>::const_iterator >("const_iterator")
				.def(constructor<>())
				.def(self == other<CMyVector<TestTLV>::const_iterator>())		//变量在lua中可以执行比较操作
				.def("increment", (CMyVector<TestTLV>::const_iterator&(CMyVector<TestTLV>::const_iterator::*)())&(CMyVector<TestTLV>::const_iterator::operator++))
				.def("GetValue", &(CMyVector<TestTLV>::const_iterator::operator *))
			];

		luabind::module(luaVM)
			[
				class_<CMyVector<TestTLV>::iterator, CMyVector<TestTLV>::const_iterator>("iterator")
				.def(constructor<>())
				.def(self == other<CMyVector<TestTLV>::iterator>())		//变量在lua中可以执行比较操作
				.def("increment", (CMyVector<TestTLV>::iterator&(CMyVector<TestTLV>::iterator::*)())&(CMyVector<TestTLV>::iterator::operator++))
				.def("GetValue", &(CMyVector<TestTLV>::iterator::operator *))
			];

		luabind::module(luaVM)
			[
				luabind::def("TestEnumVector", &TestEnumVector<TestTLV>),
				luabind::def("TestEnumVectorPointer", &TestEnumVectorPointer<TestTLV>),
				class_<CMyVector<TestTLV> >("CMyVector")
				.def(constructor<>())
				.def("push_back",/* (CMyVector<TestTLV>::PushBackFunType)*/&CMyVector<TestTLV>::push_back)
				.def("Test", &CMyVector<TestTLV>::Test)
				.def("Begin", (CMyVector<TestTLV>::iterator(CMyVector<TestTLV>::*)())&CMyVector<TestTLV>::begin)
				.def("End", (CMyVector<TestTLV>::iterator(CMyVector<TestTLV>::*)())&CMyVector<TestTLV>::end)
				.def("Erase", (CMyVector<TestTLV>::iterator(CMyVector<TestTLV>::*)(CMyVector<TestTLV>::const_iterator))
				&CMyVector<TestTLV>::erase)
				.def("Insert", (CMyVector<TestTLV>::iterator 
				(CMyVector<TestTLV>::*)
				(CMyVector<TestTLV>::const_iterator _Where, const TestTLV& _Val))
				&CMyVector<TestTLV>::insert)
			];


		//luabind::call_function<void>(luaVM, "LuaTestVector");

		CMyVector<TestTLV> *pTemp = new CMyVector<TestTLV>;
		//luabind::call_function<void>(luaVM, "LuaTestVectorParam", pTemp);
		int nSize = pTemp->size();
		printf("nsize=%d", nSize);

		for (int a = 1; a < 10;a++)
		{
			TestTLV t1;
			t1.SetDword(a,a);
			pTemp->push_back(t1);
		}


		//luabind::call_function<void>(luaVM, "LuaTestiterator", pTemp);

		ITest *pITest = NULL;
		//luabind::call_function<void>(luaVM, "LuaTestInterface", pITest);

		luabind::module(luaVM)
			[
				luabind::def("CreateITest", &CreateITest, luabind::dependency(result,_1)),		//引用形式，lua不管释放指针
				luabind::def("CreateITest2", &CreateITest2, luabind::dependency(result,_1))	//引用形式，lua不管释放指针
			];

		luabind::module(luaVM)
			[
				class_<test_wrapper>("test_wrapper")
				.def(constructor<int>())
				.def("Test", &test_wrapper::Test)
			];
		//luabind::call_function<void>(luaVM, "LuaTestInterface2");

		//luabind::call_function<void>(luaVM, "LuaTestInsertErase", pTemp);

		pTemp->clear();
		delete pTemp;

		//TestStl(luaVM);

		extern void TestSharePointer(lua_State *luaVM);
		TestSharePointer(luaVM);	
	}
	assert(0 == TestTLV::g_lCount);
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