
// TestTimerDlg.h : ͷ�ļ�
//

#pragma once
#include "InterfaceTimer.h"

// CTestTimerDlg �Ի���
class CTestTimerDlg 
	: public CDialogEx
	, public ITimerCallback
{
// ����
public:
	CTestTimerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CTestTimerDlg();

// �Ի�������
	enum { IDD = IDD_TESTTIMER_DIALOG };

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
