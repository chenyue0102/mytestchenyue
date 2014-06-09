#pragma once

interface ITest
{
	virtual void Test() = 0;
};

class CBaseText 
	: public ITest
{
public:
	CBaseText()
	{

	}
	virtual ~CBaseText()
	{

	}
	virtual void Test()
	{
		printf("CBaseText Test\n");
	}
};

class CBaseText2
	: public ITest
{
public:
	CBaseText2()
	{

	}
	virtual ~CBaseText2()
	{

	}
	virtual void Test()
	{
		printf("CBaseText2 Test\n");
	}
};

inline ITest* CreateITest()
{
	return new CBaseText();
}

inline ITest* CreateITest2()
{
	return new CBaseText2();
}

class test_wrapper
{
public:
	test_wrapper(ITest *p)
	{
		m_pITest = p;
	}
	void Test()
	{
		if (NULL != m_pITest)
		{
			m_pITest->Test();
		}
	}
private:
	ITest	*m_pITest;
};