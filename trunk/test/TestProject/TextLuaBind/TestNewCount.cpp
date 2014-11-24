#include "StdAfx.h"
#include "TestNewCount.h"
#include <assert.h>
#include <luabind/adopt_policy.hpp>		
#include <luabind/copy_policy.hpp>
#include "luabind/operator.hpp"
#include "luabind/return_reference_to_policy.hpp"
#include <luabind/discard_result_policy.hpp>

volatile long CTestNewCount::m_nCount = 0;


//return_reference_to��ʾ����ֵΪ����
#define DEF_REGISTER_CONST_ITERATOR(luaVM, classtype, regname, regnamespace) \
luabind::module(luaVM, #regnamespace)	\
[ \
class_<classtype::const_iterator>(#regname) \
.def(constructor<>()) \
.def(self == other<classtype::const_iterator>()) 		\
.def("Increment", (classtype::const_iterator&(classtype::const_iterator::*)())&(classtype::const_iterator::operator++), discard_result) \
.def("GetValue", &(classtype::const_iterator::operator *)/*, return_reference_to(_1)*/) \
]; \
\

//return_reference_to��ʾ����ֵΪ����iterator��const_iterator������
#define DEF_REGISTER_ITERATOR(luaVM, classtype, regname, regnamespace) \
luabind::module(luaVM, #regnamespace)	\
[ \
	class_<classtype::iterator, classtype::const_iterator >(#regname) \
	.def(constructor<>()) \
	.def(self == other<classtype::iterator>()) 		\
	.def("Increment", (classtype::iterator&(classtype::iterator::*)())&(classtype::iterator::operator++), discard_result) \
	.def("GetValue", &(classtype::iterator::operator *)/*, return_reference_to(_1)*/) \
]; \
\

#define DEF_REGISTER_VECTOR(luaVM, classtype, regname, regnamespace) \
luabind::module(luaVM, #regnamespace) \
[ \
	class_<classtype >(#regname) \
	.def(constructor<>()) \
	.def("PushBack", (void (classtype::*)(const classtype::value_type&))&classtype::push_back) \
	.def("Begin", (classtype::iterator(classtype::*)())&classtype::begin) \
	.def("End", (classtype::iterator(classtype::*)())&classtype::end) \
	.def("Clear", &classtype::clear) \
	.def("Erase", (classtype::iterator (classtype::*)(classtype::const_iterator))&classtype::erase) \
]; \
\

CTestNewCount* GetNewObject()	//��������Ȩת�ø�Lua
{
	return new CTestNewCount;
}


static CTestNewCount *g_pCTestNewCount = NULL;
CTestNewCount& GetSingleObject()		//����Ȩ��ת��
{
	//���̲߳���ȫ
	if (NULL == g_pCTestNewCount)
	{
		g_pCTestNewCount = new CTestNewCount;
	}

	return *g_pCTestNewCount;
}

void DestroyGlobalCTestNewCount()
{
	if (NULL != g_pCTestNewCount)
	{
		delete g_pCTestNewCount;
		g_pCTestNewCount = NULL;
	}
}

void RegisterCTestNewCount(lua_State *luaVM)
{
	luabind::module(luaVM, "namespacetest")		//namespacetestΪ�����ռ�����
	[
		class_<CTestNewCount, CTestNewCount_wrapper, boost::shared_ptr<CTestNewCount> >("CTestNewCount")
		.def(constructor<>())
		.def("TestCount", &CTestNewCount::TestCount)
		.def("Test", &CTestNewCount::Test)
		.def_readwrite("m_dwID", &CTestNewCount::m_dwID)
		.def("GetID", &CTestNewCount::GetID)
		.def("SetID", &CTestNewCount::SetID),

		def("GetNewObject", &GetNewObject, adopt(result)),		//adopt��ʾ����Ȩת���Lua��Result��ʾ�Ƿ���ֵת�ø�Lua
		def("GetSingleObject", &GetSingleObject, copy(result))		//����Ȩ��ת�ƣ�luaͨ���������캯��������һ������
	];


	//ע��vector������
	DEF_REGISTER_CONST_ITERATOR(luaVM, CTestNewCountArray, const_iterator, "VectorCTestNewCount");
	DEF_REGISTER_ITERATOR(luaVM, CTestNewCountArray, iterator, "VectorCTestNewCount");
	//DEF_REGISTER_VECTOR(luaVM, VectorCTestNewCount, VectorCTestNewCount, "VectorCTestNewCount");

	luabind::module(luaVM, "CTestNewCountArray") 
		[ 
		class_<CTestNewCountArray >("CTestNewCountArray") 
		.def(constructor<>()) 
		.def("PushBack", &CTestNewCountArray::push_back) 
		.def("Begin", &CTestNewCountArray::begin) 
		.def("End", &CTestNewCountArray::end) 
		.def("Clear", &CTestNewCountArray::clear) 
		.def("Erase", &CTestNewCountArray::erase) 
		]; 
}

void TestCTestNewCount(lua_State *luaVM)
{
	//����C++New�Ķ���ת�Ƹ�Lua
	//luabind::call_function<void>(luaVM, "LuaTestGetObject");

	//���Կ�����ȡ
	//luabind::call_function<void>(luaVM, "LuaTestCopyObject");

	//���Բ�������Ȩת�Ƹ�Lua
	/*for (int nIndex = 0; nIndex < 500; nIndex++)
	{
		luabind::call_function<void>(luaVM, "LuaTestTransObject", new CTestNewCount)[adopt(_1)];
	}*/


	//����������Vector
	CTestNewCountArray v;
	luabind::call_function<void>(luaVM, "LuaInitVector", boost::ref(v));

	//���Բ���ɾ��
	for (int a = 200; a < 800; a++)
	{
		luabind::call_function<void>(luaVM, "LuaEraseVector", boost::ref(v), a);
	}
}

CTestNewCount::CTestNewCount(void)
	: m_dwID(0)
{
	InterlockedIncrement(&m_nCount);
}

CTestNewCount::CTestNewCount(const CTestNewCount &other)
	: m_dwID(0)
{
	InterlockedIncrement(&m_nCount);
	m_dwID = other.m_dwID;
}

CTestNewCount::~CTestNewCount(void)
{
	InterlockedDecrement(&m_nCount);
}

void CTestNewCount::TestCount()
{
	assert(0 == m_nCount);
}

void CTestNewCount::Test()
{
	printf("CTestNewCount::Test()\n");
}

DWORD CTestNewCount::GetID()
{
	return m_dwID;
}

void CTestNewCount::SetID( DWORD dwID )
{
	m_dwID = dwID;
}

void CTestNewCount_wrapper::Test()
{
	call<void>("Test"); 
}

void CTestNewCount_wrapper::default_Test( CTestNewCount* ptr )
{
	return ptr->CTestNewCount::Test();
}

void CTestNewCountArray::push_back( const boost::shared_ptr<CTestNewCount> &_Val )
{
	return __super::push_back(_Val);
}

CTestNewCountArray::iterator CTestNewCountArray::begin()
{
	return __super::begin();
}

CTestNewCountArray::iterator CTestNewCountArray::end()
{
	return __super::end();
}

void CTestNewCountArray::clear()
{
	return __super::clear();
}

CTestNewCountArray::iterator CTestNewCountArray::erase( const_iterator _Where )
{
	return __super::erase(_Where);
}
