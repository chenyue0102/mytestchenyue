
// TestSerializeMFCDlg.h : ͷ�ļ�
//

#pragma once
#include "InvokeHelper.h"

struct TestA;
struct TestB;
// CTestSerializeMFCDlg �Ի���
class CTestSerializeMFCDlg : public CDialogEx
{
// ����
public:
	CTestSerializeMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTSERIALIZEMFC_DIALOG };

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

	void DealA(const TestA &a);
	void DealB(const TestB &b);
	unsigned long DealC(const TestA &a, TestB &b);
	void TestCallFun();
	CInvokeHelper<CTestSerializeMFCDlg> m_InvokeHelper;
};
