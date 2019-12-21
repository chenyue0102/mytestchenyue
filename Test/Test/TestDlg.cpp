
// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <algorithm>
#include "./include/CrashRpt.h"
#include "CppSQLite3.h"
#include <stdlib.h>
#pragma comment(lib, "sqlite3.lib")
#pragma comment(lib, "./lib/CrashRpt1403.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestDlg �Ի���
#define IP_ADDRESS "127.0.0.1"
#define IP_PORT 9052

static bool initSocket()
{
	WORD version;
	WSADATA wsaData;
	version = MAKEWORD(1, 1);
	return (0 == WSAStartup(version, &wsaData));
}

void serverThread()
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(IP_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);

	int ret = bind(s, (sockaddr*)&addr, sizeof(addr));
	ret = listen(s, SOMAXCONN);
	sockaddr_in aptAddr = { 0 };
	int aptAddrLen = sizeof(aptAddr);
ACCEPT:
	SOCKET sApt = accept(s, (sockaddr*)&aptAddr, &aptAddrLen);
	bool bHaveRecvData = false;
	while (true)
	{
		fd_set set = { 0 };;
		timeval tv = { 0 };
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		FD_ZERO(&set);
		FD_SET(sApt, &set);
		int ret = select(0, &set, nullptr, nullptr, &tv);
		if (SOCKET_ERROR == ret)
		{
			closesocket(sApt);
			goto ACCEPT;
		}
		else if (FD_ISSET(sApt, &set))
		{
			bHaveRecvData = true;
			char szBuf[1024];
			int len = recv(sApt, szBuf, sizeof(szBuf) - 1, 0);
			if (len <= 0)
			{
				printf("recv failed %d\n", len);
				closesocket(sApt);
				goto ACCEPT;
			}
			szBuf[len] = '\0';
			if (len < 100)
			{
				printf("server recv=%s\n", szBuf);
			}
		}
		else
		{
			if (bHaveRecvData)
			{
				bHaveRecvData = false;
				send(sApt, "abcd", 4, 0);
				send(sApt, "1234", 4, 0);
			}
		}
	}
}


CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CTestDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_DESTROY, &CTestDlg::OnBnClickedButtonDestroy)
	ON_BN_CLICKED(IDC_BUTTON_POST, &CTestDlg::OnBnClickedButtonPost)
	ON_BN_CLICKED(IDC_BUTTON_REG, &CTestDlg::OnBnClickedButtonReg)
	ON_BN_CLICKED(IDC_BUTTON_UNREG, &CTestDlg::OnBnClickedButtonUnreg)
	ON_BN_CLICKED(IDC_BUTTON_DISPATCH, &CTestDlg::OnBnClickedButtonDispatch)
	ON_BN_CLICKED(IDC_BUTTON_CRASH, &CTestDlg::OnBnClickedButtonCrash)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CTestDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������
void installCrashReport(LPCTSTR pszAppName, LPCTSTR pszUrl, LPCTSTR pszPrivacyPolicyURL)
{
	CR_INSTALL_INFO info;
	memset(&info, 0, sizeof(CR_INSTALL_INFO));
	info.cb = sizeof(CR_INSTALL_INFO);
	info.pszAppName = pszAppName;// _T("MFCDemo"); // Define application name.
									 //info.pszAppVersion = _T("1.0.0"); // Define application version.
									 // URL for sending error reports over HTTP.
	info.pszUrl = pszUrl;// _T("http://someserver.com/crashrpt.php");
	// Install all available exception handlers.
	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;
	// Provide privacy policy URL
	info.pszPrivacyPolicyURL = pszPrivacyPolicyURL;// _T("http://someserver.com/privacy.html");

	int nResult = crInstall(&info);
	if (nResult == 0)
	{
		// Take screenshot of the app window at the moment of crash
		crAddScreenshot2(CR_AS_MAIN_WINDOW | CR_AS_USE_JPEG_FORMAT, 95);
	}
	else
	{
		TCHAR buff[256] = { 0 };
		crGetLastErrorMsg(buff, 256);
		OutputDebugString(buff);
	}
}

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	std::vector<int> v = { 1,2,3 };
	auto iterRemove = std::remove(v.begin(), v.end(), 3);
	if (iterRemove != v.end())
	{
		v.erase(iterRemove, v.end());
	}
	

	installCrashReport(L"Test", L"http://www.baidu.com", L"http://www.baidu.com");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (8000 == uMsg)
	{
		std::string strBuffer;
		strBuffer.resize(lParam);
		m_msgDispatch.getMsg(wParam, &*strBuffer.begin(), strBuffer.size());
	}
	
}

