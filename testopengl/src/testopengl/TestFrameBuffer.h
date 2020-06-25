#pragma once
#include <GL/glew.h>
#include "Test.h"
#include "OpenGLHelper.h"
#include "TestTexture.h"

namespace TestFrameBuffer {
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
		GLenum ret = GL_NO_ERROR;
		ret = OpenGLHelper::createTexture2D(GL_RGB8, 400, 400, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, g_texture); assert(ret == GL_NO_ERROR);
		g_program = glCreateProgram(); assert(0 != g_program);
		ret = OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, vStringxx, 0); assert(ret == GL_NO_ERROR);
		ret = OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, fStringxx, 0); assert(ret == GL_NO_ERROR);
		glLinkProgram(g_program); 
		outputProgramLog(g_program);
		CHECKERR();

		glGenRenderbuffers(1, &g_renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, g_renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 400, 400);
		CHECKERR();

		glGenFramebuffers(1, &g_framebuffer);
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
		//GL_DRAW_FRAMEBUFFER 绘制缓存,GL_READ_FRAMEBUFFER读取缓存 GL_FRAMEBUFFER 可读可写
		glBindFramebuffer(GL_FRAMEBUFFER, g_framebuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, g_texture, 0);
		GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffers);
		//glDrawBuffer(GL_FRONT_AND_BACK);//同时写入前缓存与后缓存
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
		CHECKERR();

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

		//从帧缓冲区中拷贝数据
		static bool isfirst = true;
		if (isfirst) {
			isfirst = false;
			GLuint tex = 0;
			glGenTextures(1, &tex); CHECKERR();
			glBindTexture(GL_TEXTURE_2D, tex); CHECKERR();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 400, 400, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr); CHECKERR();
			//glReadBuffer(GL_BACK); CHECKERR();
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 0, 0, 400, 400, 0); CHECKERR();
			std::string tmpBuf;
			tmpBuf.resize(400 * 400 * 3);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, &tmpBuf[0]); CHECKERR();
			SaveBitmap("d:/1.bmp", 400, 400, 24, &tmpBuf[0], tmpBuf.size());

			std::string tmpBuf2;
			tmpBuf2.resize(400 * 400 * 3);
			glReadPixels(0, 0, 400, 400, GL_BGR, GL_UNSIGNED_BYTE, &tmpBuf2[0]);
			SaveBitmap("d:/2.bmp", 400, 400, 24, &tmpBuf2[0], tmpBuf2.size());
		}
	}

	static void testdraw() {
		drawtorenderbuffer();
	}
};