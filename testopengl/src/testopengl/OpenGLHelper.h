#pragma once
#include <GL/glew.h>
#include <stdio.h>
#include <assert.h>

inline void CHECKERR() {
	int err = 0;
	if (GL_NO_ERROR != (err = glGetError())){
		assert(false);
		printf("glGetError=%d\n", err);
	}
}

#define BUFFER_OFFSET(offset) ((void*)(offset))

#define CHECK_BREAK \
	if (GL_NO_ERROR != (ret = glGetError())) { \
		printf("glGetError=%x\n", ret); \
		assert(false); \
		break; \
	}

namespace OpenGLHelper {
void outputCompileShader(GLuint shader);
void outputProgramLog(GLuint program);
bool SaveBitmap(const char* pFileName, int width, int height, int biBitCount, const void* pBuf, int nBufLen);
GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len);
GLenum createTexture2D(GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint filterParam, GLuint& tex);
GLenum createArrayBuffer(const void* vertexPointsBuffer, GLsizei vlen, const void* colorPointsBuffer, GLsizei clen, GLuint& buf);
};