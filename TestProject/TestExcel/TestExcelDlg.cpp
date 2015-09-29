
// TestExcelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestExcel.h"
#include "TestExcelDlg.h"
#include "afxdialogex.h"
#include "CApplication.h"
#include "CWorkbooks.h"
#include "CWorkbook.h"
#include "CWorksheets.h"
#include "CWorksheet.h"
#include "CRange.h"
#include <string>
#include "sqlite3.h"
#include "Sqlite3Connect.h"
#include <assert.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
std::wstring TranslateString(const std::string &strText,  UINT CodePage/* = CP_ACP*/)
{
	std::wstring strWText;
	int nWideLength = 0;
	nWideLength = MultiByteToWideChar(CodePage, 0, strText.c_str(), static_cast<int>(strText.length()), NULL, 0);
	if (0 != nWideLength)
	{
		strWText.resize(nWideLength, L'\0');
		MultiByteToWideChar(CodePage, 0, strText.c_str(), static_cast<int>(strText.length()), &*strWText.begin(), nWideLength);
	}
	return strWText;
}

std::string TranslateString(const std::wstring &strWText,  UINT CodePage/* = CP_ACP*/)
{
	std::string strText;
	int nLength = 0;
	nLength = WideCharToMultiByte(CodePage, 0, strWText.c_str(), static_cast<int>(strWText.length()), NULL, 0, NULL, NULL);
	if (0 != nLength)
	{
		strText.resize(nLength, '\0');
		WideCharToMultiByte(CodePage, 0, strWText.c_str(), static_cast<int>(strWText.length()), &*strText.begin(), nLength, NULL, NULL);
	}
	return strText;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestExcelDlg 对话框

enum FieldType
{
	FieldTypeNone,
	FieldTypeInt64,
	FieldTypeString,
};
struct FieldInfo
{
	FieldType	Type;
	WCHAR		FieldName[32];
};

/*
L"([大类] int, [小类] int,[大组] int, [小组] int"
L",[序号] int, [设备实施分类与代码] int, [设备实施分类名称] text, [设备实施名称] text,[计量单位] text"
L",[序号2] int,[资产类别] text,[资产编码] int,[资产名称] text,[规格型号] text,[原值] text,[开始使用日期] text"
L",[具体位置] text, [使用年限] text, [重要等级] text,[设备状态] text,[在用状态是否完好] text,[是否委托（受委托）] text"
L",[受托（委托）单位] text, [备注] text"
*/
FieldInfo g_FieldInfos[] = 
{
	{FieldTypeInt64, L"大类"}, {FieldTypeInt64, L"小类"}, {FieldTypeInt64, L"大组"}, {FieldTypeInt64, L"小组"},
	{FieldTypeInt64, L"序号"}, {FieldTypeInt64, L"设备实施分类与代码"}, {FieldTypeString, L"设备实施分类名称"}, {FieldTypeString, L"设备实施名称"}, {FieldTypeString, L"计量单位"},
	{FieldTypeInt64, L"序号2"}, {FieldTypeString, L"资产类别"}, {FieldTypeInt64, L"资产编码"}, {FieldTypeString, L"资产名称"}, 
	{FieldTypeString, L"规格型号"}, {FieldTypeString, L"原值"}, {FieldTypeString, L"开始使用日期"},
	{FieldTypeString, L"具体位置"}, {FieldTypeString, L"使用年限"}, {FieldTypeString, L"重要等级"},
	{FieldTypeString, L"设备状态"}, {FieldTypeString, L"在用状态是否完好"}, {FieldTypeString, L"是否委托（受委托）"},
	{FieldTypeString, L"受托（委托）单位"}, {FieldTypeString, L"备注"}, 
};


CTestExcelDlg::CTestExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestExcelDlg::IDD, pParent)
	, m_pApplication(new CApplication)
	, m_pSQLite(new CSQLite)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTestExcelDlg::~CTestExcelDlg()
{
	if (nullptr != m_pApplication)
	{
		delete m_pApplication;
		m_pApplication = nullptr;
	}
	if (nullptr != m_pSQLite)
	{
		delete m_pSQLite;
		m_pSQLite = nullptr;
	}
}

void CTestExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_editFileName);
}

BEGIN_MESSAGE_MAP(CTestExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE, &CTestExcelDlg::OnBnClickedButtonSelectFile)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TO_DATABASE, &CTestExcelDlg::OnBnClickedButtonLoadToDatabase)
END_MESSAGE_MAP()


// CTestExcelDlg 消息处理程序

BOOL CTestExcelDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	InitSqliteDatabase();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestExcelDlg::OnPaint()
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
HCURSOR CTestExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestExcelDlg::OnBnClickedButtonSelectFile()
{
	CFileDialog openFile(TRUE, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"xls (*.xls)|*.xls||", this);
	if (IDOK == openFile.DoModal())
	{
		m_strExcelFileName = openFile.GetPathName();
		m_editFileName.SetWindowText(m_strExcelFileName);
	}
}

