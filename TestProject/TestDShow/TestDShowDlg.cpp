
// TestDShowDlg.cpp : 实现文件
//

#include "stdafx.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
}
#include "TestDShow.h"
#include "TestDShowDlg.h"
#include "afxdialogex.h"
#include <Dshow.h>
#include "Test.h"
#include <atlbase.h>
#include <gdiplus.h>
#include <thread>
#include <mutex>
#include <list>
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
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


//void test()
//{
//	CFile file[5];
//	BYTE *szTxt[5];
//
//	int nWidth = 0;
//	int nHeight = 0;
//
//	int nDataLen = 0;
//
//	int nLen;
//
//	CString csFileName;
//	for (int fileI = 1; fileI <= 5; fileI++)
//	{
//		csFileName.Format(L"e:\\pics\\%d.bmp", fileI);
//		file[fileI - 1].Open(csFileName, CFile::modeRead | CFile::typeBinary);
//		nLen = file[fileI - 1].GetLength();
//
//		szTxt[fileI - 1] = new BYTE[nLen];
//		file[fileI - 1].Read(szTxt[fileI - 1], nLen);
//		file[fileI - 1].Close();
//
//		//BMP bmi;//BITMAPINFO bmi;
//		//int nHeadLen = sizeof(BMP);
//		BITMAPFILEHEADER bmpFHeader;
//		BITMAPINFOHEADER bmpIHeader;
//		memcpy(&bmpFHeader, szTxt[fileI - 1], sizeof(BITMAPFILEHEADER));
//
//		int nHeadLen = bmpFHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
//		memcpy(&bmpIHeader, szTxt[fileI - 1] + sizeof(BITMAPFILEHEADER), nHeadLen);
//
//		nWidth = bmpIHeader.biWidth;// 464;// bmi.bmpInfo.bmiHeader.biWidth;// ;
//		nHeight = bmpIHeader.biHeight;//362;// bmi.bmpInfo.bmiHeader.biHeight;// ;
//
//		szTxt[fileI - 1] += bmpFHeader.bfOffBits;
//		nDataLen = nLen - bmpFHeader.bfOffBits;
//	}
//
//	av_register_all();
//	avcodec_register_all();
//	AVFrame *m_pRGBFrame = new AVFrame[1];  //RGB帧数据  
//	AVFrame *m_pYUVFrame = new AVFrame[1];;  //YUV帧数据
//	AVCodecContext *c = NULL;
//	AVCodecContext *in_c = NULL;
//	AVCodec *pCodecH264; //编码器
//	uint8_t * yuv_buff;//
//
//					   //查找h264编码器
//	pCodecH264 = avcodec_find_encoder(AV_CODEC_ID_H264);
//	if (!pCodecH264)
//	{
//		fprintf(stderr, "h264 codec not found\n");
//		exit(1);
//	}
//
//	c = avcodec_alloc_context3(pCodecH264);
//	c->bit_rate = 3000000;// put sample parameters 
//	c->width = nWidth;// 
//	c->height = nHeight;// 
//
//						// frames per second 
//	AVRational rate;
//	rate.num = 1;
//	rate.den = 25;
//	c->time_base = rate;//(AVRational){1,25};
//	c->gop_size = 10; // emit one intra frame every ten frames 
//	c->max_b_frames = 1;
//	c->thread_count = 1;
//	c->pix_fmt = PIX_FMT_YUV420P;//PIX_FMT_RGB24;
//
//								 //av_opt_set(c->priv_data, /*"preset"*/"libvpx-1080p.ffpreset", /*"slow"*/NULL, 0);
//								 //打开编码器
//	if (avcodec_open2(c, pCodecH264, NULL)<0)
//		TRACE("不能打开编码库");
//
//	int size = c->width * c->height;
//
//	yuv_buff = (uint8_t *)malloc((size * 3) / 2); // size for YUV 420 
//
//												  //将rgb图像数据填充rgb帧
//	uint8_t * rgb_buff = new uint8_t[nDataLen];
//
//	//图象编码
//	int outbuf_size = 100000;
//	uint8_t * outbuf = (uint8_t*)malloc(outbuf_size);
//	int u_size = 0;
//	FILE *f = NULL;
//	char * filename = "e:\\pics\\myData.h264";
//	f = fopen(filename, "wb");
//	if (!f)
//	{
//		TRACE("could not open %s\n", filename);
//		exit(1);
//	}
//
//	//初始化SwsContext
//	SwsContext * scxt = sws_getContext(c->width, c->height, PIX_FMT_BGR24, c->width, c->height, PIX_FMT_YUV420P, SWS_POINT, NULL, NULL, NULL);
//
//	AVPacket avpkt;
//
//	//AVFrame *pTFrame=new AVFrame
//	for (int i = 0; i<250; ++i)
//	{
//
//		//AVFrame *m_pYUVFrame = new AVFrame[1];
//
//		int index = (i / 25) % 5;
//		memcpy(rgb_buff, szTxt[index], nDataLen);
//
//		avpicture_fill((AVPicture*)m_pRGBFrame, (uint8_t*)rgb_buff, PIX_FMT_RGB24, nWidth, nHeight);
//
//		//将YUV buffer 填充YUV Frame
//		avpicture_fill((AVPicture*)m_pYUVFrame, (uint8_t*)yuv_buff, PIX_FMT_YUV420P, nWidth, nHeight);
//
//		// 翻转RGB图像
//		m_pRGBFrame->data[0] += m_pRGBFrame->linesize[0] * (nHeight - 1);
//		m_pRGBFrame->linesize[0] *= -1;
//		m_pRGBFrame->data[1] += m_pRGBFrame->linesize[1] * (nHeight / 2 - 1);
//		m_pRGBFrame->linesize[1] *= -1;
//		m_pRGBFrame->data[2] += m_pRGBFrame->linesize[2] * (nHeight / 2 - 1);
//		m_pRGBFrame->linesize[2] *= -1;
//
//
//		//将RGB转化为YUV
//		sws_scale(scxt, m_pRGBFrame->data, m_pRGBFrame->linesize, 0, c->height, m_pYUVFrame->data, m_pYUVFrame->linesize);
//
//		int got_packet_ptr = 0;
//		av_init_packet(&avpkt);
//		avpkt.data = outbuf;
//		avpkt.size = outbuf_size;
//		u_size = avcodec_encode_video2(c, &avpkt, m_pYUVFrame, &got_packet_ptr);
//		if (u_size == 0)
//		{
//			fwrite(avpkt.data, 1, avpkt.size, f);
//		}
//	}
//
//	fclose(f);
//	delete[]m_pRGBFrame;
//	delete[]m_pYUVFrame;
//	delete[]rgb_buff;
//	free(outbuf);
//	avcodec_close(c);
//	av_free(c);
//}

