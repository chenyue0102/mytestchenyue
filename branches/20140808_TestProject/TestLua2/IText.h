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
		printf("CBaseText\n");
	}
	virtual ~CBaseText()
	{
		printf("~CBaseText\n");
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
		printf("CBaseText2\n");
	}
	virtual ~CBaseText2()
	{
		printf("~CBaseText2\n");
	}
	virtual void Test()
	{
		printf("CBaseText2 Test\n");
	}
};

inline int CreateITest()
{
	return (int) new CBaseText();
}

inline int CreateITest2()
{
	return (int)  new CBaseText2();
}

template<typename C>
class CT
{
public:
	template<typename T>
	T TestT(T &t)
	{
		return t + 1;
	}

	template<typename T>
	T TestT(T t, int a)
	{
		return t + 1;
	}
};


class test_wrapper
{
public:
	test_wrapper( int p)
	{
		m_pITest = (ITest*)(p);
	}
	virtual ~test_wrapper()
	{
		printf("~test_wrapper\n");
	}
	void Test()
	{
		int (CT<int>::*fun)(int&) = &CT<int>::TestT<int>;
		CT<int> ct;
		int a = 0;
		(ct.*fun)(a);
		if (NULL != m_pITest)
		{
			m_pITest->Test();
		}
	}
private:
	ITest	*m_pITest;
};