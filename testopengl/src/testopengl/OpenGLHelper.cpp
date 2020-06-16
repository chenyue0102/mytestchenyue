#include "OpenGLHelper.h"
#include <assert.h>
#include <stdio.h>


namespace OpenGLHelper {
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
	GLenum ret = GL_NO_ERROR;
	GLuint shader = 0;

	do
	{
		if (0 == (shader = glCreateShader(type))) {
			ret = glGetError();
			break;
		}
		GLint lens[] = { len };
		glShaderSource(shader, 1, &source, (len > 0 ? lens : nullptr));
		if (GL_NO_ERROR != (ret = glGetError())) {
			break;
		}
		glCompileShader(shader);
		outputCompileShader(shader);
		if (GL_NO_ERROR != (ret = glGetError())) {
			break;
		}
		glAttachShader(program, shader);
		if (GL_NO_ERROR != (ret = glGetError())) {
			break;
		}
	} while (false);

	if (0 != shader) {
		glDeleteShader(shader);
		shader = 0;
	}
	return ret;
}
};