void CTestExcelDlg::InitSqliteDatabase()
{
	std::string strDataBase("c:\\1.db3");
	do 
	{
		m_pSQLite->Open(strDataBase.c_str());
		//初始化表
		//"select count(*) from sqlite_master where type = 'table' and name = ''",
		const char *pstrCheckTableName[] = 
		{
			"\'Equipment\'",
		};

		/*const WCHAR *pstrCreateTable[] = 
		{
			L"create table [Equipment]"
			L"([大类] int, [小类] int,[大组] int, [小组] int"
			L",[序号] int, [设备实施分类与代码] int, [设备实施分类名称] text, [设备实施名称] text,[计量单位] text"
			L",[序号2] int,[资产类别] text,[资产编码] int,[资产名称] text,[规格型号] text,[原值] text,[开始使用日期] text"
			L",[具体位置] text, [使用年限] text, [重要等级] text,[设备状态] text,[在用状态是否完好] text,[是否委托（受委托）] text"
			L",[受托（委托）单位] text, [备注] text"
			L")",
		};*/
		CString strCreateTable;
		strCreateTable = L"create table [Equipment](";
		for (int nIndex = 0; nIndex < _countof(g_FieldInfos); nIndex++)
		{
			if (0 != nIndex)
			{
				strCreateTable += L",";
			}
			strCreateTable += g_FieldInfos[nIndex].FieldName;
			strCreateTable += L" ";
			switch (g_FieldInfos[nIndex].Type)
			{
			case FieldTypeInt64:
				{
					strCreateTable += L"bigint";
				}
				break;
			case FieldTypeString:
				{
					strCreateTable += L"text";
				}
				break;
			default:
				{
					MessageBox(L"false");
					assert(false);
				}
				break;
			}
		}
		strCreateTable += L")";
		CString strTableNames[] = {strCreateTable};
		//assert(_countof(pstrCreateTable) == _countof(pstrCheckTableName));
		std::string strCheckTableHead("select count(*) from sqlite_master where type = 'table' and name = ");
		for (int nIndex = 0; nIndex < _countof(pstrCheckTableName); nIndex++)
		{
			std::string strCheckTable = strCheckTableHead + pstrCheckTableName[nIndex];
			CSQLiteDataReader SQLiteDataReade = m_pSQLite->ExcuteQuery(strCheckTable.c_str());
			if (SQLiteDataReade.Read())
			{
				// 获取TableCount
				int iReturn = SQLiteDataReade.GetIntValue(0);

				// 释放资源
				SQLiteDataReade.Close();

				// 未创建表,需要创建表
				if (iReturn == 0)
				{
					if (!m_pSQLite->ExcuteNonQuery(TranslateString(static_cast<const WCHAR*>(strTableNames[nIndex]), CP_UTF8).c_str()))
					{
						MessageBox(L"false");
						assert(false);
					}
				}
			}
		}
	} while (false);
}


