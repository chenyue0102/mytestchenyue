#include <GL/glew.h>
#include "FormatConver.h"
#include <assert.h>
#include <QDebug>
#include "OpenGLHelper.h"

#define CHECKERR \
{\
int err = 0;\
if (GL_NO_ERROR != (err = glGetError()))\
{\
assert(false); \
qDebug() << "glGetError=" <<err;\
}\
}

inline void outputCompileShader(GLuint shader)
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
			qDebug() << szBuf;
		}
		else
		{
			GLchar *buf = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, nullptr, buf);
			buf[len] = '\0';
			qDebug() << buf;
			delete[]buf;
		}
		assert(false);
	}
}
inline void outputProgramLog(GLuint program)
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
			qDebug() << szBuf;
		}
		else
		{
			GLchar *buf = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, nullptr, buf);
			buf[len] = '\0';
			qDebug() << buf;
			delete[]buf;
		}
		assert(false);
	}
}


#if 1
const char *vString = R"(
#version 430 core
	in vec4 vertexIn;
	in vec2 textureIn;
	out vec2 textureOut;
	void main(void)
	{
		gl_Position = vertexIn;
		textureOut = textureIn;
	}
)";

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
const char *fString = R"(
#version 430 core
#if 0
varying vec2 textureOut;
uniform sampler2D tex;
uniform int bCover;
uniform float nThreshold;
#else
in vec2 textureOut;
out vec4 fColor;
uniform sampler2D tex;
struct Param
{
	int bCover;
	float nThreshold;
};
uniform Param param;
#endif
	
void main(void)
{
	vec4 rgb4 = texture2D(tex, textureOut);
	vec3 rgb = vec3(rgb4.x, rgb4.y, rgb4.z);
	vec3 yuv = mat3(0.299, 0.587, 0.114,
		-0.169, -0.331, 0.5,
		0.5, -0.419, -0.081) * rgb + vec3(0, 128, 128);
	if (0 == param.bCover)
	{
		fColor = vec4(rgb, 1.0);
	}
	else
	{
		if (yuv.x >= param.nThreshold)
		{
			fColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
		else
		{
			fColor = vec4(0.0, 0.0, 0.0, 1.0);
		}
	}
}
)";
#endif
//rgb2yuv420
const char *cString = R"(
#version 430 core
//y row x col
layout (local_size_x=32,local_size_y=32) in;
layout (binding=0,rgba32f) uniform image2D  rgbTex;
layout (binding=1,rgba32f) uniform image2D yTex;
layout (binding=2,rgba32f) uniform image2D uTex;
layout (binding=3,rgba32f) uniform image2D vTex;
//每个线程处理的列数
uint getColCountPerThread()
{
	ivec2 dims = imageSize(rgbTex);
	uint texWidth = dims.x;
	//gl_WorkGroupSize.y表示第二个维度，分配多少个线程
	uint count = (texWidth / gl_WorkGroupSize.y);
	if ((texWidth % gl_WorkGroupSize.y) != 0)
	{
		count++;
	}
	return count;
}
vec3 rgb2yuv(vec3 rgb)
{
#if 1
	vec3 yuv = mat3(0.299,-0.169,0.5,
		0.587,-0.331,-0.419,
		0.114,0.5,-0.081)*rgb + vec3(0.0,0.5,0.5);
	return yuv;
#else
	vec3 yuv;
	yuv.r = 0.299*rgb.r;
#endif

}
void main()
{
	ivec2 dims = imageSize(rgbTex);
	int texWidth = dims.x;
	int texHeight = dims.y;
	const uvec3 groupSize = gl_WorkGroupSize;
	const uvec3 localId = gl_LocalInvocationID;
	const uint colCount = getColCountPerThread();
	
	for (uint row = localId.x; row < texHeight; row+=groupSize.x)
	{
		uint beginNum = localId.y * colCount;
		//uv 偶数行设置
		int uvRow = (row & 0x00000001) == 0 ? int(row / 2) : -1;
		bool bEvenCol = (beginNum & 0x00000001) == 0;//偶数列
		for (uint col = beginNum; col < texWidth && col < (beginNum + colCount); col++)
		{
			ivec2 pos = ivec2(col, row);
			vec4 texel = imageLoad(rgbTex, pos);
			vec3 yuv = rgb2yuv(texel.rgb);
			imageStore(yTex, pos, vec4(yuv.r, 0.0, 0.0, 0.0));
			if (-1 != uvRow)
			{
				if (bEvenCol)
				{
					imageStore(uTex, ivec2(col / 2, uvRow), vec4(yuv.g, 0.0, 0.0, 0.0));
					imageStore(vTex, ivec2(col / 2, uvRow), vec4(yuv.b, 0.0, 0.0, 0.0));
				}
				bEvenCol = !bEvenCol;
			}
		}
	}
}
)";
FormatConver::FormatConver()
{
}


FormatConver::~FormatConver()
{
}

