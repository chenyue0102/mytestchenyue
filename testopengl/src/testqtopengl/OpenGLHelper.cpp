#include <assert.h>
#include <GL/glew.h>
#include "OpenGLHelper.h"



namespace OpenGLHelper
{
GLuint genTexture(GLenum inFormat, GLenum format, GLenum type, int width, int height)
{
	GLuint textures = INVALID_VALUE;
	GLenum err = GL_NO_ERROR;
	bool ret = false;
	do
	{
		if (0 == inFormat
			|| 0 == format
			|| 0 == type
			|| 0 == width
			|| 0 == height)
		{
			assert(false);
			break;
		}
		glGenTextures(1, &textures);
		CHECKERRBREAK;

		glBindTexture(GL_TEXTURE_2D, textures);
		CHECKERRBREAK;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		CHECKERRBREAK;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		CHECKERRBREAK;

		glTexImage2D(GL_TEXTURE_2D, 0, inFormat, width, height, 0, format, type, nullptr);
		CHECKERRBREAK;

		glBindTexture(GL_TEXTURE_2D, 0);
		ret = true;
	} while (false);
	if (!ret
		&& INVALID_VALUE != textures)
	{
		glDeleteTextures(1, &textures);
		textures = INVALID_VALUE;
	}
	return textures;
}
bool genTextures(GLsizei n, GLuint * texs)
{
	bool ret = false;
	GLenum err = GL_NO_ERROR;
	do
	{
		glGenTextures(n, texs);
		CHECKERRBREAK;

		for (int i = 0; i < n; i++)
		{
			glBindTexture(GL_TEXTURE_2D, texs[i]);
			CHECKERRBREAK;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			CHECKERRBREAK;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			CHECKERRBREAK;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		ret = true;
	} while (false);

	if (!ret
		&& nullptr != texs)
	{
		glDeleteTextures(n, texs);
	}
	return ret;
}
GLuint genRenderbuffer(int width, int height)
{
	GLuint renderBuffer = INVALID_VALUE;
	GLenum err = GL_NO_ERROR;
	bool ret = false;

	do
	{
		glGenRenderbuffers(1, &renderBuffer);
		CHECKERRBREAK;

		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		CHECKERRBREAK;

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		CHECKERRBREAK;

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		ret = true;
	} while (false);
	if (!ret
		&& INVALID_VALUE != renderBuffer)
	{
		glDeleteRenderbuffers(1, &renderBuffer);
		renderBuffer = INVALID_VALUE;
	}
	return renderBuffer;
}
GLuint genFramebuffer(GLuint texture, GLuint renderbuffer)
{
	GLuint framebuffer = INVALID_VALUE;
	GLenum err = GL_NO_ERROR;
	bool ret = false;

	do
	{
		if (INVALID_VALUE == texture
			|| INVALID_VALUE == renderbuffer)
		{
			assert(false);
			break;
		}
		glGenFramebuffers(1, &framebuffer);
		CHECKERRBREAK;

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		CHECKERRBREAK;

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		CHECKERRBREAK;

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
		CHECKERRBREAK;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		CHECKERRBREAK;

		if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
		{
			assert(false);
			break;
		}
		ret = true;
	} while (false);
	if (!ret
		&& INVALID_VALUE != framebuffer)
	{
		glDeleteFramebuffers(1, &framebuffer);
		framebuffer = INVALID_VALUE;
	}
	return framebuffer;
}

bool setVertexAttribPointer(GLuint program, const char *vertexName, const char *textureName)
{
	bool ret = false;
	GLenum err = GL_NO_ERROR;

	do
	{
		if (INVALID_VALUE == program)
		{
			assert(false);
			break;
		}

		//verPointer需要保持生命周期，用在glDrawArrays
		static const GLfloat verPointer[] =
		{
			-1.0f, -1.0f,
			1.0f, -1.0f,
			-1.0f, 1.0f,
			1.0f, 1.0f
		};
		int vertexIndex = glGetAttribLocation(program, vertexName);
		CHECKERRBREAK;
		glVertexAttribPointer(vertexIndex, 2, GL_FLOAT, 0, 0, verPointer);
		CHECKERRBREAK;
		glEnableVertexAttribArray(vertexIndex);
		CHECKERRBREAK;

		//texPointer需要保持生命周期，用在glDrawArrays
		static const GLfloat texPointer[] = {
			0.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
		};
		int textureIndex = glGetAttribLocation(program, textureName);
		CHECKERRBREAK;
		glVertexAttribPointer(textureIndex, 2, GL_FLOAT, 0, 0, texPointer);
		CHECKERRBREAK;
		glEnableVertexAttribArray(textureIndex);

		ret = true;
	} while (false);
	return ret;
}
GLuint createShader(GLenum type, const char * string)
{
	bool ret = false;
	GLenum err = GL_NO_ERROR;
	GLuint shader = INVALID_VALUE;

	do
	{
		if (nullptr == string)
		{
			assert(false);
			break;
		}
		shader = glCreateShader(type);
		CHECKERRBREAK;
		glShaderSource(shader, 1, &string, nullptr);
		CHECKERRBREAK;
		glCompileShader(shader);
		CHECKERRBREAK;
		ret = true;
	} while (false);
	if (!ret
		&& INVALID_VALUE != shader)
	{
		glDeleteShader(shader);
		shader = INVALID_VALUE;
	}
	return shader;
}
GLuint genAndBindTexture(int width, int height, GLuint bindIndex, GLenum access, GLenum shaderFormat)
{
	GLuint tex = INVALID_VALUE;
	bool ret = false;
	do
	{
		if (INVALID_VALUE == (tex = genTexture(GL_RGBA32F, GL_RGBA, GL_FLOAT, width, height)))
		{
			assert(false);
			break;
		}
		glBindTexture(GL_TEXTURE_2D, tex);
		CHECKERRBREAK;
		glBindImageTexture(bindIndex, tex, 0, GL_FALSE, 0, access, shaderFormat);
		CHECKERRBREAK;
		ret = true;
	} while (false);
	if (!ret
		&& INVALID_VALUE != tex)
	{
		glDeleteTextures(1, &tex);
		tex = INVALID_VALUE;
	}
	return tex;
}
GLuint genAndBindTexture(int width, int height, GLuint bindIndex, GLenum access, GLenum shaderFormat, GLenum bufFormat, GLenum bufType, const void * buffer)
{
	GLuint tex = INVALID_VALUE;
	bool ret = false;

	do
	{
		if (INVALID_VALUE == (tex = genAndBindTexture(width, height, bindIndex, access, shaderFormat)))
		{
			assert(false);
			break;
		}
		glBindTexture(GL_TEXTURE_2D, tex);
		CHECKERRBREAK;
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, bufFormat, bufType, buffer);
		CHECKERRBREAK;
		ret = true;
	} while (false);
	if (!ret
		&& INVALID_VALUE != tex)
	{
		glDeleteTextures(1, &tex);
		tex = INVALID_VALUE;
	}
	return tex;
}
}
