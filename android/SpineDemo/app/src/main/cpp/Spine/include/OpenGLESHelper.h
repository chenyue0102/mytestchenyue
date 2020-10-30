#ifndef OpenGLES_Helper_h_
#define OpenGLES_Helper_h_
#pragma once

#ifdef WIN32
#include <GL/glew.h>
#elif defined __ANDROID__
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#elif defined __APPLE__
#include <OpenGLES/ES3/glext.h>
#else
#error "platform unknown"
#endif

#include <stdio.h>
#include <assert.h>
#include "Log.h"

inline void outputOpenGLError(unsigned int code, const char *fileName, const char *funName, int line){
	Log::e("OpenGL error:%x file:%s fun:%s line:%d", code, fileName, funName, line);
}

#define CHECKERR \
{\
	unsigned int err = 0; \
	if (GL_NO_ERROR != (err = glGetError())){ \
        outputOpenGLError(err, __FILE__, __FUNCTION__, __LINE__); \
        assert(false); \
    } \
}

#define CHECKBREAK \
{ \
	unsigned int err = 0; \
	if (GL_NO_ERROR != (err = glGetError())) { \
		outputOpenGLError(err, __FILE__, __FUNCTION__, __LINE__); \
		assert(false); \
		break; \
	} \
}

#define BUFFER_OFFSET(offset) ((void*)(offset))

namespace OpenGLESHelper {
void outputCompileShader(GLuint shader);
void outputProgramLog(GLuint program);
GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len);
GLenum createTexture2D(GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint filterParam, GLuint& tex);
GLenum createArrayBuffer(const void* vertexPointsBuffer, GLsizei vlen, const void* colorPointsBuffer, GLsizei clen, GLuint& buf);
};
#endif
