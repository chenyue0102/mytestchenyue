
// TestIOCP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestIOCPApp: 
// �йش����ʵ�֣������ TestIOCP.cpp
//

class CTestIOCPApp : public CWinApp
{
public:
	CTestIOCPApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestIOCPApp theApp;