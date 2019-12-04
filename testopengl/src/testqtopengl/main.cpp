#include <GL/glew.h>
#include "testqtopengl.h"
#include <assert.h>
#include <QtWidgets/QApplication>
#include "FormatConver.h"

bool SaveBitmap(const char *pFileName, int width, int height, int biBitCount, const void *pBuf, int nBufLen)
{
	if (nullptr == pFileName
		|| 0 == width
		|| 0 == height
		|| !(biBitCount == 24 || biBitCount == 32 || biBitCount == 16)
		|| nullptr == pBuf
		|| nBufLen < ((width * height * biBitCount) / 8)
		)
	{
		return false;
	}
	else
	{
		BITMAPFILEHEADER bfh = { 0 };
		bfh.bfType = 'MB';
		bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nBufLen;
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		FILE *fp = fopen(pFileName, "wb");
		fwrite(&bfh, 1, sizeof(bfh), fp);
		BITMAPINFOHEADER bih = { 0 };
		bih.biSize = sizeof(bih);
		bih.biWidth = width;
		bih.biHeight = height;
		bih.biPlanes = 1;
		bih.biBitCount = biBitCount;
		fwrite(&bih, 1, sizeof(bih), fp);
		fwrite(pBuf, 1, nBufLen, fp);
		fclose(fp);
		return true;
	}
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	testqtopengl w;
	w.show();
	GLenum status = glewInit();
	assert(GLEW_OK == status);
	QImage img;
	img.load("d:/1.png");
	img = img.convertToFormat(QImage::Format_RGB888);
	int len = img.width() * img.height() * 3;
	char *pout = new char[len];
	FormatConver f;
	const void *pin = img.constBits();
	int width = img.width();
	int height = img.height();
	f.rgb2yuv(pin, width, height, pout, len);
	SaveBitmap("d:/1.bmp", width, height, 24, pout, len);
#if 0
	FILE *ff = fopen("d:/1.yuv", "wb");
	fwrite(pout, 1, width * height + (width * height) / 2, ff);
	fclose(ff);
#endif
	return a.exec();
}