bool FormatConver::rgb2yuv(const void * buffer, int width, int height, void * outbuffer, int & outbuflen)
{
	int cShader = glCreateShader(GL_COMPUTE_SHADER);
	CHECKERR;
	glShaderSource(cShader, 1, &cString, nullptr);
	CHECKERR;
	glCompileShader(cShader);
	outputCompileShader(cShader);

	int program = glCreateProgram();
	CHECKERR;
	glAttachShader(program, cShader);
	CHECKERR;
	glLinkProgram(program);
	outputProgramLog(program);
	glDeleteShader(cShader);
	CHECKERR;
	cShader = 0;

	glUseProgram(program);
	CHECKERR;

#if 0
	CHECKERR;
	GLuint rgbTexture = 0;
	glGenTextures(1, &rgbTexture);
	CHECKERR;
	glBindTexture(GL_TEXTURE_2D, rgbTexture);
	CHECKERR;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	CHECKERR;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	CHECKERR;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	CHECKERR
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	CHECKERR;
	glBindImageTexture(0, rgbTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	CHECKERR;
	
	CHECKERR;
	GLuint yTexture = 0;
	glGenTextures(1, &yTexture);
	CHECKERR;
	glBindTexture(GL_TEXTURE_2D, yTexture);
	CHECKERR;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	CHECKERR;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	CHECKERR;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	CHECKERR;
	glBindImageTexture(1, yTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
#endif
	GLuint rgbTexture = OpenGLHelper::genAndBindTexture(width, height, 0, GL_READ_ONLY, GL_RGBA32F, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	GLuint yTexture = OpenGLHelper::genAndBindTexture(width, height, 1, GL_WRITE_ONLY, GL_RGBA32F);
	GLuint uTexture = OpenGLHelper::genAndBindTexture(width / 2, height / 2, 2, GL_WRITE_ONLY, GL_RGBA32F);
	GLuint vTexture = OpenGLHelper::genAndBindTexture(width / 2, height / 2, 3, GL_WRITE_ONLY, GL_RGBA32F);
	glDispatchCompute(32, 1, 1);
	CHECKERR;
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
	//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	CHECKERR;

	glBindTexture(GL_TEXTURE_2D, yTexture);
	CHECKERR;
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, outbuffer);
	CHECKERR;

	char *pu = (char*)(outbuffer)+width * height;
	glBindTexture(GL_TEXTURE_2D, uTexture);
	CHECKERR;
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, pu);
	CHECKERR;

	char *pv = pu +width * height / 4;
	glBindTexture(GL_TEXTURE_2D, vTexture);
	CHECKERR;
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, pv);
	CHECKERR;

	glDeleteTextures(1, &rgbTexture);
	return true;
}
#if 0
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
		initVertexArray();
		initProgram();
	}

	int tex = glGetUniformLocation(m_program, "tex");

	glUseProgram(m_program);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glViewport(0, 0, m_textureWidth, m_textureHeight);
	//render
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CHECKERR;
	glActiveTexture(GL_TEXTURE0);
	CHECKERR;
	glBindTexture(GL_TEXTURE_2D, m_rgbTexture);
	CHECKERR;
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_textureWidth, m_textureHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	CHECKERR;
	glUniform1i(tex, 0);
	CHECKERR;
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CHECKERR;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_yuvTexture);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, outbuffer);
	glDisable(GL_TEXTURE_2D);
	return true;
}
#endif

bool FormatConver::drawImage(const void * buffer, int width, int height)
{
	m_textureWidth = width;
	m_textureHeight = height;
	if (0 == m_rgbTexture)
	{
		initTexture();
		initVertexArray();
		initProgram();
	}
	
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
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vString, nullptr);
	CHECKERR;
	glShaderSource(fShader, 1, &fString, nullptr);
	CHECKERR;

	glCompileShader(vShader);
	outputCompileShader(vShader);
	CHECKERR;
	glCompileShader(fShader);
	outputCompileShader(fShader);
	CHECKERR;

	m_program = glCreateProgram();
	CHECKERR;

	glAttachShader(m_program, vShader);
	CHECKERR;
	glAttachShader(m_program, fShader);
	CHECKERR;

	glLinkProgram(m_program);
	outputProgramLog(m_program);
	CHECKERR;

	glDeleteShader(vShader);
	CHECKERR;
	glDeleteShader(fShader);
	CHECKERR;


	int vertexIn = glGetAttribLocation(m_program, "vertexIn");
	CHECKERR;
	glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer);
	CHECKERR;
	glVertexAttribPointer(vertexIn, 2, GL_FLOAT, 0, 0, 0);
	CHECKERR;
	glEnableVertexAttribArray(vertexIn);
	CHECKERR;

	int textureIn = glGetAttribLocation(m_program, "textureIn");
	CHECKERR;
	glBindBuffer(GL_ARRAY_BUFFER, m_fBuffer);
	CHECKERR;
	glVertexAttribPointer(textureIn, 2, GL_FLOAT, 0, 0, 0);
	CHECKERR;
	glEnableVertexAttribArray(textureIn);
	CHECKERR;

	//需要先use program，才能设置uniform数值
	//glUseProgram(m_program);
	CHECKERR;
	int coverId = glGetUniformLocation(m_program, "param.bCover");
	CHECKERR;
	//glProgramUniform1i比glUniform1i多个program参数,不需要提前glUseProgram
	glProgramUniform1i(m_program, coverId, (GLint)true);
	CHECKERR;

	int thresholdId = glGetUniformLocation(m_program, "param.nThreshold");
	CHECKERR;
	glProgramUniform1f(m_program, thresholdId, 0.1);
	CHECKERR;
	//glUseProgram(0);
	//CHECKERR;
}

void FormatConver::initVertexArray()
{
	const GLfloat verPointer[] =
	{
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};
	CHECKERR;
	glGenBuffers(1, &m_vBuffer);
	CHECKERR;
	glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer);
	CHECKERR;
	glBufferData(GL_ARRAY_BUFFER, sizeof(verPointer), verPointer, GL_STATIC_DRAW);
	CHECKERR;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	CHECKERR;

	const GLfloat texPointer[] = 
	{
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};
	glGenBuffers(1, &m_fBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_fBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texPointer), texPointer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
