
// TestExcelDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "NormalLock.h"
#include <list>

// CTestExcelDlg �Ի���
class CApplication;
class CSQLite;
class CTestExcelDlg : public CDialogEx
{
// ����
public:
	CTestExcelDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CTestExcelDlg();
// �Ի�������
	enum { IDD = IDD_TESTEXCEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
