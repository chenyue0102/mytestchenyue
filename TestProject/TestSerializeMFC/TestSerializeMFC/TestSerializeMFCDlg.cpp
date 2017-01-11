
// TestSerializeMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSerializeMFC.h"
#include "TestSerializeMFCDlg.h"
#include "afxdialogex.h"
#include "SerializeHelper.h"
#include "TKSerialize.h"
#include "TestStruct.h"
#include <vector>
#include <string>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


template<typename T>
bool CompareArray(const T leftArray[], const T rightArray[], size_t stCount)
{
	for (size_t nIndex = 0; nIndex < stCount; ++nIndex)
	{
		if (!(leftArray[nIndex] == rightArray[nIndex]))
		{
			return false;
		}
	}
	return true;
}
struct Test
{
	//QString strText;
	int		number;
	int		nArray[3];
	char	szText[16];

	Test()
		//: strText()
		: number(0)
		, nArray()
		, szText()
	{

	}
	void init()
	{
		//strText = QStringLiteral("�������");
		number = 9999;
		nArray[0] = 1;
		nArray[1] = 2;
		nArray[2] = 3;
		strcpy(szText, "hello,world");
	}
	bool operator==(const Test &other)
	{
		return (//strText == other.strText
			//&& 
			number == other.number
			&& CompareArray(nArray, other.nArray, _countof(nArray))
			&& CompareArray(szText, other.szText, _countof(szText)));
	}
};
using namespace SerializeExport;
bool SerializeStruct(ISerialize *pSerialize, Test &Value)
{
	try
	{
		//SERIALIZE_VALUE(strText);
		SERIALIZE_VALUE(number);
		SERIALIZE_VALUE(nArray);
		SERIALIZE_VALUE(szText);
	}
	catch (...)
	{
		return false;
	}
	return true;
}


struct Tlv
{
	int Type;
	std::string strValue;

	Tlv()
		: Type(0)
		, strValue()
	{

	}
	void init()
	{
		Type = 1;
		unsigned long ul = 123456;
		strValue.append((char*)&ul, sizeof(ul));

	}
	void init2()
	{
		Type = 2;
		strValue = "hello, world";
	}
	bool operator==(const Tlv &other)const
	{
		return (Type == other.Type
			&& strValue == other.strValue);
	}
};

