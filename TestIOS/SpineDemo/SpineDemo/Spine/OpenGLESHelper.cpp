#include "OpenGLESHelper.h"
#include <assert.h>
#include <stdio.h>


namespace OpenGLESHelper {
void test() {

}

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
			printf("%s\n", szBuf);
		}
		else
		{
			GLchar *buf = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, nullptr, buf);
			buf[len] = '\0';
			printf("%s\n", buf);
			delete[]buf;
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
			printf("%s\n", szBuf);
		}
		else
		{
			GLchar *buf = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, nullptr, buf);
			buf[len] = '\0';
			printf("%s\n", buf);
			delete[]buf;
		}
		assert(false);
	}
}

GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len) {
	GLenum err = GL_NO_ERROR;
	GLuint shader = 0;

	do
	{
		if (0 == (shader = glCreateShader(type))) {
			err = glGetError();
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
	return err;
}

GLenum createTexture2D(GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint filterParam, GLuint &tex) {
	GLenum err = GL_NO_ERROR;
	bool needClean = false;
	do
	{
		glGenTextures(1, &tex); CHECK_BREAK;
		needClean = true;
		glBindTexture(GL_TEXTURE_2D, tex); CHECK_BREAK;
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, type, 0); CHECK_BREAK;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParam); CHECK_BREAK;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParam); CHECK_BREAK;
	} while (false);

	if (GL_NO_ERROR != err && needClean) {
		glDeleteTextures(1, &tex);
	}
	return err;
}
GLenum createArrayBuffer(const void* vertexPointsBuffer, GLsizei vlen, const void* colorPointsBuffer, GLsizei clen, GLuint &buf)
{
	GLenum err = GL_NO_ERROR;
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

	if (GL_NO_ERROR != err && needClean) {
		glDeleteBuffers(1, &buf);
	}
	return err;
}

};
