#include "OpenGLHelper.h"
#include <assert.h>
#include <stdio.h>
#include "MacroDefine.h"
#include "Log.h"
#include "Single.h"


namespace OpenGLHelper {

void outputCompileShader(GLuint shader)
{
	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (GL_FALSE == status)
	{
		const int MAX_LOG_LENGTH = 512;
		GLint len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		if (len < MAX_LOG_LENGTH)
		{
			GLchar szBuf[MAX_LOG_LENGTH] = { 0 };
			int len = MAX_LOG_LENGTH;
			glGetShaderInfoLog(shader, MAX_LOG_LENGTH, nullptr, szBuf);
			mylog_e("%s", szBuf);
		}
		else
		{
			GLchar *szBuf = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, nullptr, szBuf);
			szBuf[len] = '\0';
			mylog_e("%s", szBuf);
			delete[]szBuf;
		}
		assert(GL_FALSE != status);
	}
}

void outputProgramLog(GLuint program)
{
	GLint status = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (GL_FALSE == status)
	{
		const int MAX_LOG_LENGTH = 512;
		GLint len = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		if (len < MAX_LOG_LENGTH)
		{
			GLchar szBuf[MAX_LOG_LENGTH] = { 0 };
			glGetProgramInfoLog(program, MAX_LOG_LENGTH, nullptr, szBuf);
			mylog_e("%s", szBuf);
		}
		else
		{
			GLchar *szBuf = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, nullptr, szBuf);
			szBuf[len] = '\0';
			mylog_e("%s", szBuf);
			delete[]szBuf;
		}
		assert(false);
	}
}

//bool SaveBitmap(const char* pFileName, int width, int height, int biBitCount, const void* pBuf, int nBufLen)
//{
//	if (nullptr == pFileName
//		|| 0 == width
//		|| 0 == height
//		|| !(biBitCount == 24 || biBitCount == 32 || biBitCount == 16)
//		|| nullptr == pBuf
//		|| nBufLen < ((width * height * biBitCount) / 8)
//		)
//	{
//		return false;
//	}
//	else
//	{
//		BITMAPFILEHEADER bfh = { 0 };
//		bfh.bfType = 'MB';
//		bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nBufLen;
//		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//		FILE* fp = fopen(pFileName, "wb");
//		fwrite(&bfh, 1, sizeof(bfh), fp);
//		BITMAPINFOHEADER bih = { 0 };
//		bih.biSize = sizeof(bih);
//		bih.biWidth = width;
//		bih.biHeight = height;
//		bih.biPlanes = 1;
//		bih.biBitCount = biBitCount;
//		bih.biCompression = BI_RGB;
//		fwrite(&bih, 1, sizeof(bih), fp);
//		fwrite(pBuf, 1, nBufLen, fp);
//		fclose(fp);
//		return true;
//	}
//}

GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len) {
	GLenum ret = GL_NO_ERROR;
	GLuint shader = 0;

	do
	{
		if (0 == (shader = glCreateShader(type))) {
			ret = glGetError();
			assert(false);
			break;
		}
		GLint lens[] = { len };
		glShaderSource(shader, 1, &source, (len > 0 ? lens : nullptr)); CHECK_BREAK;
		glCompileShader(shader);
		outputCompileShader(shader); CHECK_BREAK;
		glAttachShader(program, shader); CHECK_BREAK;
	} while (false);

	if (0 != shader) {
		glDeleteShader(shader);
		shader = 0;
	}
	return ret;
}

GLenum createTexture2D(GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint filterParam, GLuint &tex) {
	GLenum ret = GL_NO_ERROR;
	bool needClean = false;
	do
	{
		glGenTextures(1, &tex); CHECK_BREAK;
		needClean = true;
		ret = setTexture2D(tex, internalformat, width, height, format, type, filterParam);
	} while (false);

	if (GL_NO_ERROR != ret && needClean) {
		glDeleteTextures(1, &tex);
	}
	return ret;
}

GLenum setTexture2D(GLuint tex, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint filterParam){
	GLenum ret = GL_NO_ERROR;

	do{
		glBindTexture(GL_TEXTURE_2D, tex); CHECK_BREAK;
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, type, 0); CHECK_BREAK;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParam); CHECK_BREAK;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParam); CHECK_BREAK;
	}while (false);
	glBindTexture(GL_TEXTURE_2D, 0);CHECKERR();
	return ret;
}

GLenum createArrayBuffer(const void* vertexPointsBuffer, GLsizei vlen, const void* colorPointsBuffer, GLsizei clen, GLuint &buf)
{
	GLenum ret = GL_NO_ERROR;
	bool needClean = false;

	do
	{
		glGenBuffers(1, &buf); CHECK_BREAK;
		needClean = true;
		glBindBuffer(GL_ARRAY_BUFFER, buf); CHECK_BREAK;
		glBufferData(GL_ARRAY_BUFFER, vlen + clen, nullptr, GL_STATIC_DRAW); CHECK_BREAK;
		glBufferSubData(GL_ARRAY_BUFFER, 0, vlen, vertexPointsBuffer); CHECK_BREAK;
		glBufferSubData(GL_ARRAY_BUFFER, vlen, clen, colorPointsBuffer); CHECK_BREAK;
	} while (false);

	if (GL_NO_ERROR != ret && needClean) {
		glDeleteBuffers(1, &buf);
	}
	return ret;
}

};