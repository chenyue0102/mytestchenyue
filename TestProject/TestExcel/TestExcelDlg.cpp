
// TestExcelDlg.cpp : ʵ���ļ�
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
#include <sstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
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

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestExcelDlg �Ի���

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
L"([����] int, [С��] int,[����] int, [С��] int"
L",[���] int, [�豸ʵʩ���������] int, [�豸ʵʩ��������] text, [�豸ʵʩ����] text,[������λ] text"
L",[���2] int,[�ʲ����] text,[�ʲ�����] int,[�ʲ�����] text,[����ͺ�] text,[ԭֵ] text,[��ʼʹ������] text"
L",[����λ��] text, [ʹ������] text, [��Ҫ�ȼ�] text,[�豸״̬] text,[����״̬�Ƿ����] text,[�Ƿ�ί�У���ί�У�] text"
L",[���У�ί�У���λ] text, [��ע] text"
*/
FieldInfo g_FieldInfos[] = 
{
	{FieldTypeInt64, L"����"}, {FieldTypeInt64, L"С��"}, {FieldTypeInt64, L"����"}, {FieldTypeInt64, L"С��"},
	{FieldTypeInt64, L"���"}, {FieldTypeInt64, L"�豸ʵʩ���������"}, {FieldTypeString, L"�豸ʵʩ��������"}, {FieldTypeString, L"�豸ʵʩ����"}, {FieldTypeString, L"������λ"},
	{FieldTypeInt64, L"���2"}, {FieldTypeString, L"�ʲ����"}, {FieldTypeInt64, L"�ʲ�����"}, {FieldTypeString, L"�ʲ�����"}, 
	{FieldTypeString, L"����ͺ�"}, {FieldTypeString, L"ԭֵ"}, {FieldTypeString, L"��ʼʹ������"},
	{FieldTypeString, L"����λ��"}, {FieldTypeString, L"ʹ������"}, {FieldTypeString, L"��Ҫ�ȼ�"},
	{FieldTypeString, L"�豸״̬"}, {FieldTypeString, L"����״̬�Ƿ����"}, {FieldTypeString, L"�Ƿ�ί�У���ί�У�"},
	{FieldTypeString, L"���У�ί�У���λ"}, {FieldTypeString, L"��ע"}, 
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
	DDX_Control(pDX, IDC_EDIT_SAVE_EXCEL, m_editSaveExcel);
}

BEGIN_MESSAGE_MAP(CTestExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE, &CTestExcelDlg::OnBnClickedButtonSelectFile)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TO_DATABASE, &CTestExcelDlg::OnBnClickedButtonLoadToDatabase)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_EXCEL, &CTestExcelDlg::OnBnClickedButtonSelectExcel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_EXCEL, &CTestExcelDlg::OnBnClickedButtonSaveExcel)
END_MESSAGE_MAP()


// CTestExcelDlg ��Ϣ�������

