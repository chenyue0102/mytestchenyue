#pragma once
#include <GL/GL.h>
#define CHECKERRBREAK \
	if (GL_NO_ERROR != glGetError())\
	{\
		assert(false); \
		break;\
	}

#define INVALID_VALUE 0
namespace OpenGLHelper
{
GLuint genTexture(GLenum inFormat, GLenum format, GLenum type, int width, int height);
bool genTextures(GLsizei n, GLuint *texs);
GLuint genRenderbuffer(int width, int height);
GLuint genFramebuffer(GLuint texture, GLuint renderbuffer);
bool setVertexAttribPointer(GLuint program, const char *vertexName, const char *textureName);
GLuint createShader(GLenum type, const char *string);
GLuint genAndBindTexture(int width, int height, GLuint bindIndex, GLenum access, GLenum shaderFormat);
GLuint genAndBindTexture(int width, int height, GLuint bindIndex, GLenum access, GLenum shaderFormat, GLenum bufFormat, GLenum bufType, const void *buffer);
};

