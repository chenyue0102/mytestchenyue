
// TestDShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestDShow.h"
#include "TestDShowDlg.h"
#include "afxdialogex.h"
#include <Dshow.h>
#include "Test.h"
#include <atlbase.h>
#include <gdiplus.h>
#include "CaptureVideo.h"
#include "CaptureAudio.h"
#pragma comment(lib, "Strmiids.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void errhandler(const char *, HWND)
{

}
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


// CTestDShowDlg 对话框



CTestDShowDlg::CTestDShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTDSHOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDShowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


char* GuidToString(const GUID &guid)
{
	int buf_len = 64;
	char *buf = (char *)malloc(buf_len);
	_snprintf(
		buf,
		buf_len,
		"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	//printf("%s\n",buf);
	return buf;
}
PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// Retrieve the bitmap color format, width, and height.  
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
	{
		errhandler("GetObject", hwnd);
	}

	// Convert the color format to a count of bits.  
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// Allocate memory for the BITMAPINFO structure. (This structure  
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
	// data structures.)  

	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));

	// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure.  

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag.  
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color  
	// indices and store the result in biSizeImage.  
	// The width must be DWORD aligned unless the bitmap is RLE 
	// compressed. 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the  
	// device colors are important.  
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
	HBITMAP hBMP, HDC hDC)
{
	HANDLE hf;                 // file handle  
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // memory pointer  
	DWORD dwTotal;              // total count of bytes  
	DWORD cb;                   // incremental count of bytes  
	BYTE *hp;                   // byte pointer  
	DWORD dwTmp;

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits)
		errhandler("GlobalAlloc", hwnd);

	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS))
	{
		errhandler("GetDIBits", hwnd);
	}

	// Create the .BMP file.  
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE)
		errhandler("CreateFile", hwnd);
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
								// Compute the size of the entire file.  
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		errhandler("WriteFile", hwnd);
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		errhandler("WriteFile", hwnd);

	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
		errhandler("WriteFile", hwnd);

	// Close the .BMP file.  
	if (!CloseHandle(hf))
		errhandler("CloseHandle", hwnd);

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}
// CTestDShowDlg 消息处理程序
CCaptureVideo m_cap_vdo;
CCaptureAudio   m_cap_ado;
HWND g_h = 0;
void CTestDShowDlg::VdoFrameData(double dblSampleTime, BYTE * pBuffer, long lBufferSize)
{
	int a = 0;
	a++;
	static bool b = true;
	if (b)
	{
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR	 gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		b = false;
		//FILE *fp = fopen("d:/1.bmp", "wb");
		//fwrite(pBuffer, 1, lBufferSize, fp);
		HBITMAP h = CreateBitmap(640, 480, 1, 24, pBuffer);
		Gdiplus::Bitmap bmp(h, nullptr);
		auto s = bmp.GetLastStatus();
		CLSID myClsId;
		int retVal = GetEncoderClsid(L"image/bmp", &myClsId);
		bmp.Save(L"d:/1.jpg", &myClsId, NULL);
		//fclose(fp);
		//CClientDC cdc(CWnd::FromHandle(g_h));
		//CreateBMPFile(g_h, L"d:/1.jpg", CreateBitmapInfoStruct(g_h, h), h, cdc.GetSafeHdc());
	}
}

void CTestDShowDlg::AdoFrameData(BYTE* pBuffer, long lBufferSize)
{
	int a = 0;
	a++;
}

