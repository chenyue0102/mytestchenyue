
// TestTimerDlg.h : 头文件
//

#pragma once
#include "InterfaceTimer.h"

// CTestTimerDlg 对话框
class CTestTimerDlg 
	: public CDialogEx
	, public ITimerCallback
{
// 构造
public:
	CTestTimerDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CTestTimerDlg();

// 对话框数据
	enum { IDD = IDD_TESTTIMER_DIALOG };

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
public:
	afx_msg void OnBnClickedButtonStartTimer();
	long	m_lKey;
public:
	virtual void STDMETHODCALLTYPE OnTimer(DWORD dwUserData);
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( /* [in] */ REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject) 
	{
		return E_NOTIMPL;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef( void)
	{
		return 0;
	}

	virtual ULONG STDMETHODCALLTYPE Release( void)
	{
		return 0;
	}
	DWORD	m_dwTickCount;
};