std::list<std::string> g_data;
std::mutex g_mutex;

void RGB24ToYUV420(int Width, int Height, uint8_t* RgbBuffer, uint8_t*bufY, uint8_t*bufU, uint8_t*bufV)
{
	int nWidth = Width;
	int nHeight = Height;
	/////////////////////下面转换算法是网上查到的
	int i, j;
	uint8_t*Y = bufY;
	uint8_t*U = bufU;
	uint8_t*V = bufV;
	uint8_t*bufRGB;
	unsigned char y, u, v, r, g, b, testu, testv;
	if (NULL == RgbBuffer)
	{
		return;
	}
	for (j = 0; j<nHeight; j++)
	{
		bufRGB = RgbBuffer + nWidth * (nHeight - 1 - j) * 3;
		for (i = 0; i<nWidth; i++)
		{
			int pos = nWidth * i + j;
			r = *(bufRGB++);
			g = *(bufRGB++);
			b = *(bufRGB++);
			y = (unsigned char)((66 * r + 129 * g + 25 * b + 128) >> 8) + 16;//16
			v = (unsigned char)((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128; //128          
			u = (unsigned char)((112 * r - 94 * g - 18 * b + 128) >> 8) + 128;
			*(bufY++) = max(0, min(y, 255));

			if (j % 2 == 0 && i % 2 == 0)
			{
				if (u>255)
				{
					u = 255;
				}
				if (u<0)
				{
					u = 0;
				}
				*(bufU++) = u;
				//存u分量
			}
			else
			{
				//存v分量
				if (i % 2 == 0)
				{
					if (v>255)
					{
						v = 255;
					}
					if (v<0)
					{
						v = 0;
					}
					*(bufV++) = v;
				}
			}
		}
	}
}

void RGB24ToYUV420(int Width, int Height, uint8_t* RgbBuffer, uint8_t*yuvBuf)
{
	uint8_t*bufY = yuvBuf;
	uint8_t*bufU = yuvBuf + Width * Height;
	uint8_t*bufV = bufU + (Width* Height * 1 / 4);
	return RGB24ToYUV420(Width, Height, RgbBuffer, bufY, bufU, bufV);
}
void encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt,
	FILE *outfile)
{
	int ret;
	/* send the frame to the encoder */
	if (frame)
	{
		//printf("Send frame %3"PRId64"\n", frame->pts);
	}
	ret = avcodec_send_frame(enc_ctx, frame);
	if (ret < 0) {
		fprintf(stderr, "Error sending a frame for encoding\n");
		exit(1);
	}
	while (ret >= 0) {
		ret = avcodec_receive_packet(enc_ctx, pkt);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
			return;
		else if (ret < 0) {
			fprintf(stderr, "Error during encoding\n");
			exit(1);
		}
		//printf("Write packet %3"PRId64" (size=%5d)\n", pkt->pts, pkt->size);
		fwrite(pkt->data, 1, pkt->size, outfile);
		av_packet_unref(pkt);
	}
}
void writeThread()
{
	av_register_all();
	avformat_network_init();
	const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
	AVCodecContext *c = avcodec_alloc_context3(codec);
	AVPacket *pkt = av_packet_alloc();
	c->bit_rate = 400000;
	c->width = 640;
	c->height = 480;
	AVRational time_base = { 1, 25 };
	c->time_base = time_base;
	AVRational framerate = { 25, 1 };
	c->framerate = framerate;
	c->gop_size = 10;
	c->max_b_frames = 1;
	c->pix_fmt = AV_PIX_FMT_YUV420P;

	if (codec->id == AV_CODEC_ID_H264)
		av_opt_set(c->priv_data, "preset", "slow", 0);

	int ret = 0;
	ret = avcodec_open2(c, codec, nullptr);
	if (ret < 0)
	{
		assert(false);
		return;
	}
	FILE *fp = fopen("d:/test.mp4", "wb");

	AVFrame *frame = av_frame_alloc();
	frame->format = c->pix_fmt;
	frame->width = c->width;
	frame->height = c->height;
	ret = av_frame_get_buffer(frame, 32);
	if (ret < 0)
	{
		assert(false);
		return;
	}
	int pts = 0;
	unsigned char *pYUV = new unsigned char[c->width * c->height * 3 / 2];
	bool bContinue = true;
	while (bContinue)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));
		std::string strData;
		{
			std::lock_guard<std::mutex> lk(g_mutex);
			if (!g_data.empty())
			{
				strData = g_data.front();
				g_data.pop_front();
			}
		}
		if (strData.empty())
		{
			continue;
		}
		ret = av_frame_make_writable(frame);
		if (ret < 0)
		{
			assert(false);
			return;
		}
		
		RGB24ToYUV420(c->width, c->height, (unsigned char*)strData.data(), frame->data[0], frame->data[1], frame->data[2]);
		frame->pts = pts;
		pts++;
		encode(c, frame, pkt, fp);
		//frame->data[0] = 
	}

	/* flush the encoder */
	encode(c, NULL, pkt, fp);
	uint8_t endcode[] = { 0, 0, 1, 0xb7 };
	/* add sequence end code to have a real MPEG file */
	fwrite(endcode, 1, sizeof(endcode), fp);
	fclose(fp);
	avcodec_free_context(&c);
	av_frame_free(&frame);
	av_packet_free(&pkt);
}