bool SerializeStruct(ISerialize *pSerialize, Tlv &Value)
{
	try
	{
		SERIALIZE_VALUE(Type);
		if (pSerialize->GetSerializeType() == EnumSerializeIORead)
		{
			if (1 == Value.Type)
			{
				unsigned int ulValue = 0;
				SerializeHelper::Serialize(pSerialize, ulValue, "Value");
				Value.strValue.clear();
				Value.strValue.append((char*)&ulValue, sizeof(ulValue));
			}
			else if (2 == Value.Type)
			{
				SerializeHelper::Serialize(pSerialize, Value.strValue, "Value");
			}
		}
		else
		{
			if (1 == Value.Type)
			{
				unsigned int ulValue = 0;
				memcpy(&ulValue, Value.strValue.data(), sizeof(ulValue));
				SerializeHelper::Serialize(pSerialize, ulValue, "Value");
			}
			else if (2 == Value.Type)
			{
				SerializeHelper::Serialize(pSerialize, Value.strValue, "Value");
			}
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}
template<typename T>
bool operator==(const std::vector<T> &left, const std::vector<T> &right)
{
	if (left.size() != right.size())
	{
		return false;
	}
	for (size_t a = 0; a < left.size(); a++)
	{
		if (!(left[a] == right[a]))
		{
			return false;
		}
	}
	return true;
}
struct TlvArray
{
	std::vector<Tlv> tArray;

	void init()
	{
		Tlv t1;
		t1.init();
		tArray.push_back(t1);
		Tlv t2;
		t2.init2();
		tArray.push_back(t2);
	}
	bool operator==(const TlvArray &other)const
	{
		return (tArray == other.tArray);
	}
};

bool SerializeStruct(ISerialize *pSerialize, TlvArray &Value)
{
	try
	{
		SERIALIZE_VALUE(tArray);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

template<typename T>
inline void CopyValue(T &From, T& To)
{
	To = std::move(From);
}

template<typename T, size_t _Size> 
inline void CopyValue(T (&tArrayFrom)[_Size], T (&tArrayTo)[_Size])
{
	for (size_t Index = 0; Index < _Size; Index++)
	{
		CopyValue(tArrayFrom[Index], tArrayTo[Index]);
	}
}

void DoTest()
{
	std::string a[2][2][2] /*= {0}*/;
	std::string b[2][2][2] = {"1" , "2", "3", "4"};
	CopyValue(b, a);
	{
		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerialize(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerialize2(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		DoTest2<TestAllType>(pSerialize.get(), pSerialize2.get());
	}
	{
		auto pSerialize = SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson);
		auto pSerialize2 = SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson);
		DoTest2<TestContainer>(pSerialize, pSerialize2);
	}

	/*{
		auto pSerialize = SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson);
		auto pSerialize2 = SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson);
		DoTest2<TlvArray>(pSerialize, pSerialize2);
	}*/
	{
		std::shared_ptr<ISerialize> pSerialize(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		std::shared_ptr<ISerialize> pSerialize2(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		DoTestMiss(pSerialize.get(), pSerialize2.get());
	}
}

struct TestA
{
	int a;
};

bool SerializeStruct(ISerialize *pSerialize, TestA &Value)
{
	try
	{
		SERIALIZE_VALUE(a);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

struct TestB
{
	char szName[100];
	TestB()
	{
		memset(szName, 0, sizeof(szName));
	}
};

bool SerializeStruct(ISerialize *pSerialize, TestB &Value)
{
	try
	{
		SERIALIZE_VALUE(szName);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CTestSerializeMFCDlg �Ի���




CTestSerializeMFCDlg::CTestSerializeMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestSerializeMFCDlg::IDD, pParent)
	, m_InvokeHelper(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_InvokeHelper.RegisterNotifyMsg(1, &CTestSerializeMFCDlg::DealA);
	m_InvokeHelper.UnRegisterNotifyMsg(1);
	m_InvokeHelper.RegisterNotifyMsg(1, &CTestSerializeMFCDlg::DealA);
	m_InvokeHelper.RegisterNotifyMsg(2, &CTestSerializeMFCDlg::DealB);
	m_InvokeHelper.RegisterQueryMsg(3, &CTestSerializeMFCDlg::DealC);
}

void CTestSerializeMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestSerializeMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTestSerializeMFCDlg ��Ϣ�������

BOOL CTestSerializeMFCDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//DoTest();

	TestCallFun();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestSerializeMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestSerializeMFCDlg::OnPaint()
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
HCURSOR CTestSerializeMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestSerializeMFCDlg::DealA(const TestA &a)
{
	CString str;
	str.Format(L"DealA %d", a.a);
	MessageBox(str);
}

void CTestSerializeMFCDlg::DealB(const TestB & b)
{
	CStringA str;
	str.Format("DealB %s", b.szName);
	MessageBox(CStringW(str));
}

unsigned long CTestSerializeMFCDlg::DealC(const TestA & a, TestB & b)
{
	CString str;
	str.Format(L"DealA %d", a.a);
	MessageBox(str);
	strcpy(b.szName, "DealC");
	return 1;
}

void CTestSerializeMFCDlg::TestCallFun()
{
	{
		TestA ta;
		ta.a = 123456;
		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerialize(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		pSerialize->SetSerializeType(EnumSerializeIOWrite);
		SerializeStruct(pSerialize.get(), ta);
		//m_InvokeHelper.InvokeNotify(1, pSerialize->GetData(), pSerialize->GetDataLen());
	}

	{
		TestB tb;
		strcpy(tb.szName, "abc123");

		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerialize(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		pSerialize->SetSerializeType(EnumSerializeIOWrite);
		SerializeStruct(pSerialize.get(), tb);
		//m_InvokeHelper.InvokeNotify(2, pSerialize->GetData(), pSerialize->GetDataLen());
	}
	{
		TestB tb = TestB();
		TestA ta = TestA();
		ta.a = 987;

		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerialize(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		pSerialize->SetSerializeType(EnumSerializeIOWrite);
		SerializeStruct(pSerialize.get(), ta);
		std::string strData;
		unsigned long ulResult = 0;
		m_InvokeHelper.InvokeQuery(3, pSerialize->GetData(), pSerialize->GetDataLen(), strData, &ulResult);
		std::unique_ptr<SerializeExport::ISerialize, decltype(&SerializeExport::DestroySerializeInterface)>
			pSerializeRead(SerializeExport::CreateSerializeInterface(EnumSerializeFormatJson), &SerializeExport::DestroySerializeInterface);
		pSerializeRead->SetSerializeType(EnumSerializeIORead);
		pSerializeRead->SetData(strData.data(), strData.size());
		SerializeStruct(pSerializeRead.get(), tb);
		CStringA str;
		str.Format("DealB %s", tb.szName);
		MessageBox(CStringW(str));
	}
}