BOOL CTestExcelDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	InitSqliteDatabase();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestExcelDlg::OnPaint()
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
		//��ʼ����
		//"select count(*) from sqlite_master where type = 'table' and name = ''",
		const char *pstrCheckTableName[] = 
		{
			"\'Equipment\'",
		};

		/*const WCHAR *pstrCreateTable[] = 
		{
			L"create table [Equipment]"
			L"([����] int, [С��] int,[����] int, [С��] int"
			L",[���] int, [�豸ʵʩ���������] int, [�豸ʵʩ��������] text, [�豸ʵʩ����] text,[������λ] text"
			L",[���2] int,[�ʲ����] text,[�ʲ�����] int,[�ʲ�����] text,[����ͺ�] text,[ԭֵ] text,[��ʼʹ������] text"
			L",[����λ��] text, [ʹ������] text, [��Ҫ�ȼ�] text,[�豸״̬] text,[����״̬�Ƿ����] text,[�Ƿ�ί�У���ί�У�] text"
			L",[���У�ί�У���λ] text, [��ע] text"
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
				// ��ȡTableCount
				int iReturn = SQLiteDataReade.GetIntValue(0);

				// �ͷ���Դ
				SQLiteDataReade.Close();

				// δ������,��Ҫ������
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
	int nStep = 1000;
	int nRowBegin = 10606;//5;
	int nMaxRow = 14081;
	while (nRowBegin < nMaxRow)
	{
		int nRowCount = nStep;
		if (nRowBegin + nRowCount > nMaxRow)
		{
			nRowCount = nMaxRow - nRowBegin + 1;
		}
		LoadToDatabase(nRowBegin, 1, nRowCount, 24);
		nRowBegin += nStep;
	}
}

void CTestExcelDlg::LoadToDatabase(int nTempBeginRow, int nTempBeginColumn, int nRowCount, int nColumnCount)
{
	CApplication app;
	BOOL bNeedQuit = FALSE;
	do 
	{
		if (!app.CreateDispatch(L"ET.APPLICATION"))
		{
			assert(false);
			break;
		}
		bNeedQuit = TRUE;

		CWorkbooks workbooks(app.get_Workbooks());
		
		_variant_t vtFileName(m_strExcelFileName);
		_variant_t vtEmpty;
		CWorkbook workbook(workbooks.Open(vtFileName, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty, vtEmpty));

		CWorksheets Worksheets(workbook.get_Worksheets());
		CWorksheet worksheet(Worksheets.get_Item(_variant_t(1)));
		CRange range(worksheet.get_Cells());
		int nBeginRow = nTempBeginRow, nBeginColumn = nTempBeginColumn;
		int nEndRow = nRowCount + nBeginRow, nEndColumn = nColumnCount + nBeginColumn;

		m_pSQLite->BeginTransaction();

		DWORD dwTickCount = GetTickCount();
		for (int nRowIndex = nBeginRow; nRowIndex < nEndRow; nRowIndex++)
		{
			/*L"([����] int, [С��] int,[����] int, [С��] int"
			L",[���] int, [�豸ʵʩ���������] int, [�豸ʵʩ��������] text, [�豸ʵʩ����] text,[������λ] text"
			L",[���2] int,[�ʲ����] text,[�ʲ�����] int,[�ʲ�����] text,[����ͺ�] text,[ԭֵ] text,[��ʼʹ������] text"
			L",[����λ��] text, [ʹ������] text, [��Ҫ�ȼ�] text,[�豸״̬] text,[����״̬�Ƿ����] text,[�Ƿ�ί�У���ί�У�] text"
			L",[���У�ί�У���λ] text, [��ע] text"*/
			
			if (nRowIndex % 1000 == 0)
			{
				DWORD dwTickCount2 = GetTickCount() - dwTickCount;
				dwTickCount = GetTickCount();
				m_pSQLite->CommitTransaction();
				m_pSQLite->BeginTransaction();
			}
			CString strArray[50];

			for (int nColumnIndex = nBeginColumn; nColumnIndex < nEndColumn; nColumnIndex++)
			{
				_variant_t vtDispatch = range.get_Item(_variant_t(nRowIndex), _variant_t(nColumnIndex));
				CRange rangeResult(vtDispatch);
				CString strResult = rangeResult.get_Formula();
				strResult.Trim();
				strArray[nColumnIndex - 1] = strResult;
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
						INT64 i64Value = _ttoi64(strArray[nIndex]);
						std::wstringstream ss;
						ss << i64Value;
						strSQL += ss.str().c_str();
					}
					break;
				case FieldTypeString:
					{
						strSQL += L"'";
						strSQL += strArray[nIndex];
						strSQL += L"'";
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
			strSQL += L")";

			CSQLiteCommand SQLiteCommand(m_pSQLite, TranslateString((const WCHAR*)strSQL, CP_UTF8).c_str());
			
			if (!SQLiteCommand.Excute())
			{
				MessageBox(L"false");
				assert(false);
				break;
			}
			SQLiteCommand.Clear();
		}
		m_pSQLite->CommitTransaction();
	} while (false);
	if (bNeedQuit)
	{
		app.Quit();
	}
}
//
//unsigned __stdcall CTestExcelDlg::ThreadProc(void *pArgument)
//{
//	CTestExcelDlg *pThis = reinterpret_cast<CTestExcelDlg*>(pArgument);
//	pThis->m_pSQLite->BeginTransaction();
//	int nCommitCount = 0;
//	while(true)
//	{
//		if (++nCommitCount > 1000)
//		{
//			nCommitCount = 0;
//			pThis->m_pSQLite->CommitTransaction();
//			pThis->m_pSQLite->BeginTransaction();
//		}
//		InsertInfo *pInserInfo = nullptr;
//		{
//			CAutoLock AutoLock(pThis->m_NormalLock);
//			if (0 != pThis->m_InsertInfoArray.size())
//			{
//				pInserInfo = *(pThis->m_InsertInfoArray.begin());
//				pThis->m_InsertInfoArray.pop_front();
//			}
//		}
//		if (nullptr == pInserInfo)
//		{
//			Sleep(1);
//			continue;
//		}
//		
//
//		delete pInserInfo;
//		Sleep(1);
//	}
//	return 0;
//}




