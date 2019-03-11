
// TestDShowDlg.h : ͷ�ļ�
//

#pragma once
#include "CaptureVideo.h"
#include "CaptureAudio.h"

// CTestDShowDlg �Ի���
class CTestDShowDlg : public CDialogEx, public CVdoFrameHandler, public CAdoFrameHandler
{
// ����
public:
	CTestDShowDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTDSHOW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

														// �������������pBufferָ������ŵľ���BGR24�ĵĲɼ������lBufferSize����pBuffer����
	void VdoFrameData(double dblSampleTime, BYTE * pBuffer, long lBufferSize);
	virtual void AdoFrameData(BYTE* pBuffer, long lBufferSize);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