BOOL CTestDShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	g_h = GetSafeHwnd();
	HRESULT hr = CoInitialize(NULL);
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
	//IGraphBuilder *pGraph;
	//hr = CoCreateInstance(CLSID_FilterGraph, NULL,
	//	CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	//IMediaControl *pControl;
	//IMediaEvent   *pEvent;
	//hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	//hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
	////hr = pGraph->RenderFile(L"C:/Users/EDZ/Desktop/v1080.mp4", NULL);
	//hr = pGraph->RenderFile(L"C:/Users/EDZ/Desktop/Wildlife.wmv", NULL);
	//hr = pControl->Run();

	//long evCode = 0;
	//pEvent->WaitForCompletion(INFINITE, &evCode);

	//pControl->Release();
	//pEvent->Release();
	//pGraph->Release();

	/*
	IEnumMoniker *pEnumMoniker = 0;
	EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnumMoniker);
	////DisplayDeviceInformation(p);
	//std::vector<std::wstring> names = GetFriendlyNames(p);
	IMoniker *pMoniker = FindCaptureDeviceMoniker(pEnumMoniker, nullptr);
	IBaseFilter *pCap=0;   //Video Capture Filter
	hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pCap);

	IGraphBuilder *pGraph=0;
	ICaptureGraphBuilder2 *pBuild=0;
	hr = InitCaptureGraphBuilder(&pGraph, &pBuild);
	hr = pGraph->AddFilter(pCap, L"Capture Filter");
	pGraph->RenderFile(L"C:\\Users\\EDZ\\Desktop/Wildlife.wmv", 0);

	IEnumPins *pinEnum = 0;
	IPin * pin = NULL;
	ULONG pinFetched = 0;
	hr = pCap->EnumPins(&pinEnum);
	pinEnum->Reset();
	while (SUCCEEDED(pinEnum->Next(1, &pin, &pinFetched)) && pinFetched)
	{
		if (!pin) {
			continue;
		}
		PIN_INFO pinInfo;
		if (FAILED(pin->QueryPinInfo(&pinInfo))) {
			continue;
		}
		printf("\t[Pin] ");
		switch (pinInfo.dir) {
		case PINDIR_INPUT:printf("Dir:Input  \t"); break;
		case PINDIR_OUTPUT:printf("Dir:Output \t"); break;
		default:printf("Dir:Unknown\n"); break;
		}

		IEnumMediaTypes *mtEnum = NULL;
		AM_MEDIA_TYPE   *mt = NULL;
		if (FAILED(pin->EnumMediaTypes(&mtEnum)))
			break;
		mtEnum->Reset();

		ULONG mtFetched = 0;

		while (SUCCEEDED(mtEnum->Next(1, &mt, &mtFetched)) && mtFetched) {

			printf("\t\t[MediaType]\n");
			//Video
			char *MEDIATYPE_Video_str = GuidToString(MEDIATYPE_Video);
			//Audio
			char *MEDIATYPE_Audio_str = GuidToString(MEDIATYPE_Audio);
			//Stream
			char *MEDIATYPE_Stream_str = GuidToString(MEDIATYPE_Stream);
			//Majortype
			char *majortype_str = GuidToString(mt->majortype);
			//Subtype
			char *subtype_str = GuidToString(mt->subtype);

			printf("\t\t  Majortype:");
			if (strcmp(majortype_str, MEDIATYPE_Video_str) == 0) {
				printf("Video\n");
			}
			else if (strcmp(majortype_str, MEDIATYPE_Audio_str) == 0) {
				printf("Audio\n");
			}
			else if (strcmp(majortype_str, MEDIATYPE_Stream_str) == 0) {
				printf("Stream\n");
			}
			else {
				printf("Other\n");
			}
			printf("\t\t  Subtype GUID:%s", subtype_str);

			free(MEDIATYPE_Video_str);
			free(MEDIATYPE_Audio_str);
			free(MEDIATYPE_Stream_str);
			free(subtype_str);
			free(majortype_str);
			printf("\n");

		}
		
		pin = nullptr;
		//printf("Name:%s\n", W2A(pinInfo.achName));
	}
	IVideoWindow *pWindow = 0;
	pGraph->QueryInterface(IID_IVideoWindow, (void **)&pWindow);
	pWindow->put_Visible(OAFALSE);
	pWindow->put_Owner((OAHWND)GetSafeHwnd());
	pWindow->put_Left(0);
	pWindow->put_Top(0);
	pWindow->put_Width(400);
	pWindow->put_Height(400);
	pWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_THICKFRAME);
	pWindow->put_MessageDrain((OAHWND)GetSafeHwnd());//Receive Message
	pWindow->put_Visible(OATRUE);

	IMediaControl *pControl=0;
	pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	pControl->Run();
	*/
	m_cap_vdo.Open(0, GetSafeHwnd());
	m_cap_vdo.GrabVideoFrames(TRUE, this);
	//m_cap_vdo.GrabVideoFrames(FALSE, NULL);
	//m_cap_vdo.Close();

	//打开mic，同时初始化directsound：
		m_cap_ado.Open();

	//开始采集声音就是：
		m_cap_ado.GrabAudioFrames(TRUE, this);
	//调用它以后，只要你重载了上面的那个函数，directsound就会周期性的从麦克采集数据，然后调用该函数。

		//停止声音采集是：
		//m_cap_ado.GrabAudioFrames(FALSE, NULL);

	//关闭mic，同时释放directsound：
		//m_cap_ado.Close();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestDShowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDShowDlg::OnPaint()
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
HCURSOR CTestDShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

