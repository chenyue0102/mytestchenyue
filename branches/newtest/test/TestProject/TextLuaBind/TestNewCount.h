#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>

class CTestNewCount
{
public:
	CTestNewCount(void);
	~CTestNewCount(void);
	CTestNewCount(const CTestNewCount &other);	//¿½±´¹¹Ôìº¯Êý
public:
	static void	TestCount();
	virtual void Test();
	DWORD	GetID();
	void			SetID(DWORD dwID);
public:
	static volatile long		m_nCount;
	DWORD						m_dwID;
};

struct CTestNewCount_wrapper 
	: public CTestNewCount
	, public luabind::wrap_base
{
public:
	CTestNewCount_wrapper(){;}
public:
	virtual void Test();
	static void default_Test(CTestNewCount* ptr);
};

class CTestNewCountArray : public std::vector<boost::shared_ptr<CTestNewCount> >
{
public:
	void		push_back(const boost::shared_ptr<CTestNewCount> &_Val);
	CTestNewCountArray::iterator begin();
	CTestNewCountArray::iterator	 end();
	void		clear();
	CTestNewCountArray::iterator erase(CTestNewCountArray::const_iterator _Where);
};
