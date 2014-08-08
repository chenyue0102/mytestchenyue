#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>

//≤‚ ‘÷«ƒ‹÷∏’Î”Îlua
class CTestSharePointer
{
public:
	CTestSharePointer(void);
	CTestSharePointer(const CTestSharePointer &other);
	virtual ~CTestSharePointer(void);
public:
	virtual void Test();
public:
	int		m_nValue;
};

struct CTestSharePointer_wrapper 
	: public CTestSharePointer
	, public luabind::wrap_base
{
public:
	CTestSharePointer_wrapper();
public:
	virtual void Test();
	static void default_Test(CTestSharePointer* ptr);
};

class CTestSharePointerVector
	: public std::vector<boost::shared_ptr<CTestSharePointer> >
{
public:
	void push_back(const boost::shared_ptr<CTestSharePointer> &_Val);
	iterator erase(const_iterator _Where);
	iterator insert(const_iterator _Where, const boost::shared_ptr<CTestSharePointer>& _Val);
};

extern void RegisterTestSharePointer(lua_State *luaVM);
extern void TestSharePointer(lua_State *luaVM);
