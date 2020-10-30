#ifndef OpenGLShaderProgram_h_
#define OpenGLShaderProgram_h_

#include <assert.h>
#include <string>
#include <stdio.h>
#include "OpenGLESHelper.h"
#include "vmath.h"
#include "spine/Color.h"


class OpenGLShaderProgram {
public:
	OpenGLShaderProgram() 
		: mProgram(0)
		, mVertexArray(0)
		, mVertexBuffer(0)
	{
		mProgram = glCreateProgram(); CHECKERR;
		initVertex();
	}
	virtual ~OpenGLShaderProgram() {
		glDeleteProgram(mProgram); CHECKERR;
		mProgram = 0;
		destroyVertex();
	}

	void initVertex() {
		glGenVertexArrays(1, &mVertexArray); CHECKERR;
		glGenBuffers(1, &mVertexBuffer); CHECKERR;
	}

	void destroyVertex() {
		if (0 != mVertexArray) {
			glDeleteVertexArrays(1, &mVertexArray);
			mVertexArray = 0;
		}
		if (0 != mVertexBuffer) {
			glDeleteBuffers(1, &mVertexBuffer);
			mVertexBuffer = 0;
		}
	}

public:
	GLuint programId() {
		return mProgram;
	}

public:
	bool readShaderSourceFile(const char* filePath, std::string &shaderText) {
		FILE *file = fopen(filePath, "r");
		if (nullptr == file) {
			assert(false);
			return false;
		}
		fseek(file, 0, SEEK_END);
		auto fileLen = ftell(file);
		shaderText.resize(fileLen, '\0');
		fseek(file, 0, SEEK_SET);
		fread(&*shaderText.begin(), 1, fileLen, file);
		fclose(file);
		return true;
	}
	//GL_VERTEX_SHADER GL_FRAGMENT_SHADER
	bool addShaderFromSourceFile(GLenum shaderType, const char *path) {
		bool ret = false;

		do
		{
			std::string text;
			if (!readShaderSourceFile(path, text)) {
				assert(false);
				break;
			}
			if (GL_NO_ERROR != OpenGLESHelper::attachShader(mProgram, shaderType, text.c_str(), text.size())) {
				assert(false);
				break;
			}
			ret = true;
		} while (false);
		return ret;
	}

	bool bind() {
		glUseProgram(mProgram); CHECKERR;
		glBindVertexArray(mVertexArray); CHECKERR;
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer); CHECKERR;
		return true;
	}

	bool unbind(){
		if (0 != mProgram){
			glBindVertexArray(0);CHECKERR;
			glBindBuffer(GL_ARRAY_BUFFER, 0);CHECKERR;
			glUseProgram(0);CHECKERR;
		}
		return true;
	}

	bool link() {
		glLinkProgram(mProgram); CHECKERR;
		return glGetError() == GL_NO_ERROR;
	}

public:
	GLint attributeLocation(const GLchar* name) {
		return glGetAttribLocation(mProgram, name);
	}

	void enableAttributeArray(const GLchar* name) {
		glEnableVertexAttribArray(attributeLocation(name)); CHECKERR;
	}

	void setVertexArrayBufferData(const void *data, int len) {
		glBindVertexArray(mVertexArray); CHECKERR;
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer); CHECKERR;
		glBufferData(GL_ARRAY_BUFFER, len, data, GL_STATIC_DRAW); CHECKERR;
	}

	void setAttributeArray(const char *name, GLenum type, const void *values, int tupleSize, int stride) {
		GLint location = attributeLocation(name);
		if (-1 != location) {
			glVertexAttribPointer(location, tupleSize, type, GL_TRUE, stride, values); CHECKERR;
		}
		else {
			assert(false);
		}
	}

	void setAttributeArray(const GLchar *name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizei offset) {
		GLint location = attributeLocation(name);
		if (-1 != location) {
			glVertexAttribPointer(location, size, type, normalized, stride, (const void*)offset); CHECKERR;
		}
		else {
			assert(false);
		}
	}

	GLint uniformLocation(const GLchar* name) {
		return glGetUniformLocation(mProgram, name); 
	}

	void setUniformValue(const GLchar* name, vmath::mat4 mat) {
		GLint location = uniformLocation(name);
		if (-1 != location) {
#ifdef __ANDROID__
			glUniformMatrix4fv(location, 1, GL_FALSE, mat); CHECKERR;
#else
            glProgramUniformMatrix4fvEXT(mProgram, location, 1, GL_FALSE, mat); CHECKERR();
#endif
		}
		else {
			assert(false);
		}
	}

	void setUniformValue(const GLchar *name, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		GLint location = uniformLocation(name); CHECKERR;
		if (-1 != location) {
#ifdef __ANDROID__
			glUniform4f(location, r, g, b, a); CHECKERR;
#else
            glProgramUniform4fEXT(mProgram, location, r, g, b, a); CHECKERR();
#endif
		}
		else {
			assert(false);
		}
	}

	void setUniformValue(const GLchar* name, GLint i) {
		GLint location = uniformLocation(name); CHECKERR;
		if (-1 != location) {
#ifdef __ANDROID__
			glUniform1i(location, i); CHECKERR;
#else
            glProgramUniform1iEXT(mProgram, location, i); CHECKERR();
#endif
		}
		else {
			assert(false);
		}
	}

	void setUniformValue(const GLchar* name, GLfloat f) {
		GLint location = uniformLocation(name); CHECKERR;
		if (-1 != location) {
#ifdef __ANDROID__
			glUniform1f(location, f); CHECKERR;
#else
            glProgramUniform1fEXT(mProgram, location, f); CHECKERR();
#endif
		}
		else {
			assert(false);
		}
	}

	void setUniformValue(const GLchar* name, const spine::Color &color) {
		setUniformValue(name, color.r, color.g, color.b, color.a);
	}

private:
	GLuint mProgram;
public:
	GLuint mVertexArray;
	GLuint mVertexBuffer;
};

#endif