void CTestExcelDlg::OnBnClickedButtonSelectExcel()
{
	CFileDialog openFile(FALSE, L"xls", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"xls (*.xls)|*.xls||", this);
	if (IDOK == openFile.DoModal())
	{
		m_strSaveExcelFileName = openFile.GetPathName();
		m_editSaveExcel.SetWindowText(m_strSaveExcelFileName);
	}
	
}


void CTestExcelDlg::OnBnClickedButtonSaveExcel()
{
	CApplication app;
	BOOL bNeedQuit = FALSE;

	do 
	{
		if (!app.CreateDispatch(L"ET.APPLICATION"))
		{
			assert(false);
			break;
		}
		bNeedQuit = TRUE;

		CWorkbooks workbooks(app.get_Workbooks());

		_variant_t vtFileName(m_strSaveExcelFileName);
		_variant_t vtReadOnly(FALSE);
		_variant_t vtEditable(TRUE);
		_variant_t vtEmpty;
		CWorkbook workbook(workbooks.Open(vtFileName, vtEmpty, vtReadOnly, vtEmpty, vtEmpty, vtEmpty, vtEmpty, 
			vtEmpty, vtEmpty, vtEditable, vtEmpty, vtEmpty, vtEmpty));
		
		CWorksheets Worksheets(workbook.get_Worksheets());
		CWorksheet worksheet(Worksheets.get_Item(_variant_t(1)));
		CRange range(worksheet.get_Cells());

		

		CSQLite Sqlite;
		if (!Sqlite.Open("C:\\1.db3"))
		{
			ASSERT(FALSE);
			break;
		}
		std::wstring strWSql;
		strWSql = L"select * from equipment limit 5,10";
		std::string strSQL = TranslateString(strWSql, CP_UTF8);
		CSQLiteDataReader SQLiteDataReade = Sqlite.ExcuteQuery(strSQL.c_str());
		int nRowIndex = 1;
		while (SQLiteDataReade.Read())
		{
			for (int nIndex = 0; nIndex < _countof(g_FieldInfos); nIndex++)
			{
				CString strValue;
				switch(g_FieldInfos[nIndex].Type)
				{
				case FieldTypeInt64:
					{
						INT64 i64Value = SQLiteDataReade.GetInt64Value(nIndex);
						strValue.Format(L"%I64d", i64Value);
					}
					break;
				case FieldTypeString:
					{
						int nLength = 0;
						const unsigned char *pstrUTF8 = SQLiteDataReade.GetStringValue(nIndex, nLength);
						std::string strUTF8;
						strUTF8.append(reinterpret_cast<const char*>(pstrUTF8), nLength);
						strValue = TranslateString(strUTF8, CP_UTF8).c_str();
					}
					break;
				default:
					{
						assert(false);
					}
					break;
				}
				_variant_t vtDispatch = range.get_Item(_variant_t(nRowIndex), _variant_t(nIndex + 1));
				CRange rangeWrite(vtDispatch);
				rangeWrite.put_Formula(strValue);
			}
			nRowIndex++;
		}
		workbook.Save();
		SQLiteDataReade.Close();
		Sqlite.Close();
	} while (false);

	if (bNeedQuit)
	{
		app.Quit();
	}
}
