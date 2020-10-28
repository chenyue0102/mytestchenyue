#include "MyTexture.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "OpenGLESHelper.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include"stb_image.h"



MyTexture::MyTexture(const char *fileName)
	: mFileName(fileName)
	, mTexture(0)
{

}

MyTexture::~MyTexture() {

}
#include <windows.h>
bool SaveBitmap(const char* pFileName, int width, int height, int biBitCount, const void* pBuf, int nBufLen)
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
		FILE* fp = fopen(pFileName, "wb");
		fwrite(&bfh, 1, sizeof(bfh), fp);
		BITMAPINFOHEADER bih = { 0 };
		bih.biSize = sizeof(bih);
		bih.biWidth = width;
		bih.biHeight = height;
		bih.biPlanes = 1;
		bih.biBitCount = biBitCount;
		bih.biCompression = BI_RGB;
		fwrite(&bih, 1, sizeof(bih), fp);
		fwrite(pBuf, 1, nBufLen, fp);
		fclose(fp);
		return true;
	}
}
void MyTexture::bind(GLuint program) {
	if (0 == mTexture) {
		int width = 0, height = 0, channel = 0;
		stbi_uc *buffer = stbi_load(mFileName.c_str(), &width, &height, &channel, 0);

		glGenTextures(1, &mTexture); CHECKERR();
		glBindTexture(GL_TEXTURE_2D, mTexture); CHECKERR();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); CHECKERR();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
			height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			buffer); CHECKERR();
		
		STBI_FREE(buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); CHECKERR();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECKERR();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f); CHECKERR();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECKERR();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECKERR();
		glGenerateMipmap(GL_TEXTURE_2D); CHECKERR();
	}
	CHECKERR();
	glBindTexture(GL_TEXTURE_2D, mTexture); CHECKERR();
}