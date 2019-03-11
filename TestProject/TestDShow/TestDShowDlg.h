
// TestDShowDlg.h : 头文件
//

#pragma once
#include "CaptureVideo.h"
#include "CaptureAudio.h"

// CTestDShowDlg 对话框
class CTestDShowDlg : public CDialogEx, public CVdoFrameHandler, public CAdoFrameHandler
{
// 构造
public:
	CTestDShowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTDSHOW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

														// 重载它，这里的pBuffer指针里面放的就是BGR24的的采集结果，lBufferSize就是pBuffer长度
	void VdoFrameData(double dblSampleTime, BYTE * pBuffer, long lBufferSize);
	virtual void AdoFrameData(BYTE* pBuffer, long lBufferSize);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
