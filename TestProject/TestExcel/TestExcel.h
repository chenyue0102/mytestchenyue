
// TestExcel.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestExcelApp:
// �йش����ʵ�֣������ TestExcel.cpp
//

class CTestExcelApp : public CWinApp
{
public:
	CTestExcelApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestExcelApp theApp;