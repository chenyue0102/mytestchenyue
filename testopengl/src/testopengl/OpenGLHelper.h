#pragma once
#include <GL/glew.h>
#include <stdio.h>

inline void CHECKERR() {
	int err = 0;
	if (GL_NO_ERROR != (err = glGetError()))
	{
		printf("glGetError=%d\n", err);
	}
}

#define BUFFER_OFFSET(offset) ((void*)(offset))

namespace OpenGLHelper {
void outputCompileShader(GLuint shader);
void outputProgramLog(GLuint program);
GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len);
};