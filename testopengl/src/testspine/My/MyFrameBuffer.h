#pragma once
#include <GL/glew.h>
#include "OpenGLESHelper.h"
#include <string>
#include <Windows.h>


static bool SaveBitmap(const char* pFileName, int width, int height, int biBitCount, const void* pBuf, int nBufLen)
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

class MyFrameBuffer {
public:
	MyFrameBuffer() {
		glGenTextures(1, &mTexture); CHECKERR;
		glBindTexture(GL_TEXTURE_2D, mTexture); CHECKERR;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 400, 400, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0); CHECKERR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECKERR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECKERR;
		glGenRenderbuffers(1, &mRenderBuffer); CHECKERR;
		glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer); CHECKERR;
		glGenFramebuffers(1, &mFrameBuffer); CHECKERR;
	}
	~MyFrameBuffer() {

	}

public:
	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer); CHECKERR;
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mTexture, 0); CHECKERR;
		GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffers); CHECKERR;
	}

	void save() {
		glBindTexture(GL_TEXTURE_2D, mTexture); CHECKERR();
		std::string tmpBuf;
		tmpBuf.resize(400 * 400 * 3);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, &tmpBuf[0]); CHECKERR();
		SaveBitmap("d:/1.bmp", 400, 400, 24, &tmpBuf[0], tmpBuf.size());
	}

private:
	GLuint mTexture;
	GLuint mRenderBuffer;
	GLuint mFrameBuffer;
};
