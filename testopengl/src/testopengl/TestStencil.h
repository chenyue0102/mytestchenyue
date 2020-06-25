#pragma once
#include <GL/glew.h>
#include "OpenGLHelper.h"

using namespace OpenGLHelper;
namespace TestStencil {

	static const GLubyte tex_checkerboard_data[] = {
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
	};

	static const GLfloat g_vertex[][2] = {
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ -1.0f, 1.0f },
		{ 1.0f, 1.0f },
	};

	static const GLfloat g_cvertex[][2] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
	};

	static const char *g_vString = R"(
#version 430 core
layout(location=0) in vec4 vPosition;
layout(location=1) in vec4 tPosition;
//#define USE_PIPELINE
//pipeline形式,内置的gl_PerVertex必须重新声明
#ifdef USE_PIPELINE
out gl_PerVertex{
	vec4 gl_Position;
	float gl_PointSize;
};
#endif
out Param{
	vec4 fPosition;
};
void main(){
	gl_Position = vPosition;
	fPosition = tPosition;
}
)";

	static const char *g_fString = R"(
#version 430 core
layout(location=2) uniform sampler2D tex;
in Param{
	vec4 fPosition;
};
out vec4 fColor;
void main(){
	float clr = texture2D(tex, fPosition.xy).r;
	if (clr <= 0.0f){
		discard;	//丢弃该片段
	}else{
		fColor = vec4(clr, clr, clr, 1.0f);
	}
}
)";

	static GLuint g_texture = 0;
	static GLuint g_vertexindex = 0;
	static GLuint g_buffer = 0;
	GLuint g_vprogramX = 0;

	void init() {
		glGenTextures(1, &g_texture);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLsizei level = 0;//mip等级
		GLint internalformat = GL_RED;//材质内部编码
		GLint border = 0;//must0
		GLenum format = GL_RED;//tex_checkerboard_data编码
		GLenum type = GL_UNSIGNED_BYTE;//tex_checkerboard_data类型
									   //glTexStorage2D(GL_TEXTURE_2D, level, internalformat, 8, 8);
		glTexImage2D(GL_TEXTURE_2D, level, internalformat, 8, 8, border, format, type, nullptr);
		CHECKERR();


		glGenBuffers(1, &g_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, g_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex) + sizeof(g_cvertex), nullptr, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex), g_vertex);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex), sizeof(g_cvertex), g_cvertex);
		CHECKERR();

		glGenVertexArrays(1, &g_vertexindex);
		glBindVertexArray(g_vertexindex);
		glBindBuffer(GL_ARRAY_BUFFER, g_buffer);

		GLuint vPositionLocation = 0;
		glVertexAttribPointer(vPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vPositionLocation);

		GLuint tPositionLocation = 1;
		glVertexAttribPointer(tPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(g_vertex)));
		glEnableVertexAttribArray(tPositionLocation);
		CHECKERR();
#if 0
		g_vprogramX = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &g_vString);
		g_fprogramX = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &g_fString);
		glCreateProgramPipelines(1, &g_pipelineX);
#else
		g_vprogramX = glCreateProgram();
		attachShader(g_vprogramX, GL_VERTEX_SHADER, g_vString, 0);
		attachShader(g_vprogramX, GL_FRAGMENT_SHADER, g_fString, 0);
		glLinkProgram(g_vprogramX);
		outputProgramLog(g_vprogramX);
		CHECKERR();
#endif
	}

	void testdraw() {

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glClear(GL_STENCIL_BUFFER_BIT);
		CHECKERR();

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);//禁止绘制到帧缓存中，这样就只绘制到模板缓存中中
		glStencilFunc(GL_ALWAYS, 1, 0Xff);					//绘制时，将全部内容均绘制到模板缓存中，GLSL中，片元着色器会丢弃不符合的片段
		glStencilMask(0xff);								//允许修改模板缓存所有bit
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);			//
		CHECKERR();

		glUseProgram(g_vprogramX);
		CHECKERR();

		glBindVertexArray(g_vertexindex);
		CHECKERR();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 8, 8, GL_RED, GL_UNSIGNED_BYTE, tex_checkerboard_data);
		GLuint texLocation = glGetUniformLocation(g_vprogramX, "tex");
		glUniform1i(texLocation, 0);
		CHECKERR();

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		CHECKERR();
	}
};