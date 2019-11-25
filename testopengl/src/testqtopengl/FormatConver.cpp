#include <GL/glew.h>
#include "FormatConver.h"
#include <assert.h>


#define GET_STR(x) #x


const char *vString = GET_STR(
	attribute vec4 vertexIn;
	attribute vec2 textureIn;
	varying vec2 textureOut;
	void main(void)
	{
		gl_Position = vertexIn;
		textureOut = textureIn;
	}
);

//rgb2yuv
//const char *fString = GET_STR(
//	varying vec2 textureOut;
//	uniform sampler2D tex;
//	void main(void)
//	{
//		vec4 rgb4 = texture2D(tex, textureOut);
//		vec3 rgb = vec3(rgb4.x, rgb4.y, rgb4.z);
//		vec3 yuv = mat3(0.299, 0.587, 0.114,
//			-0.169, -0.331, 0.5,
//			0.5, -0.419, -0.081) * rgb + vec3(0, 128, 128);
//		gl_FragColor = vec4(yuv, 1.0);
//	}
//);
const char *fString = GET_STR(
	varying vec2 textureOut;
uniform sampler2D tex;
void main(void)
{
	vec4 rgb4 = texture2D(tex, textureOut);
	vec3 rgb = vec3(rgb4.x, rgb4.y, rgb4.z);
	vec3 yuv = mat3(0.299, 0.587, 0.114,
		-0.169, -0.331, 0.5,
		0.5, -0.419, -0.081) * rgb + vec3(0, 128, 128);
	gl_FragColor = vec4(rgb, 1.0);
}
);

FormatConver::FormatConver()
{
}


FormatConver::~FormatConver()
{
}

bool FormatConver::rgb2yuv(const void * buffer, int width, int height, void * outbuffer, int & outbuflen)
{
	int len = width * height * 3;
	if (outbuflen < len)
	{
		outbuflen = len;
		return false;
	}
	m_textureWidth = width;
	m_textureHeight = height;
	if (0 == m_rgbTexture)
	{
		initTexture();
		initProgram();
	}

	static const GLfloat verPointer[] = 
	{
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};
	int vertexIn = glGetAttribLocation(m_program, "vertexIn");
	glVertexAttribPointer(vertexIn, 2, GL_FLOAT, 0, 0, verPointer);
	glEnableVertexAttribArray(vertexIn);

	static const GLfloat texPointer[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};
	int textureIn = glGetAttribLocation(m_program, "textureIn");
	glVertexAttribPointer(textureIn, 2, GL_FLOAT, 0, 0, texPointer);
	glEnableVertexAttribArray(textureIn);

	int tex = glGetUniformLocation(m_program, "tex");

	glUseProgram(m_program);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glViewport(0, 0, m_textureWidth, m_textureHeight);
	//render
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_rgbTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_textureWidth, m_textureHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glUniform1i(tex, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_yuvTexture);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, outbuffer);
	glDisable(GL_TEXTURE_2D);
	return true;
}

bool FormatConver::drawImage(const void * buffer, int width, int height)
{
	m_textureWidth = width;
	m_textureHeight = height;
	if (0 == m_rgbTexture)
	{
		initTexture();
		initProgram();
	}
	static const GLfloat verPointer[] =
	{
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};
	int vertexIn = glGetAttribLocation(m_program, "vertexIn");
	glVertexAttribPointer(vertexIn, 2, GL_FLOAT, 0, 0, verPointer);
	glEnableVertexAttribArray(vertexIn);

	static const GLfloat texPointer[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};
	int textureIn = glGetAttribLocation(m_program, "textureIn");
	glVertexAttribPointer(textureIn, 2, GL_FLOAT, 0, 0, texPointer);
	glEnableVertexAttribArray(textureIn);

	int tex = glGetUniformLocation(m_program, "tex");

	glUseProgram(m_program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_rgbTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_textureWidth, m_textureHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glUniform1i(tex, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glUseProgram(0);

	return true;
}

void FormatConver::initTexture()
{
	GLuint texs[2] = { 0 };
	glGenTextures(2, texs);
	for (auto tex : texs)
	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	}
	m_rgbTexture = texs[0];
	m_yuvTexture = texs[1];
	
	glGenRenderbuffers(1, &m_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_textureWidth, m_textureHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_yuvTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(GL_FRAMEBUFFER_COMPLETE == status);
}

void FormatConver::initProgram()
{
	m_vShader = glCreateShader(GL_VERTEX_SHADER);
	m_fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vShader, 1, &vString, nullptr);
	glShaderSource(m_fShader, 1, &fString, nullptr);

	glCompileShader(m_vShader);
	/*GLint value = 0;
	glGetShaderiv(m_vShader, GL_COMPILE_STATUS, &value);
	char logbuf[1024] = { 0 };
	int len = 1024;
	glGetShaderInfoLog(m_vShader, value, &len, logbuf);*/
	glCompileShader(m_fShader);

	m_program = glCreateProgram();

	glAttachShader(m_program, m_vShader);
	glAttachShader(m_program, m_fShader);

	glLinkProgram(m_program);
}
