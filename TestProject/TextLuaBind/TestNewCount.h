#pragma once
class CTestNewCount
{
public:
	CTestNewCount(void);
	~CTestNewCount(void);
	CTestNewCount(const CTestNewCount &other);	//�������캯��
public:
	static void	TestCount();
	void Test();
private:
	static volatile long		m_nCount;
	const char					*m_pstrTestBuffer;
};

