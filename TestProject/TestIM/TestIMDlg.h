
// TestIMDlg.h : 头文件
//

#pragma once


// CTestIMDlg 对话框
class CTestIMDlg : public CDialogEx
{
// 构造
public:
	CTestIMDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTIM_DIALOG };
#endif

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
	afx_msg void OnBnClickedButtonCreate();
	int m_nClientId;
	afx_msg void OnBnClickedButtonDestroy();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonGetGrouplist();
	afx_msg void OnBnClickedButtonSendtext();
	afx_msg void OnBnClickedButtonInviteContact();
	afx_msg void OnBnClickedButtonGetContacts();
	afx_msg void OnBnClickedButtonDelfriend();
	afx_msg void OnBnClickedButtonCreategroup();
	afx_msg void OnBnClickedButtonDestroygroup();
	afx_msg void OnBnClickedButtonModifyGroup();
	afx_msg void OnBnClickedButtonGetChatroomlist();
	afx_msg void OnBnClickedButtonJoinchatroom();
	afx_msg void OnBnClickedButtonLeavechatroom();
};
