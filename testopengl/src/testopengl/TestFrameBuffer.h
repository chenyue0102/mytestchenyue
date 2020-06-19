#pragma once
#include <GL/glew.h>
#include "Test.h"
#include "OpenGLHelper.h"

namespace TestFrameBuffer {
	GLuint g_framebuffer = 0;
	GLuint g_renderbuffer = 0;

	static void init() {
		glGenRenderbuffers(1, &g_renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, g_renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 400, 400);
		CHECKERR();

		glGenFramebuffers(1, &g_framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_framebuffer);
		CHECKERR();

		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, g_renderbuffer);
		CHECKERR();
	}

	static void testdraw() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_framebuffer);
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
};