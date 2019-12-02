#pragma once
#include <GL/GL.h>
class FormatConver
{
public:
	FormatConver();
	~FormatConver();
public:
	bool rgb2yuv(const void *buffer, int width, int height, void *outbuffer, int &outbuflen);
	bool drawImage(const void *buffer, int width, int height);
private:
	void initTexture();
	void initProgram();
	void initVertexArray();
private:
	GLuint m_rgbTexture = 0;
	GLuint m_yuvTexture = 0;
	int m_textureWidth = 0;
	int m_textureHeight = 0;
	GLuint m_frameBuffer = 0;
	GLuint m_depthBuffer = 0;
	GLuint m_program = 0;
	GLuint m_vBuffer = 0;
	GLuint m_fBuffer = 0;
};

