// TestNsis.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "TestNsis.h"


// ���ǵ���������һ��ʾ��
TESTNSIS_API int nTestNsis=0;

// ���ǵ���������һ��ʾ����
TESTNSIS_API int fnTestNsis(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� TestNsis.h
CTestNsis::CTestNsis()
{
	return;
}