void CTestExcelDlg::OnBnClickedButtonLoadToDatabase()
{
	CApplication app;
	BOOL bNeedQuit = FALSE;
	do 
	{
		_beginthreadex(nullptr, 0, &CTestExcelDlg::ThreadProc, this, 0, nullptr);
		if (!app.CreateDispatch(L"ET.APPLICATION"))
		{
			assert(false);
			break;
		}
		//m_pApplication->put_Visible(TRUE);
		bNeedQuit = TRUE;

		CWorkbooks workbooks(app.get_Workbooks());
		
		_variant_t vtFileName(m_strExcelFileName);
		_variant_t vtEmpty;
		CWorkbook workbook(workbooks.Open(vtFileName, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty));

		CWorksheets Worksheets(workbook.get_Worksheets());
		long lCount = Worksheets.get_Count();
		CWorksheet worksheet(Worksheets.get_Item(_variant_t(1)));
		CRange range(worksheet.get_Cells());
		int nBeginRow = 5, nBeginColumn = 1;
		int nEndRow = 14081, nEndColumn = 24;

		//m_pSQLite->BeginTransaction();

		DWORD dwTickCount = GetTickCount();
		for (int nRowIndex = nBeginRow; nRowIndex <= nEndRow; nRowIndex++)
		{
			/*L"([大类] int, [小类] int,[大组] int, [小组] int"
			L",[序号] int, [设备实施分类与代码] int, [设备实施分类名称] text, [设备实施名称] text,[计量单位] text"
			L",[序号2] int,[资产类别] text,[资产编码] int,[资产名称] text,[规格型号] text,[原值] text,[开始使用日期] text"
			L",[具体位置] text, [使用年限] text, [重要等级] text,[设备状态] text,[在用状态是否完好] text,[是否委托（受委托）] text"
			L",[受托（委托）单位] text, [备注] text"*/
			
			if (nRowIndex % 1000 == 0)
			{
				DWORD dwTickCount2 = GetTickCount() - dwTickCount;
				dwTickCount = GetTickCount();
			}
			CString strDalei, strXiaoLei, strDaZu, strXiaoZu;
			CString strXuHao, strFenLeiDaiMa, strFenLeiMingCheng, strShiShiMingCheng, strJiLiangDanWei;
			CString strXuHao2, strZiChanLeiBie, strZiChanBianMa, strZiChanMingCheng, strGuiGeXingHao, strYuanZhi, strRiQi;
			CString strWeiZhi, strNianXian, strDengJi, strZhuangTai, strWanHao, strWeiTuo;
			CString strWeiTuoDanWei, strBeiZhu;

			InsertInfo *pInsertInfo = new InsertInfo;
			//CString strArray[50];

			for (int nColumnIndex = nBeginColumn; nColumnIndex <= nEndColumn; nColumnIndex++)
			{
				_variant_t vtDispatch = range.get_Item(_variant_t(nRowIndex), _variant_t(nColumnIndex));
				CRange rangeResult(vtDispatch);
				CString strResult = rangeResult.get_Formula();
				strResult.Trim();
				pInsertInfo->strArray[nColumnIndex - 1] = strResult;
			}
			{
				CAutoLock AutoLock(m_NormalLock);
				m_InsertInfoArray.push_back(pInsertInfo);
			}
		}
		//m_pSQLite->CommitTransaction();
	} while (false);
	if (bNeedQuit)
	{
		app.Quit();
	}
}

unsigned __stdcall CTestExcelDlg::ThreadProc(void *pArgument)
{
	CTestExcelDlg *pThis = reinterpret_cast<CTestExcelDlg*>(pArgument);
	pThis->m_pSQLite->BeginTransaction();
	int nCommitCount = 0;
	while(true)
	{
		if (++nCommitCount > 1000)
		{
			nCommitCount = 0;
			pThis->m_pSQLite->CommitTransaction();
			pThis->m_pSQLite->BeginTransaction();
		}
		InsertInfo *pInserInfo = nullptr;
		{
			CAutoLock AutoLock(pThis->m_NormalLock);
			if (0 != pThis->m_InsertInfoArray.size())
			{
				pInserInfo = *(pThis->m_InsertInfoArray.begin());
				pThis->m_InsertInfoArray.pop_front();
			}
		}
		if (nullptr == pInserInfo)
		{
			Sleep(1);
			continue;
		}
		CString strSQL;
		strSQL = L"insert into [Equipment] values(";
		for (int nIndex = 0; nIndex < _countof(g_FieldInfos); nIndex++)
		{
			if (0 != nIndex)
			{
				strSQL += ",";
			}
			switch (g_FieldInfos[nIndex].Type)
			{
			case FieldTypeInt64:
				{
					if (pInserInfo->strArray[nIndex].IsEmpty())
					{
						strSQL += L"0";
					}
					else
					{
						strSQL += pInserInfo->strArray[nIndex];
					}
				}
				break;
			case FieldTypeString:
				{
					strSQL += L"'";
					strSQL += pInserInfo->strArray[nIndex];
					strSQL += L"'";
				}
				break;
			default:
				{
					pThis->MessageBox(L"false");
					assert(false);
				}
				break;
			}
		}
		strSQL += L")";

		CSQLiteCommand SQLiteCommand(pThis->m_pSQLite, TranslateString((const WCHAR*)strSQL, CP_UTF8).c_str());
		/*std::string strData[50];
		for (int nIndex = 0; nIndex < _countof(g_FieldInfos); nIndex++)
		{
		if (FieldTypeString == g_FieldInfos[nIndex].Type)
		{
		CStringA strIndex;
		strIndex.Format(":FieldIndex%d", nIndex);
		int iParamIndex = 0;
		if (0 == (iParamIndex = SQLiteCommand.GetParamIndex(strIndex)))
		{
		assert(false);
		break;
		}
		strData[nIndex] = TranslateString((const WCHAR*)strArray[nIndex], CP_ACP);
		if (!SQLiteCommand.BindParam(iParamIndex, (const unsigned char*)strData[nIndex].data(), strData[nIndex].length()))
		{
		assert(false);
		break;
		}
		}
		}*/
		if (!SQLiteCommand.Excute())
		{
			pThis->MessageBox(L"false");
			assert(false);
			break;
		}
		SQLiteCommand.Clear();

		delete pInserInfo;
		Sleep(1);
	}
	return 0;
}
