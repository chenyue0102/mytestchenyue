#pragma once
#include <GL/glew.h>
#include "Test.h"
#include "OpenGLHelper.h"
#include "TestTexture.h"

namespace TestFrameBuffer {
	bool SaveBitmap(const char* pFileName, int width, int height, int biBitCount, const void* pBuf, int nBufLen);
	static GLuint g_framebuffer = 0;
	static GLuint g_renderbuffer = 0;

	static GLuint g_texture = 0;
	static GLuint g_program = 0;
	static GLuint g_buffer = 0;
	static GLuint g_vertex = 0;

	static const char* vStringxx = R"(
#version 430 core
layout(location=0) in vec4 vPosition;
layout(location=1) in vec4 cPosition;
out Param{
	vec4 fPosition;
};
void main()
{
	gl_Position = vPosition;
	fPosition = cPosition;
}
)";


	static const char* fStringxx = R"(
#version 430 core
in Param{
	vec4 fPosition;
};
layout(location=2) uniform sampler2D tex;
out vec4 fColor;
void main()
{
	vec3 clr = texture2D(tex, fPosition.xy).rgb;
	fColor = vec4(clr, 1.0);//rgba
}
)";

	static void init() {
		glGenRenderbuffers(1, &g_renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, g_renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 400, 400);
		CHECKERR();

		glGenFramebuffers(1, &g_framebuffer);
		CHECKERR();

		GLenum ret = GL_NO_ERROR;
		ret = OpenGLHelper::createTexture2D(GL_RGB8, 400, 400, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, g_texture); assert(ret == GL_NO_ERROR);
		g_program = glCreateProgram(); assert(0 != g_program);
		ret = OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, vStringxx, 0); assert(ret == GL_NO_ERROR);
		ret = OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, fStringxx, 0); assert(ret == GL_NO_ERROR);
		glLinkProgram(g_program); 
		outputProgramLog(g_program);
		CHECKERR();

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		static const GLfloat vertex[][2] = {
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ -1.0f, 1.0f },
		{ 1.0f, 1.0f },
		};

		static const GLfloat cvertex[][2] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
		};
		ret = OpenGLHelper::createArrayBuffer(vertex, sizeof(vertex), cvertex, sizeof(cvertex), g_buffer); assert(ret == GL_NO_ERROR);
		
		glGenVertexArrays(1, &g_vertex);
		glBindVertexArray(g_vertex);
		glBindBuffer(GL_ARRAY_BUFFER, g_buffer);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertex)));
		glEnableVertexAttribArray(1);
	}

	static void drawtotexture() {
		//GL_DRAW_FRAMEBUFFER ªÊ÷∆ª∫¥Ê,GL_READ_FRAMEBUFFER∂¡»°ª∫¥Ê GL_FRAMEBUFFER ø…∂¡ø…–¥
		glBindFramebuffer(GL_FRAMEBUFFER, g_framebuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, g_texture, 0);
		GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffers);
		CHECKERR();
		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

		glViewport(0, 0, 400, 400);
		glClear(GL_COLOR_BUFFER_BIT);
		CHECKERR();

		Test::testdraw();
		CHECKERR();
		
		static bool save = false;
		if (!save){
			save = true;
			glBindTexture(GL_TEXTURE_2D, g_texture); CHECKERR();
			std::string tmpBuf;
			tmpBuf.resize(400 * 400 * 3);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, &tmpBuf[0]); CHECKERR();
			SaveBitmap("d:/1.bmp", 400, 400, 24, &tmpBuf[0], tmpBuf.size());
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		CHECKERR();
#if 0
		glDrawBuffer(GL_FRONT_AND_BACK);
		CHECKERR();

		glViewport(0, 0, 400, 400);
		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		TestTexture::testdraw();
		glFlush();
		CHECKERR();
		return;
#endif

		glUseProgram(g_program);
		glViewport(0, 0, 400, 400);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(g_vertex);
		glBindBuffer(GL_ARRAY_BUFFER, g_buffer);

		int offset = 0;
		glActiveTexture(GL_TEXTURE0 + offset);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		GLuint texLocation = glGetUniformLocation(g_program, "tex");
		glUniform1i(texLocation, offset);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		CHECKERR();
		glFlush();
	}

	static void drawtorenderbuffer() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_framebuffer);
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, g_renderbuffer);
		CHECKERR();

		glViewport(0, 0, 400, 400);
		glClear(GL_COLOR_BUFFER_BIT);
		CHECKERR();

		Test::testdraw();
		CHECKERR();

		glBindFramebuffer(GL_READ_FRAMEBUFFER, g_framebuffer);
		CHECKERR();
		GLenum status = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
		assert(GL_FRAMEBUFFER_COMPLETE == status);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		CHECKERR();

		glViewport(0, 0, 400, 400);
		glClear(GL_COLOR_BUFFER_BIT);
		CHECKERR();

		glBlitFramebuffer(0, 0, 400, 400, 0, 0, 400, 400, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		CHECKERR();

		glFlush();
	}

	static void testdraw() {
		drawtotexture();
	}

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
			fwrite(&bih, 1, sizeof(bih), fp);
			fwrite(pBuf, 1, nBufLen, fp);
			fclose(fp);
			return true;
		}
	}
};