void CTestDlg::OnBnClickedButtonCreate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_msgWnd.create(this);
}


void CTestDlg::OnBnClickedButtonDestroy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_msgWnd.destroy();
}


void CTestDlg::OnBnClickedButtonPost()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::PostMessage(m_msgWnd.getHwnd(), 4096, 2048, 1024);
}


void CTestDlg::OnBnClickedButtonReg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int a = 8000; a < 8010; a++)
	{
		m_msgDispatch.regMsg(m_msgWnd.getHwnd(), a);
		m_msgDispatch.regMsg(GetSafeHwnd(), a);
	}
}


void CTestDlg::OnBnClickedButtonUnreg()
{
	m_msgDispatch.unregMsg(m_msgWnd.getHwnd(), 8000);
	m_msgDispatch.unregMsg(m_msgWnd.getHwnd(), 0);
}


void CTestDlg::OnBnClickedButtonDispatch()
{
	m_msgDispatch.pushMsg(8000, "abcd1234", 8);
}


void CTestDlg::OnBnClickedButtonCrash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int a = 0;
	a = 1 / a;
}


void CTestDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		int ret = 0;
		CppSQLite3DB db;
		db.open("test.db");

		const char *pstrCheckTable = "SELECT COUNT(*) FROM sqlite_master where type='table' and name='testtable'";
		//const char *pstrCheckTable = "SELECT COUNT(*) FROM sqlite_master where type='table' and name='testtablexxx'";
		CppSQLite3Query query = db.execQuery(pstrCheckTable);
//		query.nextRow();
		query.eof();
		
		int tablecount = query.getIntField(0, 0);
		if (tablecount <= 0)
		{
			printf("not create table");
			const char *pstrCreateTable =
				"create table testtable("
				"id bigint,"
				"name text,"
				"primary key(id))"
				;
			ret = db.execDML(pstrCreateTable);
			if (SQLITE_OK == ret)
			{
				printf("create success");
			}
		}
		else
		{
			printf("have create table");
			const char *pstrInsert = "insert or replace into testtable(id,name) values(1234567890123456789, 'abcd')";
			int changerow = db.execDML(pstrInsert);
			
			printf("replace or insert success %d", changerow);

			const char *pstrselect = "select id,name from testtable";
			CppSQLite3Query q = db.execQuery(pstrselect);

			long long id = 0;
			std::string name;
			while (!q.eof())
			{
				id = q.getInt64Field("id", 0i64);
				name = q.getStringField("name", "");
				q.nextRow();
			}
			q.finalize();

			const char *pselectnull = "select id,name from testtable where id=0 and name is null";
			CppSQLite3Query qnull = db.execQuery(pselectnull);

			while (!qnull.eof())
			{
				id = qnull.getInt64Field("id", 0i64);
				name = qnull.getStringField("name", "");
				qnull.nextRow();
			}
			qnull.finalize();

			const char *pstrBind = "insert or replace into testtable(id,name) values(5566, :name)";
			CppSQLite3Statement statement = db.compileStatement(pstrBind);
			statement.bind(":name", "bindnameparam");
			changerow = statement.execDML();
			printf("replace or insert success %d", changerow);
		}
		query.finalize();

		db.close();
	}
	catch (CppSQLite3Exception &e)
	{
		std::string str = e.errorMessage();
		printf("%s", str.c_str());
	}
	
}
