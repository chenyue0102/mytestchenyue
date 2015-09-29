
// TestExcelDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "NormalLock.h"
#include <list>

// CTestExcelDlg 对话框
class CApplication;
class CSQLite;
class CTestExcelDlg : public CDialogEx
{
// 构造
public:
	CTestExcelDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTestExcelDlg();
// 对话框数据
	enum { IDD = IDD_TESTEXCEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CApplication	*m_pApplication;
public:
	CEdit m_editFileName;
	afx_msg void OnBnClickedButtonSelectFile();
	CString			m_strExcelFileName;
	void InitSqliteDatabase();
	CSQLite		*m_pSQLite;
	afx_msg void OnBnClickedButtonLoadToDatabase();
	CNormalLock	m_NormalLock;
	static unsigned __stdcall ThreadProc(void *pArgument);

	struct InsertInfo
	{
		CString strArray[50];
	};
	typedef std::list<InsertInfo*>	InsertInfoArray;
	InsertInfoArray	m_InsertInfoArray;
};
