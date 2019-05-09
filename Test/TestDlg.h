
// TestDlg.h : ͷ�ļ�
//

#pragma once
#include "MsgWnd.h"
#include "MsgDispatch.h"


// CTestDlg �Ի���
class CTestDlg : public CDialogEx , public IMsgWndCallback
{
// ����
public:
	CTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	void onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	MsgWnd m_msgWnd;
	MsgDispatch m_msgDispatch;
public:
	afx_msg void OnBnClickedButtonCreate();
	afx_msg void OnBnClickedButtonDestroy();
	afx_msg void OnBnClickedButtonPost();
	afx_msg void OnBnClickedButtonReg();
	afx_msg void OnBnClickedButtonUnreg();
	afx_msg void OnBnClickedButtonDispatch();
	afx_msg void OnBnClickedButtonCrash();
	afx_msg void OnBnClickedButtonOpen();
};
