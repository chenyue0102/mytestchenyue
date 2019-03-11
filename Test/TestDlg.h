
// TestDlg.h : 头文件
//

#pragma once
#include "MsgWnd.h"
#include "MsgDispatch.h"


// CTestDlg 对话框
class CTestDlg : public CDialogEx , public IMsgWndCallback
{
// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	void onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
