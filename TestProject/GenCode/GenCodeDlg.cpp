
// GenCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GenCode.h"
#include "GenCodeDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CODE_NUMBER_COUNT 5
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGenCodeDlg 对话框



CGenCodeDlg::CGenCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GENCODE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGenCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COUNT, m_genCount);
	DDX_Control(pDX, IDC_EDIT_START, m_startNumber);
	DDX_Control(pDX, IDC_EDIT_END, m_endNumber);
}

BEGIN_MESSAGE_MAP(CGenCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GEN, &CGenCodeDlg::OnBnClickedButtonGen)
END_MESSAGE_MAP()


// CGenCodeDlg 消息处理程序

BOOL CGenCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGenCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGenCodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGenCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
const char g_Mask[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
void CGenCodeDlg::OnBnClickedButtonGen()
{
	CString strGenCount;
	CString strEnterText;

	m_genCount.GetWindowText(strGenCount);
	int nGenCount = _tstoi(strGenCount);

	m_startNumber.GetWindowText(strEnterText);
	CString strStartNumber = strEnterText.Right(CODE_NUMBER_COUNT);
	CStringA strLeftFixText; 
	strLeftFixText = strEnterText.Left(strEnterText.GetLength() - CODE_NUMBER_COUNT);
	int nStartNumber = _tstoi(strStartNumber);
	
	FILE *fp = fopen("GenCode.txt", "wb");
	srand(GetTickCount());
	CStringA strWriteText;
	for (int i = 0; i < nGenCount; i++)
	{
		if (0 != i)
		{
			fwrite("\r\n", 1, 2, fp);
		}
		strWriteText.Format("%s%05d%c", strLeftFixText, nStartNumber + i, g_Mask[rand() % _countof(g_Mask)]);
		fwrite(strWriteText, 1, strWriteText.GetLength(), fp);
	}
	fclose(fp);
	CString strEndText;
	strEndText = strWriteText;
	m_endNumber.SetWindowText(strEndText);
}
