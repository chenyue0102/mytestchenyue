#pragma once
class CTestNewCount
{
public:
	CTestNewCount(void);
	~CTestNewCount(void);
	CTestNewCount(const CTestNewCount &other);	//¿½±´¹¹Ôìº¯Êý
public:
	static void	TestCount();
	void Test();
private:
	static volatile long		m_nCount;
	const char					*m_pstrTestBuffer;
};

