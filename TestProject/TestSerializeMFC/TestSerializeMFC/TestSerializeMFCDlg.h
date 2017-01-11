
// TestSerializeMFCDlg.h : 头文件
//

#pragma once
#include "InvokeHelper.h"

struct TestA;
struct TestB;
// CTestSerializeMFCDlg 对话框
class CTestSerializeMFCDlg : public CDialogEx
{
// 构造
public:
	CTestSerializeMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTSERIALIZEMFC_DIALOG };

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

	void DealA(const TestA &a);
	void DealB(const TestB &b);
	unsigned long DealC(const TestA &a, TestB &b);
	void TestCallFun();
	CInvokeHelper<CTestSerializeMFCDlg> m_InvokeHelper;
};