void CTestDShowDlg::VdoFrameData(double dblSampleTime, BYTE * pBuffer, long lBufferSize)
{
	//int a = 0;
	//a++;
	//static bool b = true;
	//if (b)
	//{
	//	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	//	ULONG_PTR	 gdiplusToken;
	//	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	//	b = false;
	//	//FILE *fp = fopen("d:/1.bmp", "wb");
	//	//fwrite(pBuffer, 1, lBufferSize, fp);
	//	HBITMAP h = CreateBitmap(640, 480, 1, 24, pBuffer);
	//	Gdiplus::Bitmap bmp(h, nullptr);
	//	auto s = bmp.GetLastStatus();
	//	CLSID myClsId;
	//	int retVal = GetEncoderClsid(L"image/bmp", &myClsId);
	//	bmp.Save(L"d:/1.jpg", &myClsId, NULL);
	//	//fclose(fp);
	//	//CClientDC cdc(CWnd::FromHandle(g_h));
	//	//CreateBMPFile(g_h, L"d:/1.jpg", CreateBitmapInfoStruct(g_h, h), h, cdc.GetSafeHdc());
	//}
	std::lock_guard<std::mutex> lk(g_mutex);
	g_data.push_back(std::string((char*)pBuffer, lBufferSize));
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
	std::thread *p = new std::thread(&writeThread);

